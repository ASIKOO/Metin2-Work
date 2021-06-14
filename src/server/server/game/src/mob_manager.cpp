#include "stdafx.h"
#include "char.h"
#include "char_manager.h"
#include "item_manager.h"
#include "mob_manager.h"
#include "regen.h"
#include "sectree.h"
#include "text_file_loader.h"
#include "questmanager.h"
#include "locale_service.h"

CMob::CMob()
{
	memset( &m_table, 0, sizeof(m_table) );

	for( uint32_t i=0 ; i < MOB_SKILL_MAX_NUM ; ++i )
	{
		m_mobSkillInfo[i].dwSkillVnum = 0;
		m_mobSkillInfo[i].bSkillLevel = 0;
		m_mobSkillInfo[i].vecSplashAttack.clear();
	}
}

CMob::~CMob()
{
}

void CMob::AddSkillSplash(int32_t iIndex, uint32_t dwTiming, uint32_t dwHitDistance)
{
	if (iIndex >= MOB_SKILL_MAX_NUM || iIndex < 0)
		return;

	sys_log(0, "MOB_SPLASH %s idx %d timing %u hit_distance %u",
			m_table.szLocaleName, iIndex, dwTiming, dwHitDistance);

	m_mobSkillInfo[iIndex].vecSplashAttack.push_back(TMobSplashAttackInfo(dwTiming, dwHitDistance));
}

CMobInstance::CMobInstance()
	: m_IsBerserk(false), m_IsGodSpeed(false), m_IsRevive(false)
{
	m_dwLastAttackedTime = get_dword_time();
	m_dwLastWarpTime = get_dword_time();

	memset( &m_posLastAttacked, 0, sizeof(m_posLastAttacked) );
}

CMobManager::CMobManager()
{
}

CMobManager::~CMobManager()
{
}

bool CMobManager::Initialize(TMobTable * pTable, int32_t iSize)
{
	m_map_pkMobByVnum.clear();
	m_map_pkMobByName.clear();

	TMobTable * t = pTable;


	for (int32_t i = 0; i < iSize; ++i, ++t)
	{
		CMob * pkMob = M2_NEW CMob;

		thecore_memcpy(&pkMob->m_table, t, sizeof(TMobTable));

		m_map_pkMobByVnum.insert(std::map<uint32_t, CMob *>::value_type(t->dwVnum, pkMob));
		m_map_pkMobByName.insert(std::map<std::string, CMob *>::value_type(t->szLocaleName, pkMob));

		int32_t SkillCount = 0;

		for (int32_t j = 0; j < MOB_SKILL_MAX_NUM; ++j)
			if (pkMob->m_table.Skills[j].dwVnum)
				++SkillCount;

		sys_log(0, "MOB: #%-5d %-30s LEVEL %u HP %u DEF %u EXP %u DROP_ITEM_VNUM %u SKILL_COUNT %d", 
				t->dwVnum, t->szLocaleName, t->bLevel, t->dwMaxHP, t->wDef, t->dwExp, t->dwDropItemVnum, SkillCount);

		if (t->bType == CHAR_TYPE_NPC || t->bType == CHAR_TYPE_WARP || t->bType == CHAR_TYPE_GOTO)
			CHARACTER_MANAGER::instance().RegisterRaceNum(t->dwVnum);

		quest::CQuestManager::instance().RegisterNPCVnum(t->dwVnum);
	}


	// LOCALE_SERVICE
	const int32_t FILE_NAME_LEN = 256;
	char szGroupFileName[FILE_NAME_LEN];
	char szGroupGroupFileName[FILE_NAME_LEN];

	snprintf(szGroupFileName, sizeof(szGroupGroupFileName),
			"%s/group.txt", LocaleService_GetBasePath().c_str());
	snprintf(szGroupGroupFileName, sizeof(szGroupGroupFileName),
			"%s/group_group.txt", LocaleService_GetBasePath().c_str());
	
	if (!LoadGroup(szGroupFileName))
	{
		sys_err("cannot load %s", szGroupFileName);
		thecore_shutdown();
	}
	if (!LoadGroupGroup(szGroupGroupFileName))
	{
		sys_err("cannot load %s", szGroupGroupFileName);
		thecore_shutdown();
	}
	// END_OF_LOCALE_SERVICE

	//exit(1);
	CHARACTER_MANAGER::instance().for_each_pc(std::bind(&CMobManager::RebindMobProto, this, std::placeholders::_1));
	return true;
}

