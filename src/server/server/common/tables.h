#ifndef __INC_TABLES_H__
#define __INC_TABLES_H__

#include "length.h"

typedef	uint32_t uint32_t;

/**
 * @version 05/06/10	Bang2ni - Myshop Pricelist ���� ��Ŷ HEADER_XX_MYSHOP_PRICELIST_XXX �߰�
 */
enum
{
	HEADER_GD_LOGIN				= 1,
	HEADER_GD_LOGOUT			= 2,

	HEADER_GD_PLAYER_LOAD		= 3,
	HEADER_GD_PLAYER_SAVE		= 4,
	HEADER_GD_PLAYER_CREATE		= 5,
	HEADER_GD_PLAYER_DELETE		= 6,

	HEADER_GD_LOGIN_KEY			= 7,
	// 8 empty
	HEADER_GD_BOOT				= 9,
	HEADER_GD_PLAYER_COUNT		= 10,
	HEADER_GD_QUEST_SAVE		= 11,
	HEADER_GD_SAFEBOX_LOAD		= 12,
	HEADER_GD_SAFEBOX_SAVE		= 13,
	HEADER_GD_SAFEBOX_CHANGE_SIZE	= 14,
	HEADER_GD_EMPIRE_SELECT		= 15,

	HEADER_GD_SAFEBOX_CHANGE_PASSWORD		= 16,
	HEADER_GD_SAFEBOX_CHANGE_PASSWORD_SECOND	= 17, // Not really a packet, used internal
	HEADER_GD_DIRECT_ENTER		= 18,

	HEADER_GD_GUILD_SKILL_UPDATE	= 19,
	HEADER_GD_GUILD_EXP_UPDATE		= 20,
	HEADER_GD_GUILD_ADD_MEMBER		= 21,
	HEADER_GD_GUILD_REMOVE_MEMBER	= 22,
	HEADER_GD_GUILD_CHANGE_GRADE	= 23,
	HEADER_GD_GUILD_CHANGE_MEMBER_DATA	= 24,
	HEADER_GD_GUILD_DISBAND		= 25,
	HEADER_GD_GUILD_WAR			= 26,
	HEADER_GD_GUILD_WAR_SCORE		= 27,
	HEADER_GD_GUILD_CREATE		= 28,

	HEADER_GD_ITEM_SAVE			= 30,
	HEADER_GD_ITEM_DESTROY		= 31,

	HEADER_GD_ADD_AFFECT		= 32,
	HEADER_GD_REMOVE_AFFECT		= 33,

	HEADER_GD_HIGHSCORE_REGISTER	= 34,
	HEADER_GD_ITEM_FLUSH		= 35,

	HEADER_GD_PARTY_CREATE		= 36,
	HEADER_GD_PARTY_DELETE		= 37,
	HEADER_GD_PARTY_ADD			= 38,
	HEADER_GD_PARTY_REMOVE		= 39,
	HEADER_GD_PARTY_STATE_CHANGE	= 40,
	HEADER_GD_PARTY_HEAL_USE		= 41,

	HEADER_GD_FLUSH_CACHE		= 42,
	HEADER_GD_RELOAD_PROTO		= 43,

	HEADER_GD_CHANGE_NAME		= 44,
	HEADER_GD_SMS				= 45,

	HEADER_GD_GUILD_CHANGE_LADDER_POINT	= 46,
	HEADER_GD_GUILD_USE_SKILL		= 47,

	HEADER_GD_REQUEST_EMPIRE_PRIV	= 48,
	HEADER_GD_REQUEST_GUILD_PRIV	= 49,

	HEADER_GD_MONEY_LOG				= 50,

	HEADER_GD_GUILD_DEPOSIT_MONEY				= 51,
	HEADER_GD_GUILD_WITHDRAW_MONEY				= 52,
	HEADER_GD_GUILD_WITHDRAW_MONEY_GIVE_REPLY	= 53,

	HEADER_GD_REQUEST_CHARACTER_PRIV	= 54,

	HEADER_GD_SET_EVENT_FLAG			= 55,

	HEADER_GD_PARTY_SET_MEMBER_LEVEL	= 56,

	HEADER_GD_GUILD_WAR_BET		= 57,

	HEADER_GD_CREATE_OBJECT		= 60,
	HEADER_GD_DELETE_OBJECT		= 61,
	HEADER_GD_UPDATE_LAND		= 62,

	HEADER_GD_MARRIAGE_ADD		= 70,
	HEADER_GD_MARRIAGE_UPDATE	= 71,
	HEADER_GD_MARRIAGE_REMOVE	= 72,

	HEADER_GD_WEDDING_REQUEST	= 73,
	HEADER_GD_WEDDING_READY		= 74,
	HEADER_GD_WEDDING_END		= 75,

	HEADER_GD_AUTH_LOGIN		= 100,
	HEADER_GD_LOGIN_BY_KEY		= 101,
	HEADER_GD_BILLING_EXPIRE	= 104,
	HEADER_GD_VCARD				= 105,
	HEADER_GD_BILLING_CHECK		= 106,
	HEADER_GD_MALL_LOAD			= 107,

	HEADER_GD_MYSHOP_PRICELIST_UPDATE	= 108,		///< �������� ���� ��û
	HEADER_GD_MYSHOP_PRICELIST_REQ		= 109,		///< �������� ����Ʈ ��û

	HEADER_GD_BLOCK_CHAT				= 110,

	// PCBANG_IP_LIST_BY_AUTH
	HEADER_GD_PCBANG_REQUEST_IP_LIST	= 111,
	HEADER_GD_PCBANG_CLEAR_IP_LIST		= 112,
	HEADER_GD_PCBANG_INSERT_IP			= 113,
	// END_OF_PCBANG_IP_LIST_BY_AUTH

