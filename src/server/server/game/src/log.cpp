#include "stdafx.h"
#include "constants.h"
#include "config.h"
#include "log.h"

#include "char.h"
#include "desc.h"
#include "item.h"
#include "locale_service.h"

static char	__escape_hint[1024];

LogManager::LogManager() : m_bIsConnect(false)
{
}

LogManager::~LogManager()
{
}

bool LogManager::Connect(const char * host, const int32_t port, const char * user, const char * pwd, const char * db)
{
	if (m_sql.Setup(host, user, pwd, db, g_stLocale.c_str(), false, port))
		m_bIsConnect = true;

	return m_bIsConnect;
}

void LogManager::Query(const char * c_pszFormat, ...)
{
	char szQuery[4096];
	va_list args;

	va_start(args, c_pszFormat);
	vsnprintf(szQuery, sizeof(szQuery), c_pszFormat, args);
	va_end(args);

	if (test_server)
		sys_log(0, "LOG: %s", szQuery);

	m_sql.AsyncQuery(szQuery);
}

bool LogManager::IsConnected()
{
	return m_bIsConnect;
}

void LogManager::ItemLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t dwItemID, const char * c_pszText, const char * c_pszHint, const char * c_pszIP, uint32_t dwVnum)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), c_pszHint, strlen(c_pszHint));

	Query("INSERT DELAYED INTO log%s (type, time, who, x, y, what, how, hint, ip, vnum) VALUES('ITEM', NOW(), %u, %u, %u, %u, '%s', '%s', '%s', %u)",
			get_table_postfix(), dwPID, x, y, dwItemID, c_pszText, __escape_hint, c_pszIP, dwVnum);
}

void LogManager::ItemLog(LPCHARACTER ch, LPITEM item, const char * c_pszText, const char * c_pszHint)
{
	if (NULL == ch || NULL == item)
	{
		sys_err("character or item nil (ch %p item %p text %s)", get_pointer(ch), get_pointer(item), c_pszText);
		return;
	}

	ItemLog(ch->GetPlayerID(), ch->GetX(), ch->GetY(), item->GetID(),
			NULL == c_pszText ? "" : c_pszText,
		   	c_pszHint, ch->GetDesc() ? ch->GetDesc()->GetHostName() : "",
		   	item->GetOriginalVnum());
}

void LogManager::ItemLog(LPCHARACTER ch, int32_t itemID, int32_t itemVnum, const char * c_pszText, const char * c_pszHint)
{
	ItemLog(ch->GetPlayerID(), ch->GetX(), ch->GetY(), itemID, c_pszText, c_pszHint, ch->GetDesc() ? ch->GetDesc()->GetHostName() : "", itemVnum);
}

void LogManager::CharLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t dwValue, const char * c_pszText, const char * c_pszHint, const char * c_pszIP)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), c_pszHint, strlen(c_pszHint));

	Query("INSERT DELAYED INTO log%s (type, time, who, x, y, what, how, hint, ip) VALUES('CHARACTER', NOW(), %u, %u, %u, %u, '%s', '%s', '%s')",
			get_table_postfix(), dwPID, x, y, dwValue, c_pszText, __escape_hint, c_pszIP);
}

void LogManager::CharLog(LPCHARACTER ch, uint32_t dw, const char * c_pszText, const char * c_pszHint)
{
	if (ch)
		CharLog(ch->GetPlayerID(), ch->GetX(), ch->GetY(), dw, c_pszText, c_pszHint, ch->GetDesc() ? ch->GetDesc()->GetHostName() : "");
	else
		CharLog(0, 0, 0, dw, c_pszText, c_pszHint, "");
}

