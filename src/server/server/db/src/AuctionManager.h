#ifdef __AUCTION__

#ifndef __INC_AUCTION_MANAGER_H__
#define __INC_AUCTION_MANAGER_H__

#include <boost/unordered_map.hpp>
#include "Cache.h"
#include "../../common/auction_table.h"

class CItemCache;
class CAuctionItemInfoCache;
class CSaleItemInfoCache;
class CWishItemInfoCache;

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


class AuctionBoard
{
public:
	typedef uint32_t Key;
	typedef CAuctionItemInfoCache ItemInfoCache;
	typedef TAuctionItemInfo ItemInfo;
	

public:
	AuctionBoard() {}
	~AuctionBoard() {}

	void Boot(CPeer* peer)
	{
		peer->EncodeWORD(sizeof(ItemInfo));
		peer->EncodeWORD(item_cache_map.size());

		TItemInfoCacheMap::iterator it = item_cache_map.begin();

		while (it != item_cache_map.end())
			peer->Encode((it++)->second->Get(), sizeof(ItemInfo));
	}
	
	uint32_t Size()
	{
		return item_cache_map.size();
	}

	ItemInfoCache* GetItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return NULL;
		else
			return it->second;
	}

	bool DeleteItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return false;
		else
		{
			it->second->Delete();
			item_cache_map.erase(it);
			return true;
		}
	}

	bool InsertItemInfo (ItemInfo *pNew, bool bSkipQuery = false)
	{
		ItemInfoCache* c = GetItemInfoCache (Key (pNew->item_id));
		if (c != NULL)
		{
			return false;
		}

		c = new ItemInfoCache();

		c->Put(pNew, bSkipQuery);

		item_cache_map.insert(TItemInfoCacheMap::value_type(pNew->item_id, c));
		c->Flush();

		return true;
	}
private:
	typedef boost::unordered_map <Key, ItemInfoCache *> TItemInfoCacheMap;
	TItemInfoCacheMap item_cache_map;
};

class SaleBoard 
{
public:
	typedef uint32_t Key;
	typedef CSaleItemInfoCache ItemInfoCache;
	typedef TSaleItemInfo ItemInfo;
	
	SaleBoard() {}
	~SaleBoard() {}

	void Boot(CPeer* peer)
	{
		peer->EncodeWORD(sizeof(ItemInfo));
		peer->EncodeWORD(item_cache_map.size());

		TItemInfoCacheMap::iterator it = item_cache_map.begin();

		while (it != item_cache_map.end())
			peer->Encode((it++)->second->Get(), sizeof(ItemInfo));
	}
	
	uint32_t Size()
	{
		return item_cache_map.size();
	}

	ItemInfoCache* GetItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return NULL;
		else
			return it->second;
	}

	bool DeleteItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return false;
		else
		{
			it->second->Delete();
			item_cache_map.erase(it);
			return true;
		}
	}

	bool InsertItemInfo (ItemInfo *pNew, bool bSkipQuery = false)
	{
		ItemInfoCache* c = GetItemInfoCache (Key (pNew->item_id));
		if (c != NULL)
		{
			return false;
		}

		c = new ItemInfoCache();

		c->Put(pNew, bSkipQuery);

		item_cache_map.insert(TItemInfoCacheMap::value_type(pNew->item_id, c));
		c->Flush();

		return true;
	}

private:
	typedef boost::unordered_map <Key, ItemInfoCache *> TItemInfoCacheMap;
	TItemInfoCacheMap item_cache_map;
};

class WishBoard 
{
public:
	typedef std::pair <uint32_t, uint32_t> Key;
	typedef CWishItemInfoCache ItemInfoCache;
	typedef TWishItemInfo ItemInfo;
	
	WishBoard() {}
	virtual ~WishBoard() {}

	void Boot(CPeer* peer)
	{
		peer->EncodeWORD(sizeof(ItemInfo));
		peer->EncodeWORD(item_cache_map.size());

		TItemInfoCacheMap::iterator it = item_cache_map.begin();

		while (it != item_cache_map.end())
			peer->Encode((it++)->second->Get(), sizeof(ItemInfo));
	}
	
	uint32_t Size()
	{
		return item_cache_map.size();
	}

	ItemInfoCache* GetItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return NULL;
		else
			return it->second;
	}

	bool DeleteItemInfoCache (Key key)
	{
		TItemInfoCacheMap::iterator it = item_cache_map.find (key);
		if (it == item_cache_map.end())
			return false;
		else
		{
			it->second->Delete();
			item_cache_map.erase(it);
			return true;
		}
	}

	bool InsertItemInfo (ItemInfo *pNew, bool bSkipQuery = false)
	{
		ItemInfoCache* c = GetItemInfoCache (Key (pNew->item_num, pNew->offer_id));
		if (c != NULL)
		{
			return false;
		}

		c = new ItemInfoCache();

		c->Put(pNew, bSkipQuery);

		item_cache_map.insert(TItemInfoCacheMap::value_type(Key (pNew->item_num, pNew->offer_id), c));
		c->Flush();

		return true;
	}
