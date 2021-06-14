#ifndef __INC_METIN_II_GAME_DESC_MANAGER_H__
#define __INC_METIN_II_GAME_DESC_MANAGER_H__

#include <boost/unordered_map.hpp>

#include "../../common/stl.h"
#include "../../common/length.h"
#include "IFileMonitor.h"

class CLoginKey;
class CClientPackageCryptInfo;

class DESC_MANAGER : public singleton<DESC_MANAGER>
{
	public:
		typedef std::unordered_set<LPDESC>			DESC_SET;
		typedef std::unordered_set<LPCLIENT_DESC>	CLIENT_DESC_SET;
		typedef std::map<int32_t, LPDESC>					DESC_HANDLE_MAP;
		typedef std::map<uint32_t, LPDESC>					DESC_HANDSHAKE_MAP;
		typedef std::map<uint32_t, LPDESC>					DESC_ACCOUNTID_MAP;
		typedef boost::unordered_map<std::string, LPDESC>	DESC_LOGINNAME_MAP;
		typedef std::map<uint32_t, uint32_t>					DESC_HANDLE_RANDOM_KEY_MAP;

	public:
		DESC_MANAGER();
		virtual ~DESC_MANAGER();

		void			Initialize();
		void			Destroy();

		LPDESC			AcceptDesc(LPFDWATCH fdw, socket_t s);
		LPDESC			AcceptP2PDesc(LPFDWATCH fdw, socket_t s);
		void			DestroyDesc(LPDESC d, bool erase_from_set = true);

		uint32_t			CreateHandshake();

		LPCLIENT_DESC		CreateConnectionDesc(LPFDWATCH fdw, const char * host, uint16_t port, int32_t iPhaseWhenSucceed, bool bRetryWhenClosed);
		void			TryConnect();

		LPDESC			FindByHandle(uint32_t handle);
		LPDESC			FindByHandshake(uint32_t dwHandshake);

		LPDESC			FindByCharacterName(const char* name);
		LPDESC			FindByLoginName(const std::string& login);
		void			ConnectAccount(const std::string& login, LPDESC d);
		void			DisconnectAccount(const std::string& login);

		void			DestroyClosed();

		void			UpdateLocalUserCount();
		uint32_t			GetLocalUserCount() { return m_iLocalUserCount; }
		void			GetUserCount(int32_t & iTotal, int32_t ** paiEmpireUserCount, int32_t & iLocalCount);

		const DESC_SET &	GetClientSet();

		uint32_t			MakeRandomKey(uint32_t dwHandle);
		bool			GetRandomKey(uint32_t dwHandle, uint32_t* prandom_key);

		uint32_t			CreateLoginKey(LPDESC d);
		LPDESC			FindByLoginKey(uint32_t dwKey);
		void			ProcessExpiredLoginKey();

		bool			IsDisconnectInvalidCRC() { return m_bDisconnectInvalidCRC; }
		void			SetDisconnectInvalidCRCMode(bool bMode) { m_bDisconnectInvalidCRC = bMode; }

		bool			IsP2PDescExist(const char * szHost, uint16_t wPort);

		// for C/S hybrid crypt
		bool			LoadClientPackageCryptInfo(const char* pDirName);
		void			SendClientPackageCryptKey( LPDESC desc );
		void			SendClientPackageSDBToLoadMap( LPDESC desc, const char* pMapName );
#ifdef __FreeBSD__
		static void		NotifyClientPackageFileChanged( const std::string& fileName, eFileUpdatedOptions eUpdateOption );
#endif 

	private:
		bool				m_bDisconnectInvalidCRC;

		DESC_HANDLE_RANDOM_KEY_MAP	m_map_handle_random_key;

		CLIENT_DESC_SET		m_set_pkClientDesc;
		DESC_SET			m_set_pkDesc;

		DESC_HANDLE_MAP			m_map_handle;
		DESC_HANDSHAKE_MAP		m_map_handshake;
		//DESC_ACCOUNTID_MAP		m_AccountIDMap;
		DESC_LOGINNAME_MAP		m_map_loginName;
		std::map<uint32_t, CLoginKey *>	m_map_pkLoginKey;

		int32_t				m_iSocketsConnected;

		int32_t				m_iHandleCount;

		int32_t				m_iLocalUserCount;
		int32_t				m_aiEmpireUserCount[EMPIRE_MAX_NUM];

		bool			m_bDestroyed;

		CClientPackageCryptInfo*	m_pPackageCrypt;
};

#endif
