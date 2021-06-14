#ifndef __INC_LOG_MANAGER_H__
#define __INC_LOG_MANAGER_H__

#include "../../libsql/AsyncSQL.h"
#include "any_function.h"

enum GOLDBAR_HOW
{
	PERSONAL_SHOP_BUY	= 1 ,
	PERSONAL_SHOP_SELL	= 2 ,
	SHOP_BUY			= 3 ,
	SHOP_SELL			= 4 ,
	EXCHANGE_TAKE		= 5 ,
	EXCHANGE_GIVE		= 6 ,
	QUEST				= 7 ,
};

class LogManager : public singleton<LogManager>
{
	public:
		LogManager();
		virtual ~LogManager();

		bool		IsConnected();

		bool		Connect(const char * host, const int32_t port, const char * user, const char * pwd, const char * db);

		void		ItemLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t dwItemID, const char * c_pszText, const char * c_pszHint, const char * c_pszIP, uint32_t dwVnum);
		void		ItemLog(LPCHARACTER ch, LPITEM item, const char * c_pszText, const char * c_pszHint);
		void		ItemLog(LPCHARACTER ch, int32_t itemID, int32_t itemVnum, const char * c_pszText, const char * c_pszHint);

		void		CharLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t dw, const char * c_pszText, const char * c_pszHint, const char * c_pszIP);
		void		CharLog(LPCHARACTER ch, uint32_t dw, const char * c_pszText, const char * c_pszHint);

		void		LoginLog(bool isLogin, uint32_t dwAccountID, uint32_t dwPID, uint8_t bLevel, uint8_t bJob, uint32_t dwPlayTime);
		void		MoneyLog(uint8_t type, uint32_t vnum, int32_t gold);
		void		HackLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP);
		void		HackLog(const char * c_pszHackName, LPCHARACTER ch);
		void		HackCRCLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP, uint32_t dwCRC);
		void		GoldBarLog(uint32_t dwPID, uint32_t dwItemID, GOLDBAR_HOW eHow, const char * c_pszHint);
		void		PCBangLoginLog(uint32_t dwPCBangID, const char * c_szPCBangIP, uint32_t dwPlayerID, uint32_t dwPlayTime);
		void		CubeLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t item_vnum, uint32_t item_uid, int32_t item_count, bool success);
		void		GMCommandLog(uint32_t dwPID, const char * szName, const char * szIP, uint8_t byChannel, const char * szCommand);
		void		SpeedHackLog(uint32_t pid, uint32_t x, uint32_t y, int32_t hack_count);
		void		ChangeNameLog(uint32_t pid, const char * old_name, const char * new_name, const char * ip);
		void		RefineLog(uint32_t pid, const char * item_name, uint32_t item_id, int32_t item_refine_level, int32_t is_success, const char * how);
		void		ShoutLog(uint8_t bChannel, uint8_t bEmpire, const char * pszText);
		void		LevelLog(LPCHARACTER pChar, uint32_t level, uint32_t playhour);
		void		BootLog(const char * c_pszHostName, uint8_t bChannel);
		void		VCardLog(uint32_t vcard_id, uint32_t x, uint32_t y, const char * hostname, const char * giver_name, const char * giver_ip, const char * taker_name, const char * taker_ip);
		void		FishLog(uint32_t dwPID, int32_t prob_idx, int32_t fish_id, int32_t fish_level, uint32_t dwMiliseconds, uint32_t dwVnum = false, uint32_t dwValue = 0);
		void		QuestRewardLog(const char * c_pszQuestName, uint32_t dwPID, uint32_t dwLevel, int32_t iValue1, int32_t iValue2);
		void		DetailLoginLog(bool isLogin, LPCHARACTER ch);
		void		DragonSlayLog(uint32_t dwGuildID, uint32_t dwDragonVnum, uint32_t dwStartTime, uint32_t dwEndTime);
		//void		HackShieldLog(uint32_t ErrorCode, LPCHARACTER ch);

	private:
		void		Query(const char * c_pszFormat, ...);

		CAsyncSQL	m_sql;
		bool		m_bIsConnect;
};

#endif
