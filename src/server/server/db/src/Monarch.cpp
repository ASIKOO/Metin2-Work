#include "Monarch.h"
#include "../../common/utils.h"
#include "Main.h"
#include "ClientManager.h"

extern int32_t g_test_server;

CMonarch::CMonarch()
{
	memset(&m_MonarchInfo, 0, sizeof(MonarchInfo));
}

CMonarch::~CMonarch()
{
}

bool CMonarch::VoteMonarch(uint32_t pid, uint32_t selectdpid)
{
	MAP_MONARCHELECTION::iterator it = m_map_MonarchElection.find(pid);

	if (it == m_map_MonarchElection.end())
	{
		MonarchElectionInfo * p = new MonarchElectionInfo;
		p->pid = pid;
		p->selectedpid= selectdpid;
		m_map_MonarchElection.insert(MAP_MONARCHELECTION::value_type(pid, p));

		char szQuery[256];
		snprintf(szQuery, sizeof(szQuery),
				"INSERT INTO monarch_election(pid, selectedpid, electiondata) VALUES(%d, %d, now())", pid, selectdpid);

		CDBManager::instance().AsyncQuery(szQuery);
		return 1;	
	}

	return 0;
}

void CMonarch::ElectMonarch()
{
	int32_t size = GetVecMonarchCandidacy().size();

	int32_t * s = new int32_t[size];

	itertype(m_map_MonarchElection) it = m_map_MonarchElection.begin();

	int32_t idx = 0;

	for (; it != m_map_MonarchElection.end(); ++it)	
	{
		if ((idx =  GetCandidacyIndex(it->second->pid)) < 0)
			continue;

		++s[idx];

		if (g_test_server)
			sys_log (0, "[MONARCH_VOTE] pid(%d) come to vote candidacy pid(%d)", it->second->pid, m_vec_MonarchCandidacy[idx].pid);
	}

	delete [] s;
}

bool CMonarch::IsCandidacy(uint32_t pid)
{
	VEC_MONARCHCANDIDACY::iterator it = m_vec_MonarchCandidacy.begin();
	
	for (; it != m_vec_MonarchCandidacy.end(); ++it)
	{
		if (it->pid == pid)
			return false;
	}
			
	return true;
}

bool CMonarch::AddCandidacy(uint32_t pid, const char * name)
{
	if (IsCandidacy(pid) == false)
		return false;

	MonarchCandidacy info;

	info.pid = pid;
	strlcpy(info.name, name, sizeof(info.name));
	m_vec_MonarchCandidacy.push_back(info);	

	char szQuery[256];
	snprintf(szQuery, sizeof(szQuery),
			"INSERT INTO monarch_candidacy(pid, date) VALUES(%d, now())", pid);

	CDBManager::instance().AsyncQuery(szQuery);
	return true;
}

bool CMonarch::DelCandidacy(const char * name)
{
	itertype(m_vec_MonarchCandidacy) it = m_vec_MonarchCandidacy.begin();
	for (; it != m_vec_MonarchCandidacy.end(); ++it)
	{
		if (0 == strncmp(it->name, name, sizeof(it->name)))
		{
			char szQuery[256];
			snprintf(szQuery, sizeof(szQuery),
					"DELETE FROM monarch_candidacy WHERE pid=%d ", it->pid);
			CDBManager::instance().AsyncQuery(szQuery);
		
			m_vec_MonarchCandidacy.erase (it);
			return true;
		}
	}
	return false;

}

bool CMonarch::IsMonarch(int32_t Empire, uint32_t pid)
{
	if (m_MonarchInfo.pid[Empire] != pid)
		return false;
	return true;
}

bool CMonarch::AddMoney(int32_t Empire, int64_t Money)
{
	if (m_MonarchInfo.money[Empire] + Money > 2000000000)
		return true;

	m_MonarchInfo.money[Empire] += Money;

	int64_t Money64 = m_MonarchInfo.money[Empire];

	char szQuery[1024];	
	snprintf(szQuery, sizeof(szQuery), "UPDATE monarch set money=%lld where empire=%d", Money64, Empire);

	CDBManager::instance().AsyncQuery(szQuery);

	return true;
}

bool CMonarch::DecMoney(int32_t Empire, int64_t Money)
{
	if (m_MonarchInfo.money[Empire] - Money <  0)
		return false;
	m_MonarchInfo.money[Empire] -= Money;

	int64_t Money64 = m_MonarchInfo.money[Empire];

	char szQuery[1024];	
	snprintf(szQuery, sizeof(szQuery), "UPDATE monarch set money=%lld where empire=%d", Money64, Empire);

	CDBManager::instance().AsyncQuery(szQuery);
	return true;
}

