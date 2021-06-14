// vim:ts=8 sw=4
#ifndef __INC_CLIENTMANAGER_H__
#define __INC_CLIENTMANAGER_H__

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "../../common/stl.h"
#include "../../common/building.h"
#include "../../common/auction_table.h"

#include "Peer.h"
#include "DBManager.h"
#include "LoginData.h"

class CPlayerTableCache;
class CItemCache;
class CItemPriceListTableCache;

class CPacketInfo
{
    public:
	void Add(int32_t header);
	void Reset();

	std::map<int32_t, int32_t> m_map_info;
};

uint32_t CreatePlayerSaveQuery(char * pszQuery, uint32_t querySize, TPlayerTable * pkTab);

class CClientManager : public CNetBase, public singleton<CClientManager>
{
    public:
	typedef std::list<CPeer *>			TPeerList;
	typedef boost::unordered_map<uint32_t, CPlayerTableCache *> TPlayerTableCacheMap;
	typedef boost::unordered_map<uint32_t, CItemCache *> TItemCacheMap;
	typedef boost::unordered_set<CItemCache *, boost::hash<CItemCache*> > TItemCacheSet;
	typedef boost::unordered_map<uint32_t, TItemCacheSet *> TItemCacheSetPtrMap;
	typedef boost::unordered_map<uint32_t, CItemPriceListTableCache*> TItemPriceListCacheMap;
	typedef boost::unordered_map<int16_t, uint8_t> TChannelStatusMap;

	// MYSHOP_PRICE_LIST
	/// 아이템 가격정보 리스트 요청 정보
	/**
	 * first: Peer handle
	 * second: 요청한 플레이어의 ID
	 */
	typedef std::pair< uint32_t, uint32_t >		TItemPricelistReqInfo;
	// END_OF_MYSHOP_PRICE_LIST

	class ClientHandleInfo
	{
	    public:
		uint32_t	dwHandle;
		uint32_t	account_id;
		uint32_t	player_id;
		uint8_t	account_index;
		char	login[LOGIN_MAX_LEN + 1];
		char	safebox_password[SAFEBOX_PASSWORD_MAX_LEN + 1];
		char	ip[MAX_HOST_LENGTH + 1];

		TAccountTable * pAccountTable;
		TSafeboxTable * pSafebox;

		ClientHandleInfo(uint32_t argHandle, uint32_t dwPID = 0)
		{
		    dwHandle = argHandle;
		    pSafebox = NULL;
		    pAccountTable = NULL;
		    player_id = dwPID;
		};
		//독일선물기능용 생성자
		ClientHandleInfo(uint32_t argHandle, uint32_t dwPID, uint32_t accountId)
		{
		    dwHandle = argHandle;
		    pSafebox = NULL;
		    pAccountTable = NULL;
		    player_id = dwPID;
			account_id = accountId;
		};

		~ClientHandleInfo()
		{
		    if (pSafebox)
			{
				delete pSafebox;
				pSafebox = NULL;
			}
		}
	};

	public:
	CClientManager();
	~CClientManager();

	bool	Initialize();
	int32_t	GetCurrentTime();

	void	MainLoop();
	void	Quit();

	void	SetTablePostfix(const char* c_pszTablePostfix);
	void	SetPlayerIDStart(int32_t iIDStart);
	int32_t	GetPlayerIDStart() { return m_iPlayerIDStart; }

	int32_t	GetPlayerDeleteLevelLimit() { return m_iPlayerDeleteLevelLimit; }

	void	SetChinaEventServer(bool flag) { m_bChinaEventServer = flag; }
	bool	IsChinaEventServer() { return m_bChinaEventServer; }

	uint32_t	GetUserCount();	// 접속된 사용자 수를 리턴 한다.

	void	SendAllGuildSkillRechargePacket();
	void	SendTime();

	CPlayerTableCache *	GetPlayerCache(uint32_t id);
	void			PutPlayerCache(TPlayerTable * pNew);