void LogManager::LoginLog(bool isLogin, uint32_t dwAccountID, uint32_t dwPID, uint8_t bLevel, uint8_t bJob, uint32_t dwPlayTime)
{
	Query("INSERT DELAYED INTO loginlog%s (type, time, channel, account_id, pid, level, job, playtime) VALUES (%s, NOW(), %d, %u, %u, %d, %d, %u)",
			get_table_postfix(), isLogin ? "'LOGIN'" : "'LOGOUT'", g_bChannel, dwAccountID, dwPID, bLevel, bJob, dwPlayTime);
}

void LogManager::MoneyLog(uint8_t type, uint32_t vnum, int32_t gold)
{
	if (type == MONEY_LOG_RESERVED || type >= MONEY_LOG_TYPE_MAX_NUM)
	{
		sys_err("TYPE ERROR: type %d vnum %u gold %d", type, vnum, gold);
		return;
	}

	Query("INSERT DELAYED INTO money_log%s VALUES (NOW(), %d, %d, %d)", get_table_postfix(), type, vnum, gold);
}

void LogManager::HackLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), c_pszHackName, strlen(c_pszHackName));

	Query("INSERT INTO hack_log (time, login, name, ip, server, why) VALUES(NOW(), '%s', '%s', '%s', '%s', '%s')", c_pszLogin, c_pszName, c_pszIP, g_stHostname.c_str(), __escape_hint);
}

void LogManager::HackLog(const char * c_pszHackName, LPCHARACTER ch)
{
	if (ch->GetDesc())
	{
		HackLog(c_pszHackName, 
				ch->GetDesc()->GetAccountTable().login,
				ch->GetName(),
				ch->GetDesc()->GetHostName());
	}
}

void LogManager::HackCRCLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP, uint32_t dwCRC)
{
	Query("INSERT INTO hack_crc_log (time, login, name, ip, server, why, crc) VALUES(NOW(), '%s', '%s', '%s', '%s', '%s', %u)", c_pszLogin, c_pszName, c_pszIP, g_stHostname.c_str(), c_pszHackName, dwCRC);
}

void LogManager::PCBangLoginLog(uint32_t dwPCBangID, const char* c_szPCBangIP, uint32_t dwPlayerID, uint32_t dwPlayTime)
{
	Query("INSERT INTO pcbang_loginlog (time, pcbang_id, ip, pid, play_time) VALUES (NOW(), %u, '%s', %u, %u)",
			dwPCBangID, c_szPCBangIP, dwPlayerID, dwPlayTime);
}

void LogManager::GoldBarLog(uint32_t dwPID, uint32_t dwItemID, GOLDBAR_HOW eHow, const char* c_pszHint)
{
	char szHow[32+1];
	
	switch (eHow)
	{
		case PERSONAL_SHOP_BUY:
			snprintf(szHow, sizeof(szHow), "'BUY'");
			break;
			
		case PERSONAL_SHOP_SELL:
			snprintf(szHow, sizeof(szHow), "'SELL'");
			break;
			
		case SHOP_BUY:
			snprintf(szHow, sizeof(szHow), "'SHOP_BUY'");
			break;
			
		case SHOP_SELL:
			snprintf(szHow, sizeof(szHow), "'SHOP_SELL'");
			break;
			
		case EXCHANGE_TAKE:
			snprintf(szHow, sizeof(szHow), "'EXCHANGE_TAKE'");
			break;
			
		case EXCHANGE_GIVE:
			snprintf(szHow, sizeof(szHow), "'EXCHANGE_GIVE'");
			break;

		case QUEST:
			snprintf(szHow, sizeof(szHow), "'QUEST'");
			break;

		default:
			snprintf(szHow, sizeof(szHow), "''");
			break;
	}
	
	Query("INSERT DELAYED INTO goldlog%s (date, time, pid, what, how, hint) VALUES(CURDATE(), CURTIME(), %u, %u, %s, '%s')", 
			get_table_postfix(), dwPID, dwItemID, szHow, c_pszHint);
}