	HEADER_GD_HAMMER_OF_TOR			= 114,
	HEADER_GD_RELOAD_ADMIN			= 115,			///<��� ���� ��û
	HEADER_GD_BREAK_MARRIAGE		= 116,			///< ��ȥ �ı�
	HEADER_GD_ELECT_MONARCH			= 117,			///< ���� ��ǥ
	HEADER_GD_CANDIDACY				= 118,			///< ���� ���
	HEADER_GD_ADD_MONARCH_MONEY		= 119,			///< ���� �� ���� 
	HEADER_GD_TAKE_MONARCH_MONEY	= 120,			///< ���� �� ���� 
	HEADER_GD_COME_TO_VOTE			= 121,			///< ǥ��
	HEADER_GD_RMCANDIDACY			= 122,			///< �ĺ� ���� (���)
	HEADER_GD_SETMONARCH			= 123,			///<���ּ��� (���)
	HEADER_GD_RMMONARCH			= 124,			///<���ֻ���
	HEADER_GD_DEC_MONARCH_MONEY = 125,

	HEADER_GD_CHANGE_MONARCH_LORD = 126,
	HEADER_GD_BLOCK_COUNTRY_IP		= 127,		// ���뿪 IP-Block
	HEADER_GD_BLOCK_EXCEPTION		= 128,		// ���뿪 IP-Block ����

	HEADER_GD_REQ_CHANGE_GUILD_MASTER	= 129,

	HEADER_GD_REQ_SPARE_ITEM_ID_RANGE	= 130,

	HEADER_GD_UPDATE_HORSE_NAME		= 131,
	HEADER_GD_REQ_HORSE_NAME		= 132,

	HEADER_GD_DC					= 133,		// Login Key�� ����

	HEADER_GD_VALID_LOGOUT			= 134,

	// AUCTION
#ifdef __AUCTION__
	HEADER_GD_GET_AUCTION_LIST		= 135,
	HEADER_GD_COMMAND_AUCTION		= 136,
#endif

	HEADER_GD_REQUEST_CHARGE_CASH	= 137,

	HEADER_GD_DELETE_AWARDID	= 138,	// delete gift notify icon
	
	HEADER_GD_UPDATE_CHANNELSTATUS	= 139,
	HEADER_GD_REQUEST_CHANNELSTATUS	= 140,

	HEADER_GD_SETUP			= 0xff,

	///////////////////////////////////////////////
	HEADER_DG_NOTICE			= 1,

	HEADER_DG_LOGIN_SUCCESS			= 30,
	HEADER_DG_LOGIN_NOT_EXIST		= 31,
	HEADER_DG_LOGIN_WRONG_PASSWD	= 33,
	HEADER_DG_LOGIN_ALREADY			= 34,

	HEADER_DG_PLAYER_LOAD_SUCCESS	= 35,
	HEADER_DG_PLAYER_LOAD_FAILED	= 36,
	HEADER_DG_PLAYER_CREATE_SUCCESS	= 37,
	HEADER_DG_PLAYER_CREATE_ALREADY	= 38,
	HEADER_DG_PLAYER_CREATE_FAILED	= 39,
	HEADER_DG_PLAYER_DELETE_SUCCESS	= 40,
	HEADER_DG_PLAYER_DELETE_FAILED	= 41,

	HEADER_DG_ITEM_LOAD			= 42,

	HEADER_DG_BOOT				= 43,
	HEADER_DG_QUEST_LOAD		= 44,

	HEADER_DG_SAFEBOX_LOAD					= 45,
	HEADER_DG_SAFEBOX_CHANGE_SIZE			= 46,
	HEADER_DG_SAFEBOX_WRONG_PASSWORD		= 47,
	HEADER_DG_SAFEBOX_CHANGE_PASSWORD_ANSWER = 48,

	HEADER_DG_EMPIRE_SELECT		= 49,

	HEADER_DG_AFFECT_LOAD		= 50,
	HEADER_DG_MALL_LOAD			= 51,

	HEADER_DG_DIRECT_ENTER		= 55,

	HEADER_DG_GUILD_SKILL_UPDATE	= 56,
	HEADER_DG_GUILD_SKILL_RECHARGE	= 57,
	HEADER_DG_GUILD_EXP_UPDATE		= 58,

	HEADER_DG_PARTY_CREATE		= 59,
	HEADER_DG_PARTY_DELETE		= 60,
	HEADER_DG_PARTY_ADD			= 61,
	HEADER_DG_PARTY_REMOVE		= 62,
	HEADER_DG_PARTY_STATE_CHANGE	= 63,
	HEADER_DG_PARTY_HEAL_USE		= 64,
	HEADER_DG_PARTY_SET_MEMBER_LEVEL	= 65,

	HEADER_DG_TIME			= 90,
	HEADER_DG_ITEM_ID_RANGE		= 91,

	HEADER_DG_GUILD_ADD_MEMBER		= 92,
	HEADER_DG_GUILD_REMOVE_MEMBER	= 93,
	HEADER_DG_GUILD_CHANGE_GRADE	= 94,
	HEADER_DG_GUILD_CHANGE_MEMBER_DATA	= 95,
	HEADER_DG_GUILD_DISBAND		= 96,
	HEADER_DG_GUILD_WAR			= 97,
	HEADER_DG_GUILD_WAR_SCORE		= 98,
	HEADER_DG_GUILD_TIME_UPDATE		= 99,
	HEADER_DG_GUILD_LOAD		= 100,
	HEADER_DG_GUILD_LADDER		= 101,
	HEADER_DG_GUILD_SKILL_USABLE_CHANGE	= 102,
	HEADER_DG_GUILD_MONEY_CHANGE	= 103,
	HEADER_DG_GUILD_WITHDRAW_MONEY_GIVE	= 104,

	HEADER_DG_SET_EVENT_FLAG		= 105,

	HEADER_DG_GUILD_WAR_RESERVE_ADD	= 106,
	HEADER_DG_GUILD_WAR_RESERVE_DEL	= 107,
	HEADER_DG_GUILD_WAR_BET		= 108,

	HEADER_DG_RELOAD_PROTO		= 120,
	HEADER_DG_CHANGE_NAME		= 121,

	HEADER_DG_AUTH_LOGIN		= 122,

	HEADER_DG_CHANGE_EMPIRE_PRIV	= 124,
	HEADER_DG_CHANGE_GUILD_PRIV		= 125,

	HEADER_DG_MONEY_LOG			= 126,

	HEADER_DG_CHANGE_CHARACTER_PRIV	= 127,

