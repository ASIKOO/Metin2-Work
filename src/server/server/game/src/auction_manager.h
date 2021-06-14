#ifndef __INC_AUCTION_MANAGER_H
#define __INC_AUCTION_MANAGER_H

#include "../../libsql/AsyncSQL.h"
#include "../../common/auction_table.h"
#include <boost/unordered_map.hpp>
#include <algorithm>

#define GRADE_LOW 30
#define GRADE_MID 60
#define GRADE_HIGH 90

template<>
class hash<std::pair <uint32_t, uint32_t> >
{	// hash functor
public:
	typedef std::pair <uint32_t, uint32_t> _Kty;

	uint32_t operator()(const _Kty& _Keyval) const
	{	// hash _Keyval to uint32_t value by pseudorandomizing transform
		ldiv_t _Qrem = ldiv((uint32_t)_Keyval.first + (uint32_t)_Keyval.second, 127773);

		_Qrem.rem = 16807 * _Qrem.rem - 2836 * _Qrem.quot;
		if (_Qrem.rem < 0)
			_Qrem.rem += 2147483647;
		return ((uint32_t)_Qrem.rem);
	}
};

bool CompareItemInfoByItemNameAC (TAuctionItemInfo* i, TAuctionItemInfo* j);
bool CompareItemInfoByItemNameDC (TAuctionItemInfo* i, TAuctionItemInfo* j);

bool CompareItemInfoByCategoryAC (TAuctionItemInfo* i, TAuctionItemInfo* j);
bool CompareItemInfoByCategoryDC (TAuctionItemInfo* i, TAuctionItemInfo* j);

bool CompareItemInfoByTimeAC (TAuctionItemInfo* i, TAuctionItemInfo* j);
bool CompareItemInfoByTimeDC (TAuctionItemInfo* i, TAuctionItemInfo* j);

bool CompareItemInfoByCharNameAC (TAuctionItemInfo* i, TAuctionItemInfo* j);
bool CompareItemInfoByCharNameDC (TAuctionItemInfo* i, TAuctionItemInfo* j);

bool CompareItemInfoByPriceAC (TAuctionItemInfo* i, TAuctionItemInfo* j);
bool CompareItemInfoByPriceDC (TAuctionItemInfo* i, TAuctionItemInfo* j);

class AuctionBoard
{
public:
	AuctionBoard() {}
	~AuctionBoard() {}

	TAuctionItemInfo* GetItemInfo (uint32_t key);
	bool DeleteItemInfo (uint32_t key);
	bool InsertItemInfo (TAuctionItemInfo* item_info);
	bool UpdateItemInfo (TAuctionItemInfo* item_info);


private:
	typedef boost::unordered_map <uint32_t, TAuctionItemInfo*> TItemInfoMap;
	TItemInfoMap item_map;

	typedef std::map <uint32_t, TAuctionItemInfo*> TItemMap;
	typedef boost::unordered_map <uint32_t, TItemMap*> TPCMap;

	TPCMap offer_map;

	// sorting을 위한 members
public:
	typedef std::vector <TAuctionItemInfo*> TItemInfoVec;
private:
	typedef std::map <std::string, TItemInfoVec*> SortByItemName;

	SortByItemName item_name_map;

	void Sort(TItemInfoVec& vec, uint8_t order);

public:
	void SortedItemInfos (TItemInfoVec& vec, uint8_t grade, uint8_t category, int32_t start_idx, uint8_t size, uint8_t order[5]);

	// 나의 경매장을 위한 함수.
	void YourItemInfoList (TItemInfoVec& vec, uint32_t player_id, int32_t start_idx, uint8_t size);

};
class SaleBoard
{
private:
	typedef boost::unordered_map <uint32_t, TSaleItemInfo*> TItemInfoMap;
	TItemInfoMap item_map;
	
	typedef std::map <uint32_t, TSaleItemInfo*> TItemMap;
	typedef boost::unordered_map <uint32_t, TItemMap*> TPCMap;

	TPCMap wisher_map;
	TPCMap seller_map;
	
	bool DeleteFromPCMap (TPCMap& pc_map, uint32_t player_id, uint32_t item_id);
	bool InsertInPCMap (TPCMap& pc_map, uint32_t player_id, TSaleItemInfo* item_info);

public:
	SaleBoard() {}
	~SaleBoard() {}

	typedef std::vector <TSaleItemInfo*> TItemInfoVec;
	void WisherItemInfoList (TItemInfoVec& vec, uint32_t wisher_id, int32_t start_idx, uint8_t size);

	TSaleItemInfo* GetItemInfo (uint32_t key);
	bool DeleteItemInfo (uint32_t key);
	bool InsertItemInfo (TSaleItemInfo* item_info);
};

