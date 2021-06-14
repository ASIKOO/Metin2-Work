#include "stdafx.h"
#include "constants.h"
#include "monarch.h"
#include "char.h"
#include "sectree_manager.h"
#include "desc_client.h"
#include "dev_log.h"

extern int32_t test_server;
extern int32_t passes_per_sec;

CMonarch::CMonarch()
{
	memset( &m_MonarchInfo, 0, sizeof(m_MonarchInfo) );

	Initialize();
}

CMonarch::~CMonarch()
{
}

bool CMonarch::Initialize()
{
	memset(m_PowerUp, 0, sizeof(m_PowerUp));
	memset(m_DefenseUp, 0, sizeof(m_DefenseUp));
	memset(m_PowerUpCT, 0, sizeof(m_PowerUpCT));
	memset(m_DefenseUpCT, 0, sizeof(m_DefenseUpCT));

	return 0;
}

struct FHealMyEmpire 
{
	uint8_t m_bEmpire;
	void operator () (LPENTITY ent)
	{
		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER) ent;

			if (ch->IsPC() && m_bEmpire == ch->GetEmpire())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("군주가 내린 축복으로 모든 에너지가 가득 채워집니다"));
				ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
				ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
				ch->EffectPacket(SE_SPUP_BLUE);
				ch->EffectPacket(SE_HPUP_RED);
			}
		}
	}
};

int32_t CMonarch::HealMyEmpire(LPCHARACTER ch ,uint32_t price)
{
	uint8_t Empire = ch->GetEmpire();
	uint32_t pid = ch->GetPlayerID();

	sys_log(0, "HealMyEmpire[%d] pid:%d price %d", pid, Empire, price);

	if (IsMonarch(pid, Empire) == 0)
	{
		if (!ch->IsGM())
		{
			ch->ChatPacket(CHAT_TYPE_INFO ,LC_TEXT("군주의 자격을 가지고 있지 않습니다"));
			sys_err("No Monarch pid %d ", pid);
			return 0;
		}
	}

	if (!ch->IsMCOK(CHARACTER::MI_HEAL))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%d 초 후에 군주의 축복을 사용할 수 있습니다"), ch->GetMCLTime(CHARACTER::MI_HEAL));

		return 0;
	}

	if (!IsMoneyOk(price, Empire)) 
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("국고에 돈이 부족합니다. 현재 : %u 필요금액 : %u"), GetMoney(Empire), price);
		return 0;
	}

	int32_t iMapIndex = ch->GetMapIndex();

	FHealMyEmpire f;
	f.m_bEmpire = Empire;
	SECTREE_MANAGER::instance().for_each(iMapIndex, f);	

	// DB에 돈 삭감 보내기 
	SendtoDBDecMoney(price, Empire, ch);

	// 쿨타임 설정	
	ch->SetMC(CHARACTER::MI_HEAL);

	if (test_server)
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("[TEST_ONLY]현재 국고 : %d "), GetMoney(Empire) - price);
	return 1;
}

void CMonarch::SetMonarchInfo(TMonarchInfo * pInfo)
{
	memcpy(&m_MonarchInfo, pInfo, sizeof(TMonarchInfo));
}

bool CMonarch::IsMonarch(uint32_t pid, uint8_t bEmpire)
{
	if (bEmpire >= _countof(m_MonarchInfo.pid))
		return false;

	return (m_MonarchInfo.pid[bEmpire] == pid);
}

bool CMonarch::IsMoneyOk(int32_t price, uint8_t bEmpire)
{
	dev_log(LOG_DEB1, "GetMoney(%d), price = (%d,%d)", bEmpire, GetMoney(bEmpire), price);
	return (GetMoney(bEmpire) >= price);
}

bool CMonarch::SendtoDBAddMoney(int32_t Money, uint8_t bEmpire, LPCHARACTER ch)
{
	if (GetMoney(bEmpire) + Money > 2000000000)
		return false;

	if (GetMoney(bEmpire) + Money < 0)
		return false;

	int32_t nEmpire = bEmpire;	
	db_clientdesc->DBPacketHeader(HEADER_GD_ADD_MONARCH_MONEY, ch->GetDesc()->GetHandle(), sizeof(int32_t) + sizeof(int32_t));
	db_clientdesc->Packet(&nEmpire, sizeof(int32_t));	
	db_clientdesc->Packet(&Money, sizeof(int32_t));	
	return true;
}

