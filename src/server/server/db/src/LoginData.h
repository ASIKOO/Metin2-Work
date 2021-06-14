// vim:ts=8 sw=4
#ifndef __INC_METIN_II_DB_LOGINDATA_H__
#define __INC_METIN_II_DB_LOGINDATA_H__

class CLoginData
{
    public:
	CLoginData();

	TAccountTable & GetAccountRef();
	void            SetClientKey(const uint32_t * c_pdwClientKey);

	const uint32_t *   GetClientKey();
	void            SetKey(uint32_t dwKey);
	uint32_t           GetKey();

	void            SetConnectedPeerHandle(uint32_t dwHandle);
	uint32_t		GetConnectedPeerHandle();

	void            SetLogonTime();
	uint32_t		GetLogonTime();

	void		SetIP(const char * c_pszIP);
	const char *	GetIP();

	void		SetPlay(bool bOn);
	bool		IsPlay();

	void		SetDeleted(bool bSet);
	bool		IsDeleted();

	void		SetBillID(uint32_t id) { m_dwBillID = id; }
	uint32_t		GetBillID() { return m_dwBillID; }

	void		SetBillType(uint8_t type) { m_bBillType = type; }
	uint8_t		GetBillType() { return m_bBillType; }

	int32_t		GetLastPlayTime() { return m_lastPlayTime; }

	void            SetPremium(int32_t * paiPremiumTimes);
	int32_t             GetPremium(uint8_t type);
	int32_t *           GetPremiumPtr();

	uint32_t		GetLastPlayerID() const { return m_dwLastPlayerID; }
	void		SetLastPlayerID(uint32_t id) { m_dwLastPlayerID = id; }

    private:
	uint32_t           m_dwKey;
	uint32_t           m_adwClientKey[4];
	uint32_t           m_dwConnectedPeerHandle;
	uint32_t           m_dwLogonTime;
	char		m_szIP[MAX_HOST_LENGTH+1];
	bool		m_bPlay;
	bool		m_bDeleted;

	uint8_t		m_bBillType;
	uint32_t		m_dwBillID;
	int32_t		m_lastPlayTime;
	int32_t		m_aiPremiumTimes[PREMIUM_MAX_NUM];

	uint32_t		m_dwLastPlayerID;

	TAccountTable   m_data;
};

#endif