void LogManager::CubeLog(uint32_t dwPID, uint32_t x, uint32_t y, uint32_t item_vnum, uint32_t item_uid, int32_t item_count, bool success)
{
	Query("INSERT DELAYED INTO cube%s (pid, time, x, y, item_vnum, item_uid, item_count, success) "
			"VALUES(%u, NOW(), %u, %u, %u, %u, %d, %d)",
			get_table_postfix(), dwPID, x, y, item_vnum, item_uid, item_count, success?1:0);
}

void LogManager::SpeedHackLog(uint32_t pid, uint32_t x, uint32_t y, int32_t hack_count)
{
	Query("INSERT INTO speed_hack%s (pid, time, x, y, hack_count) "
			"VALUES(%u, NOW(), %u, %u, %d)",
			get_table_postfix(), pid, x, y, hack_count);
}

void LogManager::ChangeNameLog(uint32_t pid, const char *old_name, const char *new_name, const char *ip)
{
	Query("INSERT DELAYED INTO change_name%s (pid, old_name, new_name, time, ip) "
			"VALUES(%u, '%s', '%s', NOW(), '%s') ",
			get_table_postfix(), pid, old_name, new_name, ip);
}

void LogManager::GMCommandLog(uint32_t dwPID, const char* szName, const char* szIP, uint8_t byChannel, const char* szCommand)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), szCommand, strlen(szCommand));

	Query("INSERT DELAYED INTO command_log%s (userid, server, ip, port, username, command, date ) "
			"VALUES(%u, 999, '%s', %u, '%s', '%s', NOW()) ",
			get_table_postfix(), dwPID, szIP, byChannel, szName, __escape_hint);
}

void LogManager::RefineLog(uint32_t pid, const char* item_name, uint32_t item_id, int32_t item_refine_level, int32_t is_success, const char* how)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), item_name, strlen(item_name));

	Query("INSERT INTO refinelog%s (pid, item_name, item_id, step, time, is_success, setType) VALUES(%u, '%s', %u, %d, NOW(), %d, '%s')",
			get_table_postfix(), pid, __escape_hint, item_id, item_refine_level, is_success, how);
}


void LogManager::ShoutLog(uint8_t bChannel, uint8_t bEmpire, const char * pszText)
{
	m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), pszText, strlen(pszText));

	Query("INSERT INTO shout_log%s VALUES(NOW(), %d, %d,'%s')", get_table_postfix(), bChannel, bEmpire, __escape_hint);
}

void LogManager::LevelLog(LPCHARACTER pChar, uint32_t level, uint32_t playhour)
{
	if (true == LC_IsEurope())
	{
		uint32_t aid = 0;

		if (NULL != pChar->GetDesc())
		{
			aid = pChar->GetDesc()->GetAccountTable().id;
		}

		Query("REPLACE INTO levellog%s (name, level, time, account_id, pid, playtime) VALUES('%s', %u, NOW(), %u, %u, %d)",
				get_table_postfix(), pChar->GetName(), level, aid, pChar->GetPlayerID(), playhour);
	}
	else
	{
		Query("REPLACE INTO levellog%s (name, level, time, playtime) VALUES('%s', %u, NOW(), %d)",
				get_table_postfix(), pChar->GetName(), level, playhour);
	}
}

void LogManager::BootLog(const char * c_pszHostName, uint8_t bChannel)
{
	Query("INSERT INTO bootlog (time, hostname, channel) VALUES(NOW(), '%s', %d)",
			c_pszHostName, bChannel);
}

void LogManager::VCardLog(uint32_t vcard_id, uint32_t x, uint32_t y, const char * hostname, const char * giver_name, const char * giver_ip, const char * taker_name, const char * taker_ip)
{
	Query("INSERT DELAYED INTO vcard_log (vcard_id, x, y, hostname, giver_name, giver_ip, taker_name, taker_ip) VALUES(%u, %u, %u, '%s', '%s', '%s', '%s', '%s')",
			vcard_id, x, y, hostname, giver_name, giver_ip, taker_name, taker_ip);
}