	HEADER_DG_BILLING_REPAIR		= 128,
	HEADER_DG_BILLING_EXPIRE		= 129,
	HEADER_DG_BILLING_LOGIN		= 130,
	HEADER_DG_VCARD			= 131,
	HEADER_DG_BILLING_CHECK		= 132,

	HEADER_DG_CREATE_OBJECT		= 140,
	HEADER_DG_DELETE_OBJECT		= 141,
	HEADER_DG_UPDATE_LAND		= 142,

	HEADER_DG_MARRIAGE_ADD		= 150,
	HEADER_DG_MARRIAGE_UPDATE		= 151,
	HEADER_DG_MARRIAGE_REMOVE		= 152,

	HEADER_DG_WEDDING_REQUEST		= 153,
	HEADER_DG_WEDDING_READY		= 154,
	HEADER_DG_WEDDING_START		= 155,
	HEADER_DG_WEDDING_END		= 156,

	HEADER_DG_MYSHOP_PRICELIST_RES	= 157,		///< �������� ����Ʈ ����
	HEADER_DG_RELOAD_ADMIN = 158, 				///< ��� ���� ���ε� 
	HEADER_DG_BREAK_MARRIAGE = 159,				///< ��ȥ �ı�
	HEADER_DG_ELECT_MONARCH			= 160,			///< ���� ��ǥ
	HEADER_DG_CANDIDACY				= 161,			///< ���� ���
	HEADER_DG_ADD_MONARCH_MONEY		= 162,			///< ���� �� ���� 
	HEADER_DG_TAKE_MONARCH_MONEY	= 163,			///< ���� �� ���� 
	HEADER_DG_COME_TO_VOTE			= 164,			///< ǥ��
	HEADER_DG_RMCANDIDACY			= 165,			///< �ĺ� ���� (���)
	HEADER_DG_SETMONARCH			= 166,			///<���ּ��� (���)
	HEADER_DG_RMMONARCH			= 167,			///<���ֻ���
	HEADER_DG_DEC_MONARCH_MONEY = 168,

	HEADER_DG_CHANGE_MONARCH_LORD_ACK = 169,
	HEADER_DG_UPDATE_MONARCH_INFO	= 170,
	HEADER_DG_BLOCK_COUNTRY_IP		= 171,		// ���뿪 IP-Block
	HEADER_DG_BLOCK_EXCEPTION		= 172,		// ���뿪 IP-Block ���� account

	HEADER_DG_ACK_CHANGE_GUILD_MASTER = 173,

	HEADER_DG_ACK_SPARE_ITEM_ID_RANGE = 174,

	HEADER_DG_UPDATE_HORSE_NAME 	= 175,
	HEADER_DG_ACK_HORSE_NAME		= 176,

	HEADER_DG_NEED_LOGIN_LOG		= 177,
#ifdef __AUCTION__
	HEADER_DG_AUCTION_RESULT	=	178,
#endif
	HEADER_DG_RESULT_CHARGE_CASH	= 179,
	HEADER_DG_ITEMAWARD_INFORMER	= 180,	//gift notify
	HEADER_DG_RESPOND_CHANNELSTATUS		= 181,

	HEADER_DG_MAP_LOCATIONS		= 0xfe,
	HEADER_DG_P2P			= 0xff,

	HEADER_GP_CONFIRM_PASSPOD = 1,
	HEADER_PG_CONFIRM_PASSPOD = 2,

};

enum E_PASSPOD
{
	E_PASSPOD_SUCCESS = 0,
	E_PASSPOD_FAILED_PASSPOD_ERROR,
	E_PASSPOD_FAILED_USER_NOT_FOUND,
	E_PASSPOD_FAILED_SYSTEM_NOT_FOUND,
	E_PASSPOD_FAILED_TOKEN_DISABLED,
	E_PASSPOD_FAILED_EMPTY,
};


typedef struct SRequestConfirmPasspod
{
	int32_t pid;
	char passpod[MAX_PASSPOD + 1];
	char login[LOGIN_MAX_LEN + 1];

} RequestConfirmPasspod;

typedef struct SResultConfirmPasspod
{
	int32_t pid;
	int32_t ret_code;
	char login[LOGIN_MAX_LEN + 1];
} ResultConfirmPasspod;
/* ----------------------------------------------
 * table
 * ----------------------------------------------
 */

/* game Server -> DB Server */
#pragma pack(1)
enum ERequestChargeType
{
	ERequestCharge_Cash = 0,
	ERequestCharge_Mileage,
};

typedef struct SRequestChargeCash
{
	uint32_t		dwAID;		// id(primary key) - Account Table
	uint32_t		dwAmount;
	ERequestChargeType	eChargeType;

} TRequestChargeCash;

typedef struct SSimplePlayer
{
	uint32_t		dwID;
	char		szName[CHARACTER_NAME_MAX_LEN + 1];
	uint8_t		byJob;
	uint8_t		byLevel;
	uint32_t		dwPlayMinutes;
	uint8_t		byST, byHT, byDX, byIQ;
	uint16_t		wMainPart;
	uint8_t		bChangeName;
	uint16_t		wHairPart;
	uint8_t		bDummy[4];
	int32_t		x, y;
	int32_t		lAddr;
	uint16_t		wPort;
	uint8_t		skill_group;
} TSimplePlayer;

typedef struct SAccountTable
{
	uint32_t		id;
	char		login[LOGIN_MAX_LEN + 1];
	char		passwd[PASSWD_MAX_LEN + 1];
	char		social_id[SOCIAL_ID_MAX_LEN + 1];
	char		status[ACCOUNT_STATUS_MAX_LEN + 1];
	uint8_t		bEmpire;
	TSimplePlayer	players[PLAYER_PER_ACCOUNT];
} TAccountTable;

typedef struct SPacketDGCreateSuccess
{
	uint8_t		bAccountCharacterIndex;
	TSimplePlayer	player;
} TPacketDGCreateSuccess;

typedef struct TPlayerItemAttribute
{
	uint8_t	bType;
	int16_t	sValue;
} TPlayerItemAttribute;

typedef struct SPlayerItem
{
	uint32_t	id;
	uint8_t	window;
	uint16_t	pos;
	uint32_t	count;

	uint32_t	vnum;
	int32_t	alSockets[ITEM_SOCKET_MAX_NUM];	// ���Ϲ�ȣ

	TPlayerItemAttribute    aAttr[ITEM_ATTRIBUTE_MAX_NUM];

	uint32_t	owner;
} TPlayerItem;

