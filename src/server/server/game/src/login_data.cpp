#include "stdafx.h"
#include "constants.h"
#include "login_data.h"

extern std::string g_stBlockDate; 

CLoginData::CLoginData()
{
	m_dwKey = 0;
	memset(m_adwClientKey, 0, sizeof(m_adwClientKey));
	m_bBillType = 0;
	m_dwBillID = 0;
	m_dwConnectedPeerHandle = 0;
	m_dwLogonTime = 0;
	m_lRemainSecs = 0;
	memset(m_szIP, 0, sizeof(m_szIP));
	m_bBilling = false;
	m_bDeleted = false;
	memset(m_aiPremiumTimes, 0, sizeof(m_aiPremiumTimes));
}

void CLoginData::SetClientKey(const uint32_t * c_pdwClientKey)
{
	thecore_memcpy(&m_adwClientKey, c_pdwClientKey, sizeof(uint32_t) * 4);
}

const uint32_t * CLoginData::GetClientKey()
{
	return &m_adwClientKey[0];
}

void CLoginData::SetKey(uint32_t dwKey)
{
	m_dwKey = dwKey;
}

uint32_t CLoginData::GetKey()
{
	return m_dwKey;
}

void CLoginData::SetBillType(uint8_t bType)
{
	m_bBillType = bType;
}

uint32_t CLoginData::GetBillID() 
{
	return m_dwBillID;
}

void CLoginData::SetBillID(uint32_t dwID)
{
	m_dwBillID = dwID;
}

uint8_t CLoginData::GetBillType()
{
	return m_bBillType;
}

void CLoginData::SetConnectedPeerHandle(uint32_t dwHandle)
{
	m_dwConnectedPeerHandle = dwHandle;
}

uint32_t CLoginData::GetConnectedPeerHandle()
{
	return m_dwConnectedPeerHandle;
}

void CLoginData::SetLogonTime()
{
	m_dwLogonTime = get_dword_time();
}

uint32_t CLoginData::GetLogonTime()
{
	return m_dwLogonTime;
}

void CLoginData::SetIP(const char * c_pszIP)
{
	strlcpy(m_szIP, c_pszIP, sizeof(m_szIP));
}

const char * CLoginData::GetIP()
{
	return m_szIP;
}

void CLoginData::SetRemainSecs(int32_t l)
{
	m_lRemainSecs = l;
	sys_log(0, "SetRemainSecs %s %d type %u", m_stLogin.c_str(), m_lRemainSecs, m_bBillType);
}

int32_t CLoginData::GetRemainSecs()
{
	return m_lRemainSecs;
}

void CLoginData::SetBilling(bool bOn)
{
	if (bOn)
	{
		sys_log(0, "BILLING: ON %s key %u ptr %p", m_stLogin.c_str(), m_dwKey, this);
		SetLogonTime();
	}
	else
		sys_log(0, "BILLING: OFF %s key %u ptr %p", m_stLogin.c_str(), m_dwKey, this);

	m_bBilling = bOn;
}

bool CLoginData::IsBilling()
{
	return m_bBilling;
}

void CLoginData::SetDeleted(bool bSet)
{
	m_bDeleted = bSet;
}

bool CLoginData::IsDeleted()
{
	return m_bDeleted;
}

void CLoginData::SetLogin(const char * c_pszLogin)
{
	m_stLogin = c_pszLogin;
}

const char * CLoginData::GetLogin()
{
	return m_stLogin.c_str();
}

void CLoginData::SetPremium(int32_t * paiPremiumTimes)
{
	thecore_memcpy(m_aiPremiumTimes, paiPremiumTimes, sizeof(m_aiPremiumTimes));
}

int32_t CLoginData::GetPremium(uint8_t type)
{
	if (type >= PREMIUM_MAX_NUM)
		return 0;

	return m_aiPremiumTimes[type];
}

int32_t * CLoginData::GetPremiumPtr()
{
	return &m_aiPremiumTimes[0];
}