	void			CreateItemCacheSet(uint32_t dwID);
	TItemCacheSet *		GetItemCacheSet(uint32_t dwID);
	void			FlushItemCacheSet(uint32_t dwID);

	CItemCache *		GetItemCache(uint32_t id);
	void			PutItemCache(TPlayerItem * pNew, bool bSkipQuery = false);
	bool			DeleteItemCache(uint32_t id);

	void			UpdatePlayerCache();
	void			UpdateItemCache();

	// MYSHOP_PRICE_LIST
	/// 가격정보 리스트 캐시를 가져온다.
	/**
	 * @param [in]	dwID 가격정보 리스트의 소유자.(플레이어 ID)
	 * @return	가격정보 리스트 캐시의 포인터
	 */
	CItemPriceListTableCache*	GetItemPriceListCache(uint32_t dwID);

	/// 가격정보 리스트 캐시를 넣는다.
	/**
	 * @param [in]	pItemPriceList 캐시에 넣을 아이템 가격정보 리스트
	 *
	 * 캐시가 이미 있으면 Update 가 아닌 replace 한다.
	 */
	void			PutItemPriceListCache(const TItemPriceListTable* pItemPriceList);


	/// Flush 시간이 만료된 아이템 가격정보 리스트 캐시를 Flush 해주고 캐시에서 삭제한다.
	void			UpdateItemPriceListCache(void);
	// END_OF_MYSHOP_PRICE_LIST


	void			SendGuildSkillUsable(uint32_t guild_id, uint32_t dwSkillVnum, bool bUsable);

	void			SetCacheFlushCountLimit(int32_t iLimit);

	template <class Func>
	Func		for_each_peer(Func f);

	CPeer *		GetAnyPeer();

	void			ForwardPacket(uint8_t header, const void* data, int32_t size, uint8_t bChannel = 0, CPeer * except = NULL);

	void			SendNotice(const char * c_pszFormat, ...);

	char*			GetCommand(char* str);					//독일선물기능에서 명령어 얻는 함수
	void			ItemAward(CPeer * peer, char* login);	//독일 선물 기능

    protected:
	void	Destroy();

    private:
	bool		InitializeTables();
	bool		InitializeShopTable();
	bool		InitializeMobTable();
	bool		InitializeItemTable();
	bool		InitializeQuestItemTable();
	bool		InitializeSkillTable();
	bool		InitializeRefineTable();
	bool		InitializeBanwordTable();
	bool		InitializeItemAttrTable();
	bool		InitializeItemRareTable();
	bool		InitializeLandTable();
	bool		InitializeObjectProto();
	bool		InitializeObjectTable();
	bool		InitializeMonarch();

	// mob_proto.txt, item_proto.txt에서 읽은 mob_proto, item_proto를 real db에 반영.
	//	item_proto, mob_proto를 db에 반영하지 않아도, 게임 돌아가는데는 문제가 없지만,
	//	운영툴 등에서 db의 item_proto, mob_proto를 읽어 쓰기 때문에 문제가 발생한다.
	bool		MirrorMobTableIntoDB();
	bool		MirrorItemTableIntoDB();

	void		AddPeer(socket_t fd);
	void		RemovePeer(CPeer * pPeer);
	CPeer *		GetPeer(uint32_t ident);

	int32_t		AnalyzeQueryResult(SQLMsg * msg);
	int32_t		AnalyzeErrorMsg(CPeer * peer, SQLMsg * msg);

	int32_t		Process();

        void            ProcessPackets(CPeer * peer);

	CLoginData *	GetLoginData(uint32_t dwKey);
	CLoginData *	GetLoginDataByLogin(const char * c_pszLogin);
	CLoginData *	GetLoginDataByAID(uint32_t dwAID);

	void		InsertLoginData(CLoginData * pkLD);
	void		DeleteLoginData(CLoginData * pkLD);