typedef struct SQuickslot
{
	uint8_t	type;
	uint8_t	pos;
} TQuickslot;

typedef struct SPlayerSkill
{
	uint8_t	bMasterType;
	uint8_t	bLevel;
	int32_t	tNextRead;
} TPlayerSkill;

struct	THorseInfo
{
	uint8_t	bLevel;
	uint8_t	bRiding;
	int16_t	sStamina;
	int16_t	sHealth;
	uint32_t	dwHorseHealthDropTime;
};

typedef struct SPlayerTable
{
	uint32_t	id;

	char	name[CHARACTER_NAME_MAX_LEN + 1];
	char	ip[IP_ADDRESS_LENGTH + 1];

	uint16_t	job;
	uint8_t	voice;

	uint8_t	level;
	uint8_t	level_step;
	int16_t	st, ht, dx, iq;

	uint32_t	exp;
	int32_t		gold;

	uint8_t	dir;
	int32_t		x, y, z;
	int32_t		lMapIndex;

	int32_t	lExitX, lExitY;
	int32_t	lExitMapIndex;

	int16_t       hp;
	int16_t       sp;

	int16_t	sRandomHP;
	int16_t	sRandomSP;

	int32_t         playtime;

	int16_t	stat_point;
	int16_t	skill_point;
	int16_t	sub_skill_point;
	int16_t	horse_skill_point;

	TPlayerSkill skills[SKILL_MAX_NUM];

	TQuickslot  quickslot[QUICKSLOT_MAX_NUM];

	uint8_t	part_base;
	uint16_t	parts[PART_MAX_NUM];

	int16_t	stamina;

	uint8_t	skill_group;
	int32_t	lAlignment;
	char	szMobile[MOBILE_MAX_LEN + 1];

	int16_t	stat_reset_count;

	THorseInfo	horse;

	uint32_t	logoff_interval;

	int32_t		aiPremiumTimes[PREMIUM_MAX_NUM];
} TPlayerTable;

typedef struct SMobSkillLevel
{
	uint32_t	dwVnum;
	uint8_t	bLevel;
} TMobSkillLevel;

typedef struct SEntityTable
{
	uint32_t dwVnum;
} TEntityTable;

typedef struct SMobTable : public SEntityTable
{
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	char	szLocaleName[CHARACTER_NAME_MAX_LEN + 1];

	uint8_t	bType;			// Monster, NPC
	uint8_t	bRank;			// PAWN, KNIGHT, KING
	uint8_t	bBattleType;		// MELEE, etc..
	uint8_t	bLevel;			// Level
	uint8_t	bSize;

	uint32_t	dwGoldMin;
	uint32_t	dwGoldMax;
	uint32_t	dwExp;
	uint32_t	dwMaxHP;
	uint8_t	bRegenCycle;
	uint8_t	bRegenPercent;
	uint16_t	wDef;

	uint32_t	dwAIFlag;
	uint32_t	dwRaceFlag;
	uint32_t	dwImmuneFlag;

	uint8_t	bStr, bDex, bCon, bInt;
	uint32_t	dwDamageRange[2];

	int16_t	sAttackSpeed;
	int16_t	sMovingSpeed;
	uint8_t	bAggresiveHPPct;
	uint16_t	wAggressiveSight;
	uint16_t	wAttackRange;

	char	cEnchants[MOB_ENCHANTS_MAX_NUM];
	char	cResists[MOB_RESISTS_MAX_NUM];

	uint32_t	dwResurrectionVnum;
	uint32_t	dwDropItemVnum;

	uint8_t	bMountCapacity;
	uint8_t	bOnClickType;

	uint8_t	bEmpire;
	char	szFolder[64 + 1];

	float	fDamMultiply;

	uint32_t	dwSummonVnum;
	uint32_t	dwDrainSP;
	uint32_t	dwMobColor;
	uint32_t	dwPolymorphItemVnum;

	TMobSkillLevel Skills[MOB_SKILL_MAX_NUM];

	uint8_t	bBerserkPoint;
	uint8_t	bStoneSkinPoint;
	uint8_t	bGodSpeedPoint;
	uint8_t	bDeathBlowPoint;
	uint8_t	bRevivePoint;
} TMobTable;

typedef struct SSkillTable
{
	uint32_t	dwVnum;
	char	szName[32 + 1];
	uint8_t	bType;
	uint8_t	bMaxLevel;
	uint32_t	dwSplashRange;

	char	szPointOn[64];
	char	szPointPoly[100 + 1];
	char	szSPCostPoly[100 + 1];
	char	szDurationPoly[100 + 1];
	char	szDurationSPCostPoly[100 + 1];
	char	szCooldownPoly[100 + 1];
	char	szMasterBonusPoly[100 + 1];
	//char	szAttackGradePoly[100 + 1];
	char	szGrandMasterAddSPCostPoly[100 + 1];
	uint32_t	dwFlag;
	uint32_t	dwAffectFlag;

	// Data for secondary skill
	char 	szPointOn2[64];
	char 	szPointPoly2[100 + 1];
	char 	szDurationPoly2[100 + 1];
	uint32_t 	dwAffectFlag2;

	// Data for grand master point
	char 	szPointOn3[64];
	char 	szPointPoly3[100 + 1];
	char 	szDurationPoly3[100 + 1];

	uint8_t	bLevelStep;
	uint8_t	bLevelLimit;
	uint32_t	preSkillVnum;
	uint8_t	preSkillLevel;

	int32_t	lMaxHit; 
	char	szSplashAroundDamageAdjustPoly[100 + 1];

	uint8_t	bSkillAttrType;

	uint32_t	dwTargetRange;
} TSkillTable;

typedef struct SShopItemTable
{
	uint32_t		vnum;
	uint8_t		count;

    TItemPos	pos;			// PC �������� �̿�
	uint32_t		price;	// PC, shop_table_ex.txt �������� �̿�
	uint8_t		display_pos; // PC, shop_table_ex.txt �������� �̿�, ���� ��ġ.
} TShopItemTable;