class WishBoard
{
private:
	typedef std::map <uint32_t, TWishItemInfo*> TItemMap;
	typedef boost::unordered_map <uint32_t, TItemMap*> TPCMap;
	TPCMap wisher_map;

public:
	typedef TWishItemInfo ItemInfo;

	WishBoard() {}
	~WishBoard() {}

	TWishItemInfo* GetItemInfo (uint32_t wisher_id, uint32_t item_num);
	bool DeleteItemInfo (uint32_t wisher_id, uint32_t item_num);
	bool InsertItemInfo (TWishItemInfo* item_info);
};

class MyBidBoard
{
private:
	typedef std::pair <int32_t, bool> BidInfo;
	typedef std::map <uint32_t, BidInfo > TItemMap;
	typedef boost::unordered_map <uint32_t, TItemMap*> TMyBidBoard;
	// bidder_id가 key
	TMyBidBoard pc_map;

public:
	MyBidBoard() {}
	~MyBidBoard() {}

	typedef std::vector <uint32_t> TItemVec;

	void YourBidInfo (TItemVec& vec, uint32_t bidder_id, int32_t start_idx, int32_t size);

	BidInfo GetMoney (uint32_t player_id, uint32_t item_id);
	bool Delete (uint32_t player_id, uint32_t item_id);
	// 이미 있으면 덮어 씌운다.
	void Insert (uint32_t player_id, uint32_t item_id, int32_t money);
	void Lock (uint32_t player_id, uint32_t item_id);
	void UnLock (uint32_t player_id, uint32_t item_id);
};

class AuctionManager : public singleton <AuctionManager> 
{
private :
	typedef boost::unordered_map<uint32_t, LPITEM> TItemMap;
	TItemMap auction_item_map;

	// auction에 등록된 정보 중 가격, 등등 아이템 테이블에 포함되지 않는 정보들을 관리하는 것들
	AuctionBoard Auction;
	SaleBoard Sale;
	WishBoard Wish;
	MyBidBoard MyBid;

public:
	bool InsertItem (LPITEM item);
	bool InsertItem (TPlayerItem* player_item);
	LPITEM GetInventoryItem (uint32_t item_id);
	bool DeleteItem (uint32_t item_id);

	bool InsertAuctionItemInfo (TAuctionItemInfo* item_info);
	TAuctionItemInfo* GetAuctionItemInfo (uint32_t item_id)
	{
		return Auction.GetItemInfo (item_id);
	}

	bool InsertSaleItemInfo (TSaleItemInfo* item_info);
	TSaleItemInfo* GetSaleItemInfo (uint32_t item_id)
	{
		return Sale.GetItemInfo (item_id);
	}

	bool InsertWishItemInfo (TWishItemInfo* item_info);
	TWishItemInfo* GetWishItemInfo (uint32_t wisher_id, uint32_t item_id)
	{
		return Wish.GetItemInfo (wisher_id, item_id);
	}

	void YourBidItemInfoList (AuctionBoard::TItemInfoVec& vec, uint32_t bidder_id, int32_t start_idx, int32_t size);

	void Boot (const char* &pdata, uint16_t size);

	void get_auction_list (LPCHARACTER ch, int32_t start_idx, int32_t size, int32_t cond);
	void get_my_auction_list (LPCHARACTER ch, int32_t start_idx, int32_t size);
	void get_my_purchase_list (LPCHARACTER ch, int32_t start_idx, int32_t size);
	void enroll_auction (LPCHARACTER ch, LPITEM item, uint8_t empire, int32_t bidPrice, int32_t immidiatePurchasePrice);

	void recv_result_auction (uint32_t commander_id, TPacketDGResultAuction* cmd_result);

	void bid (LPCHARACTER ch, uint32_t item_id, int32_t price);
	void immediate_purchase (LPCHARACTER ch, uint32_t item_id);

	void enroll_sale (LPCHARACTER ch, LPITEM item, uint32_t wisher_id, int32_t salePrice);
	void enroll_wish (LPCHARACTER ch, uint32_t item_num, uint8_t empire, int32_t wishPrice);

	void get_auctioned_item (LPCHARACTER ch, uint32_t item_id, uint32_t item_num);
	void buy_sold_item (LPCHARACTER ch, uint32_t item_id);
	void cancel_auction (LPCHARACTER ch, uint32_t item_id);
	void cancel_wish (LPCHARACTER ch, uint32_t item_num);
	void cancel_sale (LPCHARACTER ch, uint32_t item_id);
	
	void rebid (LPCHARACTER ch, uint32_t item_id, int32_t price);
	void bid_cancel (LPCHARACTER ch, uint32_t item_id);
/*	
	void close_auction (LPCHARACTER ch);*/
};

#endif