	bool		InsertLogonAccount(const char * c_pszLogin, uint32_t dwHandle, const char * c_pszIP);
	bool		DeleteLogonAccount(const char * c_pszLogin, uint32_t dwHandle);
	bool		FindLogonAccount(const char * c_pszLogin);

	void		GuildCreate(CPeer * peer, uint32_t dwGuildID);
	void		GuildSkillUpdate(CPeer * peer, TPacketGuildSkillUpdate* p);
	void		GuildExpUpdate(CPeer * peer, TPacketGuildExpUpdate* p);
	void		GuildAddMember(CPeer * peer, TPacketGDGuildAddMember* p);
	void		GuildChangeGrade(CPeer * peer, TPacketGuild* p);
	void		GuildRemoveMember(CPeer * peer, TPacketGuild* p);
	void		GuildChangeMemberData(CPeer * peer, TPacketGuildChangeMemberData* p);
	void		GuildDisband(CPeer * peer, TPacketGuild * p);
	void		GuildWar(CPeer * peer, TPacketGuildWar * p);
	void		GuildWarScore(CPeer * peer, TPacketGuildWarScore * p);
	void		GuildChangeLadderPoint(TPacketGuildLadderPoint* p);
	void		GuildUseSkill(TPacketGuildUseSkill* p);
	void		GuildDepositMoney(TPacketGDGuildMoney* p);
	void		GuildWithdrawMoney(CPeer* peer, TPacketGDGuildMoney* p);
	void		GuildWithdrawMoneyGiveReply(TPacketGDGuildMoneyWithdrawGiveReply* p);
	void		GuildWarBet(TPacketGDGuildWarBet * p);
	void		GuildChangeMaster(TPacketChangeGuildMaster* p);

	void		SetGuildWarEndTime(uint32_t guild_id1, uint32_t guild_id2, int32_t tEndTime);

	void		QUERY_BOOT(CPeer * peer, TPacketGDBoot * p);

	void		QUERY_LOGIN(CPeer * peer, uint32_t dwHandle, SLoginPacket* data);
	void		QUERY_LOGOUT(CPeer * peer, uint32_t dwHandle, const char *);

	void		RESULT_LOGIN(CPeer * peer, SQLMsg *msg);

	void		QUERY_PLAYER_LOAD(CPeer * peer, uint32_t dwHandle, TPlayerLoadPacket*);
	void		RESULT_COMPOSITE_PLAYER(CPeer * peer, SQLMsg * pMsg, uint32_t dwQID);
	void		RESULT_PLAYER_LOAD(CPeer * peer, MYSQL_RES * pRes, ClientHandleInfo * pkInfo);
	void		RESULT_ITEM_LOAD(CPeer * peer, MYSQL_RES * pRes, uint32_t dwHandle, uint32_t dwPID);
	void		RESULT_QUEST_LOAD(CPeer * pkPeer, MYSQL_RES * pRes, uint32_t dwHandle, uint32_t dwPID);
	void		RESULT_AFFECT_LOAD(CPeer * pkPeer, MYSQL_RES * pRes, uint32_t dwHandle);

	// PLAYER_INDEX_CREATE_BUG_FIX
	void		RESULT_PLAYER_INDEX_CREATE(CPeer *pkPeer, SQLMsg *msg);
	// END_PLAYER_INDEX_CREATE_BUG_FIX
 
	// MYSHOP_PRICE_LIST
	/// 가격정보 로드 쿼리에 대한 Result 처리
	/**
	 * @param	peer 가격정보를 요청한 Game server 의 peer 객체 포인터
	 * @param	pMsg 쿼리의 Result 로 받은 객체의 포인터
	 *
	 * 로드된 가격정보 리스트를 캐시에 저장하고 peer 에게 리스트를 보내준다.
	 */
	void		RESULT_PRICELIST_LOAD(CPeer* peer, SQLMsg* pMsg);