typedef struct SShopTable
{
	uint32_t		dwVnum;
	uint32_t		dwNPCVnum;

	uint8_t		byItemCount;
	TShopItemTable	items[SHOP_HOST_ITEM_MAX_NUM];
} TShopTable;

#define QUEST_NAME_MAX_LEN	32
#define QUEST_STATE_MAX_LEN	64

typedef struct SQuestTable
{
	uint32_t		dwPID;
	char		szName[QUEST_NAME_MAX_LEN + 1];
	char		szState[QUEST_STATE_MAX_LEN + 1];
	int32_t		lValue;
} TQuestTable;

typedef struct SItemLimit
{
	uint8_t	bType;
	int32_t	lValue;
} TItemLimit;

typedef struct SItemApply
{
	uint8_t	bType;
	int32_t	lValue;
} TItemApply;

typedef struct SItemTable : public SEntityTable
{
	uint32_t		dwVnumRange;
	char        szName[ITEM_NAME_MAX_LEN + 1];
	char	szLocaleName[ITEM_NAME_MAX_LEN + 1];
	uint8_t	bType;
	uint8_t	bSubType;

	uint8_t        bWeight;
	uint8_t	bSize;

	uint32_t	dwAntiFlags;
	uint32_t	dwFlags;
	uint32_t	dwWearFlags;
	uint32_t	dwImmuneFlag;

	uint32_t       dwGold;
	uint32_t       dwShopBuyPrice;

	TItemLimit	aLimits[ITEM_LIMIT_MAX_NUM];
	TItemApply	aApplies[ITEM_APPLY_MAX_NUM];
	int32_t        alValues[ITEM_VALUES_MAX_NUM];
	int32_t	alSockets[ITEM_SOCKET_MAX_NUM];
	uint32_t	dwRefinedVnum;
	uint16_t	wRefineSet;
	uint8_t	bAlterToMagicItemPct;
	uint8_t	bSpecular;
	uint8_t	bGainSocketPct;

	int16_t	sAddonType; // �⺻ �Ӽ�

	// �Ʒ� limit flag���� realtime�� üũ �� ���� ����, ������ VNUM�� ������ ���ε�,
	// ���� ������� �Ź� �����۸��� �ʿ��� ��쿡 LIMIT_MAX_NUM���� �������鼭 üũ�ϴ� ���ϰ� Ŀ�� �̸� ���� �� ��.
	char		cLimitRealTimeFirstUseIndex;		// ������ limit �ʵ尪 �߿��� LIMIT_REAL_TIME_FIRST_USE �÷����� ��ġ (������ -1)
	char		cLimitTimerBasedOnWearIndex;		// ������ limit �ʵ尪 �߿��� LIMIT_TIMER_BASED_ON_WEAR �÷����� ��ġ (������ -1) 

} TItemTable;

struct TItemAttrTable
{
	TItemAttrTable() :
		dwApplyIndex(0),
		dwProb(0)
	{
		szApply[0] = 0;
		memset(&lValues, 0, sizeof(lValues));
		memset(&bMaxLevelBySet, 0, sizeof(bMaxLevelBySet));
	}

	char    szApply[APPLY_NAME_MAX_LEN + 1];
	uint32_t   dwApplyIndex;
	uint32_t   dwProb;
	int32_t    lValues[5];
	uint8_t    bMaxLevelBySet[ATTRIBUTE_SET_MAX_NUM];
};

typedef struct SConnectTable
{
	char	login[LOGIN_MAX_LEN + 1];
	uint32_t	ident;
} TConnectTable;

typedef struct SLoginPacket
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
} TLoginPacket;

typedef struct SPlayerLoadPacket
{
	uint32_t	account_id;
	uint32_t	player_id;
	uint8_t	account_index;	/* account ������ ��ġ */
} TPlayerLoadPacket;

typedef struct SPlayerCreatePacket
{
	char		login[LOGIN_MAX_LEN + 1];
	char		passwd[PASSWD_MAX_LEN + 1];
	uint32_t		account_id;
	uint8_t		account_index;
	TPlayerTable	player_table;
} TPlayerCreatePacket;

typedef struct SPlayerDeletePacket
{
	char	login[LOGIN_MAX_LEN + 1];
	uint32_t	player_id;
	uint8_t	account_index;
	//char	name[CHARACTER_NAME_MAX_LEN + 1];
	char	private_code[8];
} TPlayerDeletePacket;

typedef struct SLogoutPacket
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
} TLogoutPacket;

typedef struct SPlayerCountPacket
{
	uint32_t	dwCount;
} TPlayerCountPacket;

#define SAFEBOX_MAX_NUM			135
#define SAFEBOX_PASSWORD_MAX_LEN	6

typedef struct SSafeboxTable
{
	uint32_t	dwID;
	uint8_t	bSize;
	uint32_t	dwGold;
	uint16_t	wItemCount;
} TSafeboxTable;

typedef struct SSafeboxChangeSizePacket
{
	uint32_t	dwID;
	uint8_t	bSize;
} TSafeboxChangeSizePacket;

typedef struct SSafeboxLoadPacket
{
	uint32_t	dwID;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
} TSafeboxLoadPacket;

typedef struct SSafeboxChangePasswordPacket
{
	uint32_t	dwID;
	char	szOldPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
	char	szNewPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
} TSafeboxChangePasswordPacket;

typedef struct SSafeboxChangePasswordPacketAnswer
{
	uint8_t	flag;
} TSafeboxChangePasswordPacketAnswer;

typedef struct SEmpireSelectPacket
{
	uint32_t	dwAccountID;
	uint8_t	bEmpire;
} TEmpireSelectPacket;

typedef struct SPacketGDSetup
{
	char	szPublicIP[16];	// Public IP which listen to users
	uint8_t	bChannel;	// ä��
	uint16_t	wListenPort;	// Ŭ���̾�Ʈ�� �����ϴ� ��Ʈ ��ȣ
	uint16_t	wP2PPort;	// �������� ���� ��Ű�� P2P ��Ʈ ��ȣ
	int32_t	alMaps[32];
	uint32_t	dwLoginCount;
	uint8_t	bAuthServer;
} TPacketGDSetup;