bool CMonarch::TakeMoney(int32_t Empire, uint32_t pid, int64_t Money)
{
	if (IsMonarch(Empire, pid) == false)
		return false;

	if (m_MonarchInfo.money[Empire] < Money)
		return false;
	
	m_MonarchInfo.money[Empire] -= Money;

	char szQuery[1024];	
	snprintf(szQuery, sizeof(szQuery), 
			"UPDATE monarch set money=%lld; where empire=%d", m_MonarchInfo.money[Empire], Empire);

	CDBManager::instance().AsyncQuery(szQuery);

	if (g_test_server)
		sys_log(0, "[MONARCH] Take money empire(%d) money(%lld)", Empire, m_MonarchInfo.money[Empire]);
	return true;
}

bool CMonarch::LoadMonarch()
{
	MonarchInfo * p = &m_MonarchInfo;
    char szQuery[256];
	snprintf(szQuery, sizeof(szQuery), "SELECT empire, pid, a.name, money, windate FROM monarch a, player%s b where a.pid=b.id", GetTablePostfix());
    SQLMsg * pMsg = CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER);

    if (pMsg->Get()->uiNumRows == 0)
    {
        delete pMsg;
        return false;
    }

    MYSQL_ROW row;
    for (int32_t n = 0; (row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL; ++n)
    {
        int32_t idx = 0;
        int32_t Empire = 0; str_to_number(Empire, row[idx++]);

        str_to_number(p->pid[Empire], row[idx++]);
		strlcpy(p->name[Empire], row[idx++], sizeof(p->name[Empire]));

        str_to_number(p->money[Empire], row[idx++]);
		strlcpy(p->date[Empire], row[idx++], sizeof(p->date[Empire]));

		if (g_test_server)
        	sys_log(0, "[LOAD_MONARCH] Empire %d pid %d money %lld windate %s", Empire, p->pid[Empire], p->money[Empire], p->date[Empire]);
    }

    delete pMsg;
    return true;
}

bool CMonarch::SetMonarch(const char * name)
{
	MonarchInfo * p = &m_MonarchInfo;
    char szQuery[256];

	snprintf(szQuery, sizeof(szQuery), "SELECT empire, pid, name FROM player a where a.name = '%s'", name);
    SQLMsg * pMsg = CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER);

    if (pMsg->Get()->uiNumRows == 0)
    {
        delete pMsg;
        return false;
    }

    MYSQL_ROW row;
	int32_t Empire = 0;
    for (int32_t n = 0; (row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL; ++n)
    {
        int32_t idx = 0;
        str_to_number(Empire, row[idx++]);

        str_to_number(p->pid[Empire], row[idx++]);
		strlcpy(p->name[Empire], row[idx++], sizeof(p->name[Empire]));
        p->money[Empire] = atoll(row[idx++]);
	
		if (g_test_server)
			sys_log(0, "[Set_MONARCH] Empire %d pid %d money %lld windate %s", Empire, p->pid[Empire], p->money[Empire], p->date[Empire]);
    }
    delete pMsg;

	//db¿¡ ÀÔ·Â
	snprintf(szQuery, sizeof(szQuery),
					"REPLACE INTO monarch (empire, name, windate, money) VALUES(%d, %d, now(), %lld)", Empire, p->pid[Empire], p->money[Empire]);

 	CDBManager::instance().AsyncQuery(szQuery, SQL_PLAYER);	
    return true;
}

bool CMonarch::DelMonarch(int32_t Empire)
{
	char szQuery[256];

	snprintf(szQuery, sizeof(szQuery), "DELETE from monarch where empire=%d", Empire);
	SQLMsg * pMsg = CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER);

	if (pMsg->Get()->uiNumRows == 0)
	{
		delete pMsg;
		return false;
	}

	delete pMsg;

	memset(m_MonarchInfo.name[Empire], 0, sizeof(m_MonarchInfo.name[Empire]));
	m_MonarchInfo.money[Empire] = 0;
	m_MonarchInfo.pid[Empire] = 0;
	return true;
}

bool CMonarch::DelMonarch(const char * name)
{
	for (int32_t n = 1; n < 4; ++n)
	{
		if (0 == strncmp(m_MonarchInfo.name[n], name, sizeof(m_MonarchInfo.name[n])))
		{
			char szQuery[256];

			int32_t Empire = n;
			snprintf(szQuery, sizeof(szQuery), "DELETE from monarch where name=%d", Empire);
			SQLMsg * pMsg = CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER);

			if (pMsg->Get()->uiNumRows == 0)
			{
				sys_err(" DirectQuery failed(%s)", szQuery);
				delete pMsg;
				return false;
			}

			delete pMsg;

			memset(m_MonarchInfo.name[Empire], 0, 32);
			m_MonarchInfo.money[Empire] = 0;
			m_MonarchInfo.pid[Empire] = 0;
			return true;
		}
	}
		
	return false;
}

int32_t CMonarch::GetCandidacyIndex(uint32_t pid)
{
	itertype(m_vec_MonarchCandidacy) it = m_vec_MonarchCandidacy.begin();

	for (int32_t n = 0; it != m_vec_MonarchCandidacy.end(); ++it, ++n)
	{
		if (it->pid == pid)
			return n;		
	}

	return -1;
}