	/// 가격정보 업데이트를 위한 로드 쿼리에 대한 Result 처리
	/**
	 * @param	pMsg 쿼리의 Result 로 받은 객체의 포인터
	 *
	 * 로드된 정보로 가격정보 리스트 캐시를 만들고 업데이트 받은 가격정보로 업데이트 한다.
	 */
	void		RESULT_PRICELIST_LOAD_FOR_UPDATE(SQLMsg* pMsg);
	// END_OF_MYSHOP_PRICE_LIST

	void		QUERY_PLAYER_SAVE(CPeer * peer, uint32_t dwHandle, TPlayerTable*);

	void		__QUERY_PLAYER_CREATE(CPeer * peer, uint32_t dwHandle, TPlayerCreatePacket *);
	void		__QUERY_PLAYER_DELETE(CPeer * peer, uint32_t dwHandle, TPlayerDeletePacket *);
	void		__RESULT_PLAYER_DELETE(CPeer * peer, SQLMsg* msg);

	void		QUERY_PLAYER_COUNT(CPeer * pkPeer, TPlayerCountPacket *);

	void		QUERY_ITEM_SAVE(CPeer * pkPeer, const char * c_pData);
	void		QUERY_ITEM_DESTROY(CPeer * pkPeer, const char * c_pData);
	void		QUERY_ITEM_FLUSH(CPeer * pkPeer, const char * c_pData);


	void		QUERY_QUEST_SAVE(CPeer * pkPeer, TQuestTable *, uint32_t dwLen);
	void		QUERY_ADD_AFFECT(CPeer * pkPeer, TPacketGDAddAffect * p);
	void		QUERY_REMOVE_AFFECT(CPeer * pkPeer, TPacketGDRemoveAffect * p);

	void		QUERY_SAFEBOX_LOAD(CPeer * pkPeer, uint32_t dwHandle, TSafeboxLoadPacket *, bool bMall);
	void		QUERY_SAFEBOX_SAVE(CPeer * pkPeer, TSafeboxTable * pTable);
	void		QUERY_SAFEBOX_CHANGE_SIZE(CPeer * pkPeer, uint32_t dwHandle, TSafeboxChangeSizePacket * p);
	void		QUERY_SAFEBOX_CHANGE_PASSWORD(CPeer * pkPeer, uint32_t dwHandle, TSafeboxChangePasswordPacket * p);

	void		RESULT_SAFEBOX_LOAD(CPeer * pkPeer, SQLMsg * msg);
	void		RESULT_SAFEBOX_CHANGE_SIZE(CPeer * pkPeer, SQLMsg * msg);
	void		RESULT_SAFEBOX_CHANGE_PASSWORD(CPeer * pkPeer, SQLMsg * msg);
	void		RESULT_SAFEBOX_CHANGE_PASSWORD_SECOND(CPeer * pkPeer, SQLMsg * msg);

	void		QUERY_EMPIRE_SELECT(CPeer * pkPeer, uint32_t dwHandle, TEmpireSelectPacket * p);
	void		QUERY_SETUP(CPeer * pkPeer, uint32_t dwHandle, const char * c_pData);

	void		SendPartyOnSetup(CPeer * peer);

	void		QUERY_HIGHSCORE_REGISTER(CPeer * peer, TPacketGDHighscore* data);
	void		RESULT_HIGHSCORE_REGISTER(CPeer * pkPeer, SQLMsg * msg);

	void		QUERY_FLUSH_CACHE(CPeer * pkPeer, const char * c_pData);

	void		QUERY_PARTY_CREATE(CPeer * peer, TPacketPartyCreate* p);
	void		QUERY_PARTY_DELETE(CPeer * peer, TPacketPartyDelete* p);
	void		QUERY_PARTY_ADD(CPeer * peer, TPacketPartyAdd* p);
	void		QUERY_PARTY_REMOVE(CPeer * peer, TPacketPartyRemove* p);
	void		QUERY_PARTY_STATE_CHANGE(CPeer * peer, TPacketPartyStateChange* p);
	void		QUERY_PARTY_SET_MEMBER_LEVEL(CPeer * peer, TPacketPartySetMemberLevel* p);