typedef struct SPacketDGMapLocations
{
	uint8_t	bCount;
} TPacketDGMapLocations;

typedef struct SMapLocation
{
	int32_t	alMaps[32];
	char	szHost[MAX_HOST_LENGTH + 1];
	uint16_t	wPort;
} TMapLocation;

typedef struct SPacketDGP2P
{
	char	szHost[MAX_HOST_LENGTH + 1];
	uint16_t	wPort;
	uint8_t	bChannel;
} TPacketDGP2P;

typedef struct SPacketGDDirectEnter
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
	uint8_t	index;
} TPacketGDDirectEnter;

typedef struct SPacketDGDirectEnter
{
	TAccountTable accountTable;
	TPlayerTable playerTable;
} TPacketDGDirectEnter;

typedef struct SPacketGuildSkillUpdate
{
	uint32_t guild_id;
	int32_t amount;
	uint8_t skill_levels[12];
	uint8_t skill_point;
	uint8_t save;
} TPacketGuildSkillUpdate;

typedef struct SPacketGuildExpUpdate
{
	uint32_t guild_id;
	int32_t amount;
} TPacketGuildExpUpdate;

typedef struct SPacketGuildChangeMemberData
{
	uint32_t guild_id;
	uint32_t pid;
	uint32_t offer;
	uint8_t level;
	uint8_t grade;
} TPacketGuildChangeMemberData;


typedef struct SPacketDGLoginAlready
{
	char	szLogin[LOGIN_MAX_LEN + 1];
} TPacketDGLoginAlready;

typedef struct TPacketAffectElement
{
	uint32_t	dwType;
	uint8_t	bApplyOn;
	int32_t	lApplyValue;
	uint32_t	dwFlag;
	int32_t	lDuration;
	int32_t	lSPCost;
} TPacketAffectElement;

typedef struct SPacketGDAddAffect
{
	uint32_t			dwPID;
	TPacketAffectElement	elem;
} TPacketGDAddAffect;

typedef struct SPacketGDRemoveAffect
{
	uint32_t	dwPID;
	uint32_t	dwType;
	uint8_t	bApplyOn;
} TPacketGDRemoveAffect;

typedef struct SPacketGDHighscore
{
	uint32_t	dwPID;
	int32_t	lValue;
	char	cDir;
	char	szBoard[21];
} TPacketGDHighscore;

typedef struct SPacketPartyCreate
{
	uint32_t	dwLeaderPID;
} TPacketPartyCreate;

typedef struct SPacketPartyDelete
{
	uint32_t	dwLeaderPID;
} TPacketPartyDelete;

typedef struct SPacketPartyAdd
{
	uint32_t	dwLeaderPID;
	uint32_t	dwPID;
	uint8_t	bState;
} TPacketPartyAdd;

typedef struct SPacketPartyRemove
{
	uint32_t	dwLeaderPID;
	uint32_t	dwPID;
} TPacketPartyRemove;

typedef struct SPacketPartyStateChange
{
	uint32_t	dwLeaderPID;
	uint32_t	dwPID;
	uint8_t	bRole;
	uint8_t	bFlag;
} TPacketPartyStateChange;

typedef struct SPacketPartySetMemberLevel
{
	uint32_t	dwLeaderPID;
	uint32_t	dwPID;
	uint8_t	bLevel;
} TPacketPartySetMemberLevel;

typedef struct SPacketGDBoot
{
    uint32_t	dwItemIDRange[2];
	char	szIP[16];
} TPacketGDBoot;

typedef struct SPacketGuild
{
	uint32_t	dwGuild;
	uint32_t	dwInfo;
} TPacketGuild;

typedef struct SPacketGDGuildAddMember
{
	uint32_t	dwPID;
	uint32_t	dwGuild;
	uint8_t	bGrade;
} TPacketGDGuildAddMember;