void LogManager::FishLog(uint32_t dwPID, int32_t prob_idx, int32_t fish_id, int32_t fish_level, uint32_t dwMiliseconds, uint32_t dwVnum, uint32_t dwValue)
{
	Query("INSERT INTO fish_log%s VALUES(NOW(), %u, %d, %u, %d, %u, %u, %u)",
			get_table_postfix(),
			dwPID,
			prob_idx,
			fish_id,
			fish_level,
			dwMiliseconds,
			dwVnum,
			dwValue);
}

void LogManager::QuestRewardLog(const char * c_pszQuestName, uint32_t dwPID, uint32_t dwLevel, int32_t iValue1, int32_t iValue2)
{
	Query("INSERT INTO quest_reward_log%s VALUES('%s',%u,%u,2,%u,%u,NOW())", 
			get_table_postfix(), 
			c_pszQuestName,
			dwPID,
			dwLevel,
			iValue1, 
			iValue2);
}

void LogManager::DetailLoginLog(bool isLogin, LPCHARACTER ch)
{
	if (NULL == ch->GetDesc())
		return;

	if (true == isLogin)
	{
		Query("INSERT INTO loginlog2(type, is_gm, login_time, channel, account_id, pid, ip, client_version) "
				"VALUES('INVALID', %s, NOW(), %d, %u, %u, inet_aton('%s'), '%s')",
				ch->IsGM() == true ? "'Y'" : "'N'",
				g_bChannel,
				ch->GetDesc()->GetAccountTable().id,
				ch->GetPlayerID(),
				ch->GetDesc()->GetHostName(),
				ch->GetDesc()->GetClientVersion());
	}
	else
	{
		Query("SET @i = (SELECT MAX(id) FROM loginlog2 WHERE account_id=%u AND pid=%u)",
				ch->GetDesc()->GetAccountTable().id,
				ch->GetPlayerID());

		Query("UPDATE loginlog2 SET type='VALID', logout_time=NOW(), playtime=TIMEDIFF(logout_time,login_time) WHERE id=@i");
	}
}

void LogManager::DragonSlayLog(uint32_t dwGuildID, uint32_t dwDragonVnum, uint32_t dwStartTime, uint32_t dwEndTime)
{
	Query( "INSERT INTO dragon_slay_log%s VALUES( %d, %d, FROM_UNIXTIME(%d), FROM_UNIXTIME(%d) )",
			get_table_postfix(),
			dwGuildID, dwDragonVnum, dwStartTime, dwEndTime);
}

/*void LogManager::HackShieldLog(uint32_t ErrorCode, LPCHARACTER ch)
{
	struct in_addr st_addr;

#ifndef __WIN32__
	if (0 == inet_aton(ch->GetDesc()->GetHostName(), &st_addr))
#else
	uint32_t in_address;
	in_address = inet_addr(ch->GetDesc()->GetHostName());
	st_addr.s_addr = in_address;
	if (INADDR_NONE == in_address)
#endif
	{
		Query( "INSERT INTO hackshield_log(time, account_id, login, pid, name, reason, ip) "
				"VALUES(NOW(), %u, '%s', %u, '%s', %u, 0)",
				ch->GetDesc()->GetAccountTable().id, ch->GetDesc()->GetAccountTable().login,
				ch->GetPlayerID(), ch->GetName(),
				ErrorCode);
	}
	else
	{
		Query( "INSERT INTO hackshield_log(time, account_id, login, pid, name, reason, ip) "
				"VALUES(NOW(), %u, '%s', %u, '%s', %u, inet_aton('%s'))",
				ch->GetDesc()->GetAccountTable().id, ch->GetDesc()->GetAccountTable().login,
				ch->GetPlayerID(), ch->GetName(),
				ErrorCode,
				ch->GetDesc()->GetHostName());
	}
}*/

