#include "stdafx.h"
#include "MoneyLog.h"
#include "ClientManager.h"
#include "Peer.h"

CMoneyLog::CMoneyLog()
{
}

CMoneyLog::~CMoneyLog()
{
}

void CMoneyLog::Save()
{
	CPeer* peer = CClientManager::instance().GetAnyPeer();
	if (!peer)
		return;
	for (uint8_t bType = 0; bType < MONEY_LOG_TYPE_MAX_NUM; bType ++)
	{
		__typeof(m_MoneyLogContainer[bType].begin()) it;
		for (it = m_MoneyLogContainer[bType].begin(); it != m_MoneyLogContainer[bType].end(); ++it)
		{
			//bType;
			TPacketMoneyLog p;
			p.type = bType;
			p.vnum = it->first;
			p.gold = it->second;
			peer->EncodeHeader(HEADER_DG_MONEY_LOG, 0, sizeof(p));
			peer->Encode(&p, sizeof(p));
		}
		m_MoneyLogContainer[bType].clear();
	}
	/*
	   CPeer* peer = GetPeer();

	   peer->

	   for (uint8_t bType = 0; bType < MONEY_LOG_TYPE_MAX_NUM; bType++)
	   {
	//"INSERT INTO money_log%s VALUES('%s', %d, %d, %d)", CClientManager::instance().GetTablePostfix(), 
	__typeof(m_MoneyLogContainer[bType].begin()) it;
	for (it = m_MoneyLogContainer[bType].begin(); it != m_MoneyLogContainer[bType].end(); ++it)
	{
	__typeof(it->second.begin()) 
	}
	}

	for (uint8_t bType = 0; bType < MONEY_LOG_TYPE_MAX_NUM; bType++)
	m_MoneyLogContainer[bType].clear()
	*/
}

void CMoneyLog::AddLog(uint8_t bType, uint32_t dwVnum, int32_t iGold)
{
	m_MoneyLogContainer[bType][dwVnum] += iGold;
}