typedef struct SPacketDGGuildMember
{
	uint32_t	dwPID;
	uint32_t	dwGuild;
	uint8_t	bGrade;
	uint8_t	isGeneral;
	uint8_t	bJob;
	uint8_t	bLevel;
	uint32_t	dwOffer;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketDGGuildMember;

typedef struct SPacketGuildWar
{
	uint8_t	bType;
	uint8_t	bWar;
	uint32_t	dwGuildFrom;
	uint32_t	dwGuildTo;
	int32_t	lWarPrice;
	int32_t	lInitialScore;
} TPacketGuildWar;

// Game -> DB : ����� ��ȭ��
// DB -> Game : ��Ż�� ������
typedef struct SPacketGuildWarScore
{
	uint32_t dwGuildGainPoint;
	uint32_t dwGuildOpponent;
	int32_t lScore;
	int32_t lBetScore;
} TPacketGuildWarScore;

typedef struct SRefineMaterial
{
	uint32_t vnum;
	int32_t count;
} TRefineMaterial;

typedef struct SRefineTable
{
	//uint32_t src_vnum;
	//uint32_t result_vnum;
	uint32_t id;
	uint8_t material_count;
	int32_t cost; // �ҿ� ���
	int32_t prob; // Ȯ��
	TRefineMaterial materials[REFINE_MATERIAL_MAX_NUM];
} TRefineTable;

typedef struct SBanwordTable
{
	char szWord[BANWORD_MAX_LEN + 1];
} TBanwordTable;

typedef struct SPacketGDChangeName
{
	uint32_t pid;
	char name[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGDChangeName;

typedef struct SPacketDGChangeName
{
	uint32_t pid;
	char name[CHARACTER_NAME_MAX_LEN + 1];
} TPacketDGChangeName;

typedef struct SPacketGuildLadder
{
	uint32_t dwGuild;
	int32_t lLadderPoint;
	int32_t lWin;
	int32_t lDraw;
	int32_t lLoss;
} TPacketGuildLadder;

typedef struct SPacketGuildLadderPoint
{
	uint32_t dwGuild;
	int32_t lChange;
} TPacketGuildLadderPoint;

typedef struct SPacketGDSMS
{
	char szFrom[CHARACTER_NAME_MAX_LEN + 1];
	char szTo[CHARACTER_NAME_MAX_LEN + 1];
	char szMobile[MOBILE_MAX_LEN + 1];
	char szMsg[SMS_MAX_LEN + 1];
} TPacketGDSMS;

typedef struct SPacketGuildUseSkill
{
	uint32_t dwGuild;
	uint32_t dwSkillVnum;
	uint32_t dwCooltime;
} TPacketGuildUseSkill;

typedef struct SPacketGuildSkillUsableChange
{
	uint32_t dwGuild;
	uint32_t dwSkillVnum;
	uint8_t bUsable;
} TPacketGuildSkillUsableChange;

typedef struct SPacketGDLoginKey
{
	uint32_t dwAccountID;
	uint32_t dwLoginKey;
} TPacketGDLoginKey;

typedef struct SPacketGDAuthLogin
{
	uint32_t	dwID;
	uint32_t	dwLoginKey;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szSocialID[SOCIAL_ID_MAX_LEN + 1];
	uint32_t	adwClientKey[4];
	uint8_t	bBillType;
	uint32_t	dwBillID;
	int32_t		iPremiumTimes[PREMIUM_MAX_NUM];
} TPacketGDAuthLogin;

typedef struct SPacketGDLoginByKey
{
	char	szLogin[LOGIN_MAX_LEN + 1];
	uint32_t	dwLoginKey;
	uint32_t	adwClientKey[4];
	char	szIP[MAX_HOST_LENGTH + 1];
} TPacketGDLoginByKey;

/**
 * @version 05/06/08	Bang2ni - ���ӽð� �߰�
 */
typedef struct SPacketGiveGuildPriv
{
	uint8_t type;
	int32_t value;
	uint32_t guild_id;
	int32_t duration_sec;	///< ���ӽð�
} TPacketGiveGuildPriv;
typedef struct SPacketGiveEmpirePriv
{
	uint8_t type;
	int32_t value;
	uint8_t empire;
	int32_t duration_sec;
} TPacketGiveEmpirePriv;
typedef struct SPacketGiveCharacterPriv
{
	uint8_t type;
	int32_t value;
	uint32_t pid;
} TPacketGiveCharacterPriv;
typedef struct SPacketRemoveGuildPriv
{
	uint8_t type;
	uint32_t guild_id;
} TPacketRemoveGuildPriv;
typedef struct SPacketRemoveEmpirePriv
{
	uint8_t type;
	uint8_t empire;
} TPacketRemoveEmpirePriv;

typedef struct SPacketDGChangeCharacterPriv
{
	uint8_t type;
	int32_t value;
	uint32_t pid;
	uint8_t bLog;
} TPacketDGChangeCharacterPriv;

/**
 * @version 05/06/08	Bang2ni - ���ӽð� �߰�
 */
typedef struct SPacketDGChangeGuildPriv
{
	uint8_t type;
	int32_t value;
	uint32_t guild_id;
	uint8_t bLog;
	int32_t end_time_sec;	///< ���ӽð�
} TPacketDGChangeGuildPriv;

typedef struct SPacketDGChangeEmpirePriv
{
	uint8_t type;
	int32_t value;
	uint8_t empire;
	uint8_t bLog;
	int32_t end_time_sec;
} TPacketDGChangeEmpirePriv;

typedef struct SPacketMoneyLog
{
	uint8_t type;
	uint32_t vnum;
	int32_t gold;
} TPacketMoneyLog;

typedef struct SPacketGDGuildMoney
{
	uint32_t dwGuild;
	int32_t iGold;
} TPacketGDGuildMoney;

typedef struct SPacketDGGuildMoneyChange
{
	uint32_t dwGuild;
	int32_t iTotalGold;
} TPacketDGGuildMoneyChange;

typedef struct SPacketDGGuildMoneyWithdraw
{
	uint32_t dwGuild;
	int32_t iChangeGold;
} TPacketDGGuildMoneyWithdraw;

typedef struct SPacketGDGuildMoneyWithdrawGiveReply
{
	uint32_t dwGuild;
	int32_t iChangeGold;
	uint8_t bGiveSuccess;
} TPacketGDGuildMoneyWithdrawGiveReply;

typedef struct SPacketSetEventFlag
{
	char	szFlagName[EVENT_FLAG_NAME_MAX_LEN + 1];
	int32_t	lValue;
} TPacketSetEventFlag;

typedef struct SPacketBillingLogin
{
	uint32_t	dwLoginKey;
	uint8_t	bLogin;
} TPacketBillingLogin;

typedef struct SPacketBillingRepair
{
	uint32_t	dwLoginKey;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szHost[MAX_HOST_LENGTH + 1];
} TPacketBillingRepair;

typedef struct SPacketBillingExpire
{
	char	szLogin[LOGIN_MAX_LEN + 1];
	uint8_t	bBillType;
	uint32_t	dwRemainSeconds;
} TPacketBillingExpire;

typedef struct SPacketLoginOnSetup
{
	uint32_t   dwID;
	char    szLogin[LOGIN_MAX_LEN + 1];
	char    szSocialID[SOCIAL_ID_MAX_LEN + 1];
	char    szHost[MAX_HOST_LENGTH + 1];
	uint32_t   dwLoginKey;
	uint32_t   adwClientKey[4];
} TPacketLoginOnSetup;

typedef struct SPacketGDCreateObject
{
	uint32_t	dwVnum;
	uint32_t	dwLandID;
	int32_t		lMapIndex;
	int32_t	 	x, y;
	float	xRot;
	float	yRot;
	float	zRot;
} TPacketGDCreateObject;

typedef struct SPacketGDHammerOfTor
{
	uint32_t 	key;
	uint32_t	delay;
} TPacketGDHammerOfTor;

typedef struct SPacketGDVCard
{
	uint32_t	dwID;
	char	szSellCharacter[CHARACTER_NAME_MAX_LEN + 1];
	char	szSellAccount[LOGIN_MAX_LEN + 1];
	char	szBuyCharacter[CHARACTER_NAME_MAX_LEN + 1];
	char	szBuyAccount[LOGIN_MAX_LEN + 1];
} TPacketGDVCard;

typedef struct SGuildReserve
{
	uint32_t       dwID;
	uint32_t       dwGuildFrom;
	uint32_t       dwGuildTo;
	uint32_t       dwTime;
	uint8_t        bType;
	int32_t        lWarPrice;
	int32_t        lInitialScore;
	bool        bStarted;
	uint32_t	dwBetFrom;
	uint32_t	dwBetTo;
	int32_t	lPowerFrom;
	int32_t	lPowerTo;
	int32_t	lHandicap;
} TGuildWarReserve;

typedef struct
{
	uint32_t	dwWarID;
	char	szLogin[LOGIN_MAX_LEN + 1];
	uint32_t	dwGold;
	uint32_t	dwGuild;
} TPacketGDGuildWarBet;

// Marriage

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
	int32_t tMarryTime;
	char szName1[CHARACTER_NAME_MAX_LEN + 1];
	char szName2[CHARACTER_NAME_MAX_LEN + 1];
} TPacketMarriageAdd;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
	int32_t  iLovePoint;
	uint8_t  byMarried;
} TPacketMarriageUpdate;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
} TPacketMarriageRemove;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
} TPacketWeddingRequest;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
	uint32_t dwMapIndex;
} TPacketWeddingReady;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
} TPacketWeddingStart;