	void		QUERY_RELOAD_PROTO();

	void		QUERY_CHANGE_NAME(CPeer * peer, uint32_t dwHandle, TPacketGDChangeName * p);
	void		GetPlayerFromRes(TPlayerTable * player_table, MYSQL_RES* res);

	void		QUERY_SMS(CPeer * pkPeer, TPacketGDSMS * p);
	void		QUERY_LOGIN_KEY(CPeer * pkPeer, TPacketGDLoginKey * p);

	void		AddGuildPriv(TPacketGiveGuildPriv* p);
	void		AddEmpirePriv(TPacketGiveEmpirePriv* p);
	void		AddCharacterPriv(TPacketGiveCharacterPriv* p);

	void		MoneyLog(TPacketMoneyLog* p);

	void		QUERY_AUTH_LOGIN(CPeer * pkPeer, uint32_t dwHandle, TPacketGDAuthLogin * p);

	void		QUERY_LOGIN_BY_KEY(CPeer * pkPeer, uint32_t dwHandle, TPacketGDLoginByKey * p);
	void		RESULT_LOGIN_BY_KEY(CPeer * peer, SQLMsg * msg);

	void		ChargeCash(const TRequestChargeCash * p);

	void		LoadEventFlag();
	void		SetEventFlag(TPacketSetEventFlag* p);
	void		SendEventFlagsOnSetup(CPeer* peer);

	void		BillingExpire(TPacketBillingExpire * p);
	void		BillingCheck(const char * data);

	void		SendAllLoginToBilling();
	void		SendLoginToBilling(CLoginData * pkLD, bool bLogin);

	// 결혼
	void		MarriageAdd(TPacketMarriageAdd * p);
	void		MarriageUpdate(TPacketMarriageUpdate * p);
	void		MarriageRemove(TPacketMarriageRemove * p);

	void		WeddingRequest(TPacketWeddingRequest * p);
	void		WeddingReady(TPacketWeddingReady * p);
	void		WeddingEnd(TPacketWeddingEnd * p);

	// MYSHOP_PRICE_LIST
	// 개인상점 가격정보

	/// 아이템 가격정보 리스트 업데이트 패킷(HEADER_GD_MYSHOP_PRICELIST_UPDATE) 처리함수
	/**
	 * @param [in]	pPacket 패킷 데이터의 포인터
	 */
	void		MyshopPricelistUpdate(const TPacketMyshopPricelistHeader* pPacket);

	/// 아이템 가격정보 리스트 요청 패킷(HEADER_GD_MYSHOP_PRICELIST_REQ) 처리함수
	/**
	 * @param	peer 패킷을 보낸 Game server 의 peer 객체의 포인터
	 * @param [in]	dwHandle 가격정보를 요청한 peer 의 핸들
	 * @param [in]	dwPlayerID 가격정보 리스트를 요청한 플레이어의 ID
	 */
	void		MyshopPricelistRequest(CPeer* peer, uint32_t dwHandle, uint32_t dwPlayerID);
	// END_OF_MYSHOP_PRICE_LIST

	// Building
	void		CreateObject(TPacketGDCreateObject * p);
	void		DeleteObject(uint32_t dwID);
	void		UpdateLand(uint32_t * pdw);

	// VCard
	void 		VCard(TPacketGDVCard * p);
	void		VCardProcess();

	// BLOCK_CHAT
	void		BlockChat(TPacketBlockChat * p);
	// END_OF_BLOCK_CHAT
   
    private:
	int32_t					m_looping;
	socket_t				m_fdAccept;	// 접속 받는 소켓
	TPeerList				m_peerList;

	CPeer *					m_pkAuthPeer;

	// LoginKey, LoginData pair
	typedef boost::unordered_map<uint32_t, CLoginData *> TLoginDataByLoginKey;
	TLoginDataByLoginKey			m_map_pkLoginData;