bool CMonarch::SendtoDBDecMoney(int32_t Money, uint8_t bEmpire, LPCHARACTER ch)
{
	if (bEmpire >= _countof(m_MonarchInfo.money))
		return false;

	if (GetMoney(bEmpire) - Money < 0)
		return false;

	// 실제 줄이는 부분은 서버에 갔다 온 다음에 처리된다
	int32_t nEmpire = bEmpire;	

	db_clientdesc->DBPacketHeader(HEADER_GD_DEC_MONARCH_MONEY, ch->GetDesc()->GetHandle(), sizeof(int32_t) + sizeof(int32_t));
	db_clientdesc->Packet(&nEmpire, sizeof(int32_t));	
	db_clientdesc->Packet(&Money, sizeof(int32_t));	
	return true;
}

bool CMonarch::AddMoney(int32_t Money, uint8_t bEmpire)
{
	if (bEmpire >= _countof(m_MonarchInfo.money))
		return false;

	// 20억 이상 입금 불가능
	if (GetMoney(bEmpire) + Money > 2000000000)
		return false;

	m_MonarchInfo.money[bEmpire] += Money;
	return true;
}

bool CMonarch::DecMoney(int32_t Money, uint8_t bEmpire)
{
	if (bEmpire >= _countof(m_MonarchInfo.money))
		return false;

	if (GetMoney(bEmpire) - Money < 0)
		return false;

	m_MonarchInfo.money[bEmpire] -= Money;
	return true;
}

int32_t CMonarch::GetMoney(uint8_t bEmpire)
{
	if (bEmpire >= _countof(m_MonarchInfo.money))
		return 0;

	return m_MonarchInfo.money[bEmpire];
}

TMonarchInfo* CMonarch::GetMonarch()
{
	return &m_MonarchInfo;
}

uint32_t CMonarch::GetMonarchPID(uint8_t Empire)
{
	return Empire < _countof(m_MonarchInfo.pid) ? m_MonarchInfo.pid[Empire] : 0;
}

bool CMonarch::IsPowerUp(uint8_t Empire)
{
	return Empire < _countof(m_PowerUp) ? m_PowerUp[Empire] : false;
}

bool CMonarch::IsDefenceUp(uint8_t Empire)
{
	return Empire < _countof(m_DefenseUp) ? m_DefenseUp[Empire] : false;
}

bool CMonarch::CheckPowerUpCT(uint8_t Empire)
{
	if (Empire >= _countof(m_PowerUpCT))
		return false;

	if (m_PowerUpCT[Empire] > thecore_pulse())
	{
		if (test_server)
			sys_log(0, "[TEST_ONLY] : CheckPowerUpCT CT%d Now%d 60sec %d", m_PowerUpCT[Empire], thecore_pulse(), PASSES_PER_SEC(60 * 10));
		return false;
	}

	return true;
}

bool CMonarch::CheckDefenseUpCT(uint8_t Empire)
{
	if (Empire >= _countof(m_DefenseUpCT))
		return false;

	if (m_DefenseUpCT[Empire] > thecore_pulse())
	{
		if (test_server)
			sys_log(0, "[TEST_ONLY] : CheckPowerUpCT CT%d Now%d 60sec %d", m_PowerUpCT[Empire], thecore_pulse(), PASSES_PER_SEC(60 * 10));
		return false;
	}

	return true;
}

void CMonarch::PowerUp(uint8_t Empire, bool On)
{
	if (Empire >= _countof(m_PowerUpCT))
		return;

	m_PowerUp[Empire] = On;

	// 군주 사자후 쿨타임 
	m_PowerUpCT[Empire] = thecore_pulse() + PASSES_PER_SEC(60 * 10);
}

void CMonarch::DefenseUp(uint8_t Empire, bool On)
{
	if (Empire >= _countof(m_DefenseUpCT))
		return;

	m_DefenseUp[Empire] = On;

	// 군주 금강권 쿨타임 
	m_DefenseUpCT[Empire] = thecore_pulse() + PASSES_PER_SEC(60 * 10);
}

bool IsMonarchWarpZone (int32_t map_idx)
{
	// 아귀동굴, 천의동굴.
	if (map_idx >= 10000)
		map_idx /= 10000;

	switch (map_idx)
	{
	case 301:
	case 302:
	case 303:
	case 304:
		//던전
	case 351: // 적룡성
	case 352: // 백룡지성
		return false;
	}

	return (map_idx != 208 && map_idx != 216 && map_idx != 217);
}