typedef struct
{
	uint32_t dwPID1;
	uint32_t dwPID2;
} TPacketWeddingEnd;

/// ���λ��� ���������� ���. ���� ��Ŷ���� �� �ڿ� byCount ��ŭ�� TItemPriceInfo �� �´�.
typedef struct SPacketMyshopPricelistHeader
{ 
	uint32_t	dwOwnerID;	///< ���������� ���� �÷��̾� ID 
	uint8_t	byCount;	///< �������� ����
} TPacketMyshopPricelistHeader;

/// ���λ����� ���� �����ۿ� ���� ��������
typedef struct SItemPriceInfo
{
	uint32_t	dwVnum;		///< ������ vnum
	uint32_t	dwPrice;	///< ����
} TItemPriceInfo;

/// ���λ��� ������ �������� ����Ʈ ���̺�
typedef struct SItemPriceListTable
{
	uint32_t	dwOwnerID;	///< ���������� ���� �÷��̾� ID
	uint8_t	byCount;	///< �������� ����Ʈ�� ����

	TItemPriceInfo	aPriceInfo[SHOP_PRICELIST_MAX_NUM];	///< �������� ����Ʈ
} TItemPriceListTable;

typedef struct
{
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	int32_t lDuration;
} TPacketBlockChat;

// PCBANG_IP_LIST
typedef struct SPacketPCBangIP
{
	uint32_t id;
	uint32_t ip;
} TPacketPCBangIP;
// END_OF_PCBANG_IP_LIST


//ADMIN_MANAGER
typedef struct TAdminInfo
{
	int32_t m_ID;				//����ID
	char m_szAccount[32];	//����
	char m_szName[32];		//ĳ�����̸�
	char m_szContactIP[16];	//���پ�����
	char m_szServerIP[16];  //����������
	int32_t m_Authority;		//����
} tAdminInfo;
//END_ADMIN_MANAGER

//BOOT_LOCALIZATION
struct tLocale
{
	char szValue[32];
	char szKey[32];
};
//BOOT_LOCALIZATION

//RELOAD_ADMIN
typedef struct SPacketReloadAdmin
{
	char szIP[16];
} TPacketReloadAdmin;
//END_RELOAD_ADMIN

typedef struct TMonarchInfo
{
	uint32_t pid[4];  // ������ PID
	int64_t money[4];  // ������ ���� ��	
	char name[4][32];  // ������ �̸�	
	char date[4][32];  // ���� ��� ��¥
} MonarchInfo;

typedef struct TMonarchElectionInfo
{
	uint32_t pid;  // ��ǥ �ѻ�� PID
	uint32_t selectedpid; // ��ǥ ���� PID ( ���� ������ )
	char date[32]; // ��ǥ ��¥
} MonarchElectionInfo;

// ���� �⸶��
typedef struct tMonarchCandidacy
{
	uint32_t pid;
	char name[32];
	char date[32];
} MonarchCandidacy;

typedef struct tChangeMonarchLord
{
	uint8_t bEmpire;
	uint32_t dwPID;
} TPacketChangeMonarchLord;

typedef struct tChangeMonarchLordACK
{
	uint8_t bEmpire;
	uint32_t dwPID;
	char szName[32];
	char szDate[32];
} TPacketChangeMonarchLordACK;

// Block Country Ip
typedef struct tBlockCountryIp
{
	uint32_t	ip_from;
	uint32_t	ip_to;
} TPacketBlockCountryIp;

enum EBlockExceptionCommand
{
	BLOCK_EXCEPTION_CMD_ADD = 1,
	BLOCK_EXCEPTION_CMD_DEL = 2,
};

// Block Exception Account
typedef struct tBlockException
{
	uint8_t	cmd;	// 1 == add, 2 == delete
	char	login[LOGIN_MAX_LEN + 1];
}TPacketBlockException;

typedef struct tChangeGuildMaster
{
	uint32_t dwGuildID;
	uint32_t idFrom;
	uint32_t idTo;
} TPacketChangeGuildMaster;

typedef struct tItemIDRange
{
	uint32_t dwMin;
	uint32_t dwMax;
	uint32_t dwUsableItemIDMin;
} TItemIDRangeTable;

typedef struct tUpdateHorseName
{
	uint32_t dwPlayerID;
	char szHorseName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketUpdateHorseName;

typedef struct tDC
{
	char	login[LOGIN_MAX_LEN + 1];
} TPacketDC;

typedef struct tNeedLoginLogInfo
{
	uint32_t dwPlayerID;
} TPacketNeedLoginLogInfo;

//���� ���� �˸� ��� �׽�Ʈ�� ��Ŷ ����
typedef struct tItemAwardInformer
{
	char	login[LOGIN_MAX_LEN + 1];
	char	command[20];		//��ɾ�
	uint32_t vnum;			//������
} TPacketItemAwardInfromer;
// ���� �˸� ��� ������ ��Ŷ ����
typedef struct tDeleteAwardID
{
	uint32_t dwID;
} TPacketDeleteAwardID;

typedef struct SChannelStatus
{
	int16_t nPort;
	uint8_t bStatus;
} TChannelStatus;

#pragma pack()
#endif