	// Login LoginData pair
	typedef boost::unordered_map<std::string, CLoginData *> TLoginDataByLogin;
	TLoginDataByLogin			m_map_pkLoginDataByLogin;
	
	// AccountID LoginData pair
	typedef boost::unordered_map<uint32_t, CLoginData *> TLoginDataByAID;
	TLoginDataByAID				m_map_pkLoginDataByAID;

	// Login LoginData pair (실제 로그인 되어있는 계정)
	typedef boost::unordered_map<std::string, CLoginData *> TLogonAccountMap;
	TLogonAccountMap			m_map_kLogonAccount;

	int32_t					m_iPlayerIDStart;
	int32_t					m_iPlayerDeleteLevelLimit;
	int32_t					m_iPlayerDeleteLevelLimitLower;
	bool					m_bChinaEventServer;

	std::vector<TMobTable>			m_vec_mobTable;
	std::vector<TItemTable>			m_vec_itemTable;
	std::map<uint32_t, TItemTable *>		m_map_itemTableByVnum;

	int32_t					m_iShopTableSize;
	TShopTable *				m_pShopTable;

	int32_t					m_iRefineTableSize;
	TRefineTable*				m_pRefineTable;

	std::vector<TSkillTable>		m_vec_skillTable;
	std::vector<TBanwordTable>		m_vec_banwordTable;
	std::vector<TItemAttrTable>		m_vec_itemAttrTable;
	std::vector<TItemAttrTable>		m_vec_itemRareTable;

	std::vector<building::TLand>		m_vec_kLandTable;
	std::vector<building::TObjectProto>	m_vec_kObjectProto;
	std::map<uint32_t, building::TObject *>	m_map_pkObjectTable;

	std::queue<TPacketGDVCard>		m_queue_vcard;

	bool					m_bShutdowned;

	TPlayerTableCacheMap			m_map_playerCache;  // 플레이어 id가 key

	TItemCacheMap				m_map_itemCache;  // 아이템 id가 key
	TItemCacheSetPtrMap			m_map_pkItemCacheSetPtr;  // 플레이어 id가 key, 이 플레이어가 어떤 아이템 캐쉬를 가지고 있나?

	// MYSHOP_PRICE_LIST
	/// 플레이어별 아이템 가격정보 리스트 map. key: 플레이어 ID, value: 가격정보 리스트 캐시
	TItemPriceListCacheMap m_mapItemPriceListCache;  ///< 플레이어별 아이템 가격정보 리스트
	// END_OF_MYSHOP_PRICE_LIST

	TChannelStatusMap m_mChannelStatus;

	struct TPartyInfo
	{
	    uint8_t bRole;
	    uint8_t bLevel;

		TPartyInfo() :bRole(0), bLevel(0)
		{
		}
	};

	typedef std::map<uint32_t, TPartyInfo>	TPartyMember;
	typedef std::map<uint32_t, TPartyMember>	TPartyMap;
	typedef std::map<uint8_t, TPartyMap>	TPartyChannelMap;
	TPartyChannelMap m_map_pkChannelParty;

	typedef std::map<std::string, int32_t>	TEventFlagMap;
	TEventFlagMap m_map_lEventFlag;

	uint8_t					m_bLastHeader;
	int32_t					m_iCacheFlushCount;
	int32_t					m_iCacheFlushCountLimit;

    private :
	TItemIDRangeTable m_itemRange;

    public :
	bool InitializeNowItemID();
	uint32_t GetItemID();
	uint32_t GainItemID();
	TItemIDRangeTable GetItemRange() { return m_itemRange; }

	//BOOT_LOCALIZATION
    public:
	/* 로컬 정보 초기화 
	 **/
	bool InitializeLocalization(); 

    private:
	std::vector<tLocale> m_vec_Locale;
	//END_BOOT_LOCALIZATION
	//ADMIN_MANAGER

