#include "stdafx.h"
#include "PrivManager.h"
#include "ClientManager.h"

const int32_t PRIV_DURATION = 60*60*12;
const int32_t CHARACTER_GOOD_PRIV_DURATION = 2*60*60;
const int32_t CHARACTER_BAD_PRIV_DURATION = 60*60;

CPrivManager::CPrivManager()
{
	for (int32_t type = 0; type < MAX_PRIV_NUM; ++type)
	{
		for (int32_t empire = 0; empire < EMPIRE_MAX_NUM; ++empire)
			m_aaPrivEmpire[type][empire] = 0;
	}
}

CPrivManager::~CPrivManager()
{
}

//
// @version 05/06/07	Bang2ni - �ߺ������� ���ʽ��� ���� �� ��忡 ���� ó��
//
void CPrivManager::Update()
{
	int32_t now = CClientManager::instance().GetCurrentTime();

	while (!m_pqPrivGuild.empty() && m_pqPrivGuild.top().first <= now)
	{
		TPrivGuildData* p = m_pqPrivGuild.top().second;
		m_pqPrivGuild.pop();

		if (p->value != 0 && !p->bRemoved)
		{

			__typeof(m_aPrivGuild[p->type].begin()) it = m_aPrivGuild[p->type].find(p->guild_id);

			// ADD_GUILD_PRIV_TIME
			// ��忡 �ߺ������� ���ʽ��� �����Ǿ��� ��� map �� value �� ����(����) �Ǿ����Ƿ�
			// TPrivGuildData �� �����Ͱ� ������ ������ ������ �ְ� ���Ӽ����鿡�� cast �� �ش�.
			if (it != m_aPrivGuild[p->type].end() && it->second == p) {
				m_aPrivGuild[p->type].erase(it);
				SendChangeGuildPriv(p->guild_id, p->type, 0, 0);
				// END_OF_ADD_GUILD_PRIV_TIME
			}
		}

		delete p;
	}

	while (!m_pqPrivEmpire.empty() && m_pqPrivEmpire.top().first <= now)
	{
		TPrivEmpireData* p = (m_pqPrivEmpire.top().second);
		m_pqPrivEmpire.pop();

		if (p->value != 0 && !p->bRemoved)
		{
			SendChangeEmpirePriv(p->empire, p->type, 0, 0);
			m_aaPrivEmpire[p->type][p->empire] = 0;
		}

		delete p;
	}

	while (!m_pqPrivChar.empty() && m_pqPrivChar.top().first <= now)
	{
		TPrivCharData* p = (m_pqPrivChar.top().second);
		m_pqPrivChar.pop();

		if (!p->bRemoved)
		{
			// TODO send packet
			SendChangeCharPriv(p->pid, p->type, 0);
			__typeof(m_aPrivChar[p->type].begin()) it = m_aPrivChar[p->type].find(p->pid);
			if (it != m_aPrivChar[p->type].end())
				m_aPrivChar[p->type].erase(it);
		}
		delete p;
	}
}

void CPrivManager::AddCharPriv(uint32_t pid, uint8_t type, int32_t value)
{
	if (MAX_PRIV_NUM <= type)
	{
		sys_err("PRIV_MANAGER: AddCharPriv: wrong char priv type(%u) recved", type);
		return;
	}

	__typeof(m_aPrivChar[type].begin()) it = m_aPrivChar[type].find(pid);

	if (it != m_aPrivChar[type].end())
		return;

	if (!value)
		return;

	int32_t now = CClientManager::instance().GetCurrentTime();
	TPrivCharData* p = new TPrivCharData(type, value, pid);

	int32_t iDuration = CHARACTER_BAD_PRIV_DURATION;

	if (value > 0)
		iDuration = CHARACTER_GOOD_PRIV_DURATION;

	m_pqPrivChar.push(std::make_pair(now+iDuration, p));
	m_aPrivChar[type].insert(std::make_pair(pid, p));

	// TODO send packet
	sys_log(0, "AddCharPriv %d %d %d", pid, type, value);
	SendChangeCharPriv(pid, type, value);
}

//
// @version 05/06/07	Bang2ni - �̹� ���ʽ��� ���� �� ��忡 ���ʽ� ����
//
void CPrivManager::AddGuildPriv(uint32_t guild_id, uint8_t type, int32_t value, int32_t duration_sec)
{
	if (MAX_PRIV_NUM <= type)
	{
		sys_err("PRIV_MANAGER: AddGuildPriv: wrong guild priv type(%u) recved", type);
		return;
	}

	__typeof(m_aPrivGuild[type].begin()) it = m_aPrivGuild[type].find(guild_id);

	int32_t now = CClientManager::instance().GetCurrentTime();
	int32_t end = now + duration_sec;
	TPrivGuildData * p = new TPrivGuildData(type, value, guild_id, end);
	m_pqPrivGuild.push(std::make_pair(end, p));

	// ADD_GUILD_PRIV_TIME
	// �̹� ���ʽ��� ������ �ִٸ� map �� value �� ������ �ش�.
	// ���� value �� �����ʹ� priority queue ���� ������ �� �����ȴ�.
	if (it != m_aPrivGuild[type].end())
		it->second = p;
	else
		m_aPrivGuild[type].insert(std::make_pair(guild_id, p));

	SendChangeGuildPriv(guild_id, type, value, end);
	// END_OF_ADD_GUILD_PRIV_TIME

	sys_log(0, "Guild Priv guild(%d) type(%d) value(%d) duration_sec(%d)", guild_id, type, value, duration_sec);
}