void CMobManager::RebindMobProto(LPCHARACTER ch)
{
	if (ch->IsPC())
		return;

	const CMob * pMob = Get(ch->GetRaceNum());

	if (pMob)
		ch->SetProto(pMob);
}

const CMob * CMobManager::Get(uint32_t dwVnum)
{
	std::map<uint32_t, CMob *>::iterator it = m_map_pkMobByVnum.find(dwVnum);

	if (it == m_map_pkMobByVnum.end())
		return NULL;

	return it->second;
}

const CMob * CMobManager::Get(const char * c_pszName, bool bIsAbbrev)
{
	std::map<std::string, CMob *>::iterator it;

	if (!bIsAbbrev)
	{
		it = m_map_pkMobByName.find(c_pszName);

		if (it == m_map_pkMobByName.end())
			return NULL;

		return it->second;
	}

	int32_t len = strlen(c_pszName);
	it = m_map_pkMobByName.begin();

	while (it != m_map_pkMobByName.end())
	{
		if (!strncmp(it->first.c_str(), c_pszName, len))
			return it->second;

		++it;
	}

	return NULL;
}

void CMobManager::IncRegenCount(uint8_t bRegenType, uint32_t dwVnum, int32_t iCount, int32_t iTime)
{
	switch (bRegenType)
	{
		case REGEN_TYPE_MOB:
			m_mapRegenCount[dwVnum] += iCount * 86400. / iTime;
			break;

		case REGEN_TYPE_GROUP:
			{
				CMobGroup * pkGroup = CMobManager::Instance().GetGroup(dwVnum);
				if (!pkGroup)
					return;
				const std::vector<uint32_t> & c_rdwMembers = pkGroup->GetMemberVector();

				for (uint32_t i=0; i<c_rdwMembers.size(); i++)
					m_mapRegenCount[c_rdwMembers[i]] += iCount * 86400. / iTime;
			}
			break;

		case REGEN_TYPE_GROUP_GROUP:
			{
				std::map<uint32_t, CMobGroupGroup *>::iterator it = m_map_pkMobGroupGroup.find(dwVnum);

				if (it == m_map_pkMobGroupGroup.end())
					return;

				std::vector<uint32_t>& v = it->second->m_vec_dwMemberVnum;
				for (uint32_t i=0; i<v.size(); i++)
				{
					//m_mapRegenCount[v[i]] += iCount * 86400. / iTime / v.size();
					CMobGroup * pkGroup = CMobManager::Instance().GetGroup(v[i]);
					if (!pkGroup)
						return;
					const std::vector<uint32_t> & c_rdwMembers = pkGroup->GetMemberVector();

					for (uint32_t i=0; i<c_rdwMembers.size(); i++)
						m_mapRegenCount[c_rdwMembers[i]] += iCount * 86400. / iTime / v.size();
				}
			}
			break;
	}
}

void CMobManager::DumpRegenCount(const char* c_szFilename)
{
	FILE* fp = fopen(c_szFilename, "w");

	if (fp)
	{
		std::map<uint32_t, double>::iterator it;

		fprintf(fp,"MOB_VNUM\tCOUNT\n");

		for (it = m_mapRegenCount.begin(); it != m_mapRegenCount.end(); ++it)
		{
			fprintf(fp,"%u\t%g\n", it->first, it->second);
		}

		fclose(fp);
	}
}

