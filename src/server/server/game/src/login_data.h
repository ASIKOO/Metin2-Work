#ifndef __INC_METIN_II_LOGIN_DATA_H__
#define __INC_METIN_II_LOGIN_DATA_H__

class CLoginData
{
	public:
		CLoginData();

		void            SetClientKey(const uint32_t * c_pdwClientKey);

		const uint32_t *   GetClientKey();
		void            SetKey(uint32_t dwKey);
		uint32_t           GetKey();

		void		SetLogin(const char * c_pszLogin);
		const char *	GetLogin();

		void            SetBillType(uint8_t bType);
		uint32_t           GetBillID();

		void            SetBillID(uint32_t dwID);
		uint8_t            GetBillType();

		void            SetConnectedPeerHandle(uint32_t dwHandle);
		uint32_t		GetConnectedPeerHandle();

		void            SetLogonTime();
		uint32_t		GetLogonTime();

		void		SetIP(const char * c_pszIP);
		const char *	GetIP();

		void		SetRemainSecs(int32_t l);
		int32_t		GetRemainSecs();

		void		SetBilling(bool bOn);
		bool		IsBilling();

		void		SetDeleted(bool bSet);
		bool		IsDeleted();

		void		SetPremium(int32_t * paiPremiumTimes);
		int32_t		GetPremium(uint8_t type);
		int32_t *		GetPremiumPtr();


	private:
		uint32_t           m_dwKey;
		uint32_t           m_adwClientKey[4];
		uint8_t            m_bBillType;
		uint32_t           m_dwBillID;
		uint32_t           m_dwConnectedPeerHandle;
		uint32_t           m_dwLogonTime;
		int32_t		m_lRemainSecs;
		char		m_szIP[MAX_HOST_LENGTH+1];
		bool		m_bBilling;
		bool		m_bDeleted;
		std::string	m_stLogin;
		int32_t		m_aiPremiumTimes[PREMIUM_MAX_NUM];

		
		
};

#endif