void CPrivManager::AddEmpirePriv(uint8_t empire, uint8_t type, int32_t value, int32_t duration_sec)
{
	if (MAX_PRIV_NUM <= type)
	{
		sys_err("PRIV_MANAGER: AddEmpirePriv: wrong empire priv type(%u) recved", type);
		return;
	}

	if (duration_sec < 0)
		duration_sec = 0;

	int32_t now = CClientManager::instance().GetCurrentTime();
	int32_t end = now+duration_sec;

	// ���� ������ ��ȿȭ
	// priority_queue�� ����ִ� pointer == m_aaPrivEmpire[type][empire]
	{
		if (m_aaPrivEmpire[type][empire])
			m_aaPrivEmpire[type][empire]->bRemoved = true;
	}

	TPrivEmpireData * p = new TPrivEmpireData(type, value, empire, end);
	m_pqPrivEmpire.push(std::make_pair(end, p));
	m_aaPrivEmpire[type][empire] = p;

	// ADD_EMPIRE_PRIV_TIME
	SendChangeEmpirePriv(empire, type, value, end);
	// END_OF_ADD_EMPIRE_PRIV_TIME

	sys_log(0, "Empire Priv empire(%d) type(%d) value(%d) duration_sec(%d)", empire, type, value, duration_sec);
}

/**
 * @version 05/06/08	Bang2ni - ���ӽð� �߰�
 */
struct FSendChangeGuildPriv
{
	FSendChangeGuildPriv(uint32_t guild_id, uint8_t type, int32_t value, int32_t end_time_sec)
	{
		p.guild_id = guild_id;
		p.type = type;
		p.value = value;
		p.bLog = 1;
		// ADD_GUILD_PRIV_TIME
		p.end_time_sec = end_time_sec;
		// END_OF_ADD_GUILD_PRIV_TIME
	}

	void operator() (CPeer* peer)
	{
		peer->EncodeHeader(HEADER_DG_CHANGE_GUILD_PRIV, 0, sizeof(TPacketDGChangeGuildPriv));
		peer->Encode(&p, sizeof(TPacketDGChangeGuildPriv));
		p.bLog = 0;
	}

	TPacketDGChangeGuildPriv p;
};

struct FSendChangeEmpirePriv
{
	FSendChangeEmpirePriv(uint8_t empire, uint8_t type, int32_t value, int32_t end_time_sec)
	{
		p.empire = empire;
		p.type = type;
		p.value = value;
		p.bLog = 1;
		// ADD_EMPIRE_PRIV_TIME
		p.end_time_sec = end_time_sec;
		// END_OF_ADD_EMPIRE_PRIV_TIME
	}

	void operator ()(CPeer* peer)
	{
		peer->EncodeHeader(HEADER_DG_CHANGE_EMPIRE_PRIV, 0, sizeof(TPacketDGChangeEmpirePriv));
		peer->Encode(&p, sizeof(TPacketDGChangeEmpirePriv));
		p.bLog = 0;
	}

	TPacketDGChangeEmpirePriv p;
};

struct FSendChangeCharPriv
{
	FSendChangeCharPriv(uint32_t pid, uint8_t type, int32_t value)
	{
		p.pid = pid;
		p.type = type;
		p.value = value;
		p.bLog = 1;
	}
	void operator()(CPeer* peer)
	{
		peer->EncodeHeader(HEADER_DG_CHANGE_CHARACTER_PRIV, 0, sizeof(TPacketDGChangeCharacterPriv));
		peer->Encode(&p, sizeof(TPacketDGChangeCharacterPriv));
		p.bLog = 0;
	}
	TPacketDGChangeCharacterPriv p;
};

// ADD_GUILD_PRIV_TIME
void CPrivManager::SendChangeGuildPriv(uint32_t guild_id, uint8_t type, int32_t value, int32_t end_time_sec)
{
	CClientManager::instance().for_each_peer(FSendChangeGuildPriv(guild_id, type, value, end_time_sec));
}
// END_OF_ADD_GUILD_PRIV_TIME

// ADD_EMPIRE_PRIV_TIME
void CPrivManager::SendChangeEmpirePriv(uint8_t empire, uint8_t type, int32_t value, int32_t end_time_sec)
{
	CClientManager::instance().for_each_peer(FSendChangeEmpirePriv(empire, type, value, end_time_sec));
}
// END_OF_ADD_EMPIRE_PRIV_TIME

void CPrivManager::SendChangeCharPriv(uint32_t pid, uint8_t type, int32_t value)
{
	CClientManager::instance().for_each_peer(FSendChangeCharPriv(pid, type, value));
}

void CPrivManager::SendPrivOnSetup(CPeer* peer)
{
	for (int32_t i = 1; i < MAX_PRIV_NUM; ++i)
	{
		for (int32_t e = 0; e < EMPIRE_MAX_NUM; ++e)
		{
			// ADD_EMPIRE_PRIV_TIME
			TPrivEmpireData* pPrivEmpireData = m_aaPrivEmpire[i][e];
			if (pPrivEmpireData)
			{
				FSendChangeEmpirePriv(e, i, pPrivEmpireData->value, pPrivEmpireData->end_time_sec)(peer);
			}
			// END_OF_ADD_EMPIRE_PRIV_TIME
		}

		for (__typeof(m_aPrivGuild[i].begin()) it = m_aPrivGuild[i].begin(); it != m_aPrivGuild[i].end();++it)
		{
			// ADD_GUILD_PRIV_TIME
			FSendChangeGuildPriv(it->first, i, it->second->value, it->second->end_time_sec)(peer);
			// END_OF_ADD_GUILD_PRIV_TIME
		}
		for (__typeof(m_aPrivChar[i].begin()) it = m_aPrivChar[i].begin(); it != m_aPrivChar[i].end(); ++it)
		{
			FSendChangeCharPriv(it->first, i, it->second->value)(peer);
		}
	}
}