	bool __GetAdminInfo(const char *szIP, std::vector<tAdminInfo> & rAdminVec);
	bool __GetHostInfo(std::vector<std::string> & rIPVec);
	//END_ADMIN_MANAGER

		
	//RELOAD_ADMIN
	void ReloadAdmin(CPeer * peer, TPacketReloadAdmin * p);
	//END_RELOAD_ADMIN
	void BreakMarriage(CPeer * peer, const char * data);

	struct TLogoutPlayer
	{
	    uint32_t	pid;
	    int32_t	time;

	    bool operator < (const TLogoutPlayer & r) 
	    {
		return (pid < r.pid);
	    }
	};

	typedef boost::unordered_map<uint32_t, TLogoutPlayer*> TLogoutPlayerMap;
	TLogoutPlayerMap m_map_logout;
	
	void InsertLogoutPlayer(uint32_t pid);
	void DeleteLogoutPlayer(uint32_t pid);
	void UpdateLogoutPlayer();
	void UpdateItemCacheSet(uint32_t pid);

	void FlushPlayerCacheSet(uint32_t pid);

	//MONARCH
	void Election(CPeer * peer, uint32_t dwHandle, const char * p);
	void Candidacy(CPeer * peer, uint32_t dwHandle, const char * p);
	void AddMonarchMoney(CPeer * peer, uint32_t dwHandle, const char * p);
	void TakeMonarchMoney(CPeer * peer, uint32_t dwHandle, const char * p);
	void ComeToVote(CPeer * peer, uint32_t dwHandle, const char * p);
	void RMCandidacy(CPeer * peer, uint32_t dwHandle, const char * p);
	void SetMonarch(CPeer * peer, uint32_t dwHandle, const char * p);
	void RMMonarch(CPeer * peer, uint32_t dwHandle, const char * p);
								

	void DecMonarchMoney(CPeer * peer, uint32_t dwHandle, const char * p);
	//END_MONARCH

	void ChangeMonarchLord(CPeer* peer, uint32_t dwHandle, TPacketChangeMonarchLord* info);
	void BlockException(TPacketBlockException *data);

	void SendSpareItemIDRange(CPeer* peer);

	void UpdateHorseName(TPacketUpdateHorseName* data, CPeer* peer);
	void AckHorseName(uint32_t dwPID, CPeer* peer);
	void DeleteLoginKey(TPacketDC *data);
	void ResetLastPlayerID(const TPacketNeedLoginLogInfo* data);
	//delete gift notify icon
	void DeleteAwardId(TPacketDeleteAwardID* data);
	void UpdateChannelStatus(TChannelStatus* pData);
	void RequestChannelStatus(CPeer* peer, uint32_t dwHandle);
#ifdef __AUCTION__
	void EnrollInAuction (CPeer * peer, uint32_t owner_id, AuctionEnrollProductInfo* data);
	void EnrollInSale (CPeer * peer, uint32_t owner_id, AuctionEnrollSaleInfo* data);
	void EnrollInWish (CPeer * peer, uint32_t wisher_id, AuctionEnrollWishInfo* data);
	void AuctionBid (CPeer * peer, uint32_t bidder_id, AuctionBidInfo* data);
	void AuctionImpur (CPeer * peer, uint32_t purchaser_id, AuctionImpurInfo* data);
	void AuctionGetAuctionedItem (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionBuySoldItem (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionCancelAuction (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionCancelWish (CPeer * peer, uint32_t actor_id, uint32_t item_num);
	void AuctionCancelSale (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionDeleteAuctionItem (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionDeleteSaleItem (CPeer * peer, uint32_t actor_id, uint32_t item_id);
	void AuctionReBid (CPeer * peer, uint32_t bidder_id, AuctionBidInfo* data);
	void AuctionBidCancel (CPeer * peer, uint32_t bidder_id, uint32_t item_id);
#endif
};

template<class Func>	
Func CClientManager::for_each_peer(Func f)
{
    TPeerList::iterator it;
    for (it = m_peerList.begin(); it!=m_peerList.end();++it)
    {
	f(*it);
    }
    return f;
}
#endif