uint32_t CMobManager::GetGroupFromGroupGroup(uint32_t dwVnum)
{
	std::map<uint32_t, CMobGroupGroup *>::iterator it = m_map_pkMobGroupGroup.find(dwVnum);

	if (it == m_map_pkMobGroupGroup.end())
		return 0;

	return it->second->GetMember();
}

CMobGroup * CMobManager::GetGroup(uint32_t dwVnum)
{
	std::map<uint32_t, CMobGroup *>::iterator it = m_map_pkMobGroup.find(dwVnum);

	if (it == m_map_pkMobGroup.end())
		return NULL;

	return it->second;
}

bool CMobManager::LoadGroupGroup(const char * c_pszFileName)
{
	CTextFileLoader loader;

	if (!loader.Load(c_pszFileName))
		return false;

	std::string stName;

	for (uint32_t i = 0; i < loader.GetChildNodeCount(); ++i)
	{
		loader.SetChildNode(i);

		loader.GetCurrentNodeName(&stName);

		int32_t iVnum;

		if (!loader.GetTokenInteger("vnum", &iVnum))
		{
			sys_err("LoadGroupGroup : Syntax error %s : no vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}

		TTokenVector * pTok;

		CMobGroupGroup * pkGroup = M2_NEW CMobGroupGroup(iVnum);

		for (int32_t k = 1; k < 256; ++k)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%d", k);

			if (loader.GetTokenVector(buf, &pTok))
			{
				uint32_t dwMobVnum = 0;
				str_to_number(dwMobVnum, pTok->at(0).c_str());

				// ADD_MOB_GROUP_GROUP_PROB
				int32_t prob = 1;
				if (pTok->size() > 1)
					str_to_number(prob, pTok->at(1).c_str());
				// END_OF_ADD_MOB_GROUP_GROUP_PROB

				if (dwMobVnum)
					pkGroup->AddMember(dwMobVnum);

				continue;
			}

			break;
		}

		loader.SetParentNode();

		m_map_pkMobGroupGroup.insert(std::make_pair((uint32_t)iVnum, pkGroup));
	}

	return true;
}

bool CMobManager::LoadGroup(const char * c_pszFileName)
{
	CTextFileLoader loader;

	if (!loader.Load(c_pszFileName))
		return false;

	std::string stName;

	for (uint32_t i = 0; i < loader.GetChildNodeCount(); ++i)
	{
		loader.SetChildNode(i);

		loader.GetCurrentNodeName(&stName);

		int32_t iVnum;

		if (!loader.GetTokenInteger("vnum", &iVnum))
		{
			sys_err("LoadGroup : Syntax error %s : no vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}

		TTokenVector * pTok;

		if (!loader.GetTokenVector("leader", &pTok))
		{
			sys_err("LoadGroup : Syntax error %s : no leader, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}

		if (pTok->size() < 2)
		{
			sys_err("LoadGroup : Syntax error %s : no leader vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}

		CMobGroup * pkGroup = M2_NEW CMobGroup;

		pkGroup->Create(iVnum, stName);
		uint32_t vnum = 0;
		str_to_number(vnum, pTok->at(1).c_str());
		pkGroup->AddMember(vnum);

		sys_log(0, "GROUP: %-5d %s", iVnum, stName.c_str());
		sys_log(0, "               %s %s", pTok->at(0).c_str(), pTok->at(1).c_str());

		for (int32_t k = 1; k < 256; ++k)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%d", k);

			if (loader.GetTokenVector(buf, &pTok))
			{
				sys_log(0, "               %s %s", pTok->at(0).c_str(), pTok->at(1).c_str());
				uint32_t vnum = 0;
				str_to_number(vnum, pTok->at(1).c_str());
				pkGroup->AddMember(vnum);
				continue;
			}

			break;
		}

		loader.SetParentNode();
		m_map_pkMobGroup.insert(std::map<uint32_t, CMobGroup *>::value_type(iVnum, pkGroup));
	}

	return true;
}