private:
	typedef boost::unordered_map <Key, ItemInfoCache *> TItemInfoCacheMap;
	TItemInfoCacheMap item_cache_map;
};

// pc가 입찰에 참여했던 경매를 관리.
class MyBidBoard
{
public:
	MyBidBoard() {}
	~MyBidBoard() {}

	void Boot(CPeer* peer);
	uint32_t Size();
	
	int32_t GetMoney (uint32_t player_id, uint32_t item_id);
	bool Delete (uint32_t player_id, uint32_t item_id);
	// 이미 있으면 덮어 씌운다.
	void Insert (uint32_t player_id, uint32_t item_id, int32_t money);

private:
	typedef std::map <uint32_t, int32_t> TItemMap;
	typedef boost::unordered_map <uint32_t, TItemMap*> TMyBidBoard;
	TMyBidBoard pc_map;
};

class AuctionManager : public singleton <AuctionManager>
{
private:
	// auction에 등록된 아이템들.
	typedef boost::unordered_map<uint32_t, CItemCache *> TItemCacheMap;
	TItemCacheMap auction_item_cache_map;

	// auction에 등록된 정보 중 가격, 등등 아이템 테이블에 포함되지 않는 정보들을 관리하는 것들
	AuctionBoard Auction;
	SaleBoard Sale;
	WishBoard Wish;
	MyBidBoard MyBid;

public:
	AuctionManager();
	~AuctionManager();

	void Initialize ();
	void LoadAuctionItem ();

	void LoadAuctionInfo ();
	void LoadSaleInfo ();
	void LoadWishInfo ();
	void LoadMyBidInfo ();

	void Boot(CPeer* peer);

	bool InsertItemCache (CItemCache *item_cache, bool bSkipQuery = false);
	bool InsertItemCache (TPlayerItem * pNew, bool bSkipQuery = false);
	bool DeleteItemCache (uint32_t item_id);
	CItemCache* GetItemCache (uint32_t item_id);

	uint32_t GetAuctionItemSize()
	{
		return auction_item_cache_map.size();
	}
	uint32_t GetAuctionSize()
	{
		return Auction.Size();
	}
	uint32_t GetSaleSize()
	{
		return Sale.Size();
	}
	uint32_t GetWishSize()
	{
		return Wish.Size();
	}
	uint32_t GetMyBidSize()
	{
		return MyBid.Size();
	}

	void InsertAuctionItemInfoCache (TAuctionItemInfo *pNew, bool bSkipQuery = false)
	{
		Auction.InsertItemInfo (pNew, bSkipQuery);
	}
	CAuctionItemInfoCache* GetAuctionItemInfoCache (uint32_t item_id)
	{
		return Auction.GetItemInfoCache(item_id);
	}

	void InsertSaleItemInfoCache (TSaleItemInfo *pNew, bool bSkipQuery = false)
	{
		Sale.InsertItemInfo (pNew, bSkipQuery);
	}
	CSaleItemInfoCache* GetSaleItemInfoCache (uint32_t item_id)
	{
		return Sale.GetItemInfoCache(item_id);
	}

	void InsertWishItemInfoCache (TWishItemInfo *pNew, bool bSkipQuery = false)
	{
		Wish.InsertItemInfo (pNew, bSkipQuery);
	}
	CWishItemInfoCache* GetWishItemInfoCache (uint32_t item_id, uint32_t wisher_id)
	{
		return Wish.GetItemInfoCache(WishBoard::Key (item_id, wisher_id));
	}

	void InsertMyBid (uint32_t player_id, uint32_t item_id, uint32_t money)
	{
		MyBid.Insert (player_id, item_id, money);
	}

	AuctionResult EnrollInAuction(CItemCache* item_cache, TAuctionItemInfo &item_info);
	AuctionResult EnrollInSale(CItemCache* item_cache, TSaleItemInfo &item_info);
	AuctionResult EnrollInWish(TWishItemInfo &item_info);
	AuctionResult Bid(uint32_t bidder_id,  const char* bidder_name, uint32_t item_id, uint32_t bid_price);
	AuctionResult Impur(uint32_t purchaser_id, const char* purchaser_name, uint32_t item_id);
	AuctionResult GetAuctionedItem (uint32_t actor_id, uint32_t item_id, TPlayerItem& item);
	AuctionResult BuySoldItem (uint32_t actor_id, uint32_t item_id, TPlayerItem& item);
	AuctionResult CancelAuction (uint32_t actor_id, uint32_t item_id, TPlayerItem& item);
	AuctionResult CancelWish (uint32_t actor_id, uint32_t item_num);
	AuctionResult CancelSale (uint32_t actor_id, uint32_t item_id, TPlayerItem& item);
	AuctionResult DeleteAuctionItem (uint32_t actor_id, uint32_t item_id);
	AuctionResult DeleteSaleItem (uint32_t actor_id, uint32_t item_id);
	AuctionResult ReBid(uint32_t bidder_id,  const char* bidder_name, uint32_t item_id, uint32_t bid_price);
	AuctionResult BidCancel (uint32_t bidder_id, uint32_t item_id);
};

#endif

#endif