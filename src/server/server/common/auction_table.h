#ifndef __INC_AUCTION_TABLES_H__
#define __INC_AUCTION_TABLES_H__

#include "tables.h"

typedef struct _base_auction
{
public:
	uint32_t item_num;
	TItemTable* item_proto;
	int32_t offer_price;
	int32_t price;
	uint32_t offer_id;
	char shown_name[CHARACTER_NAME_MAX_LEN + 1];
	uint8_t empire;
	int32_t expired_time;

	uint32_t get_item_num () { return item_num; }
	uint32_t get_offer_id () { return offer_id; }
	uint8_t get_empire () { return empire; }
	int32_t get_expired_time () { return expired_time; }
	bool is_expired () 
	{
		return (time(NULL) > expired_time);
	}
	int32_t get_price () { return offer_price; }
} TAuctionSimpleItemInfo;

// 각 auction 정보들.
// primary key (item_id)
typedef struct _auction : public _base_auction
{
public:
	uint32_t item_id;
	uint32_t bidder_id;

	_auction (){}
	_auction (uint32_t _item_num, int32_t _offer_price, int32_t _price, uint32_t _offer_id, 
		char* _shown_name, int32_t _expired_time, uint32_t _item_id, uint32_t _bidder_id, uint8_t _empire)
	{
		item_num = _item_num;
		offer_price= _offer_price;
		price = _price;
		offer_id = _offer_id;
		thecore_memcpy(shown_name, _shown_name, strlen(_shown_name) + 1);
		expired_time = _expired_time;
		item_id = _item_id;
		bidder_id = _bidder_id;
		empire = _empire;
	}

	// 이 메소드들은 어떤 변수가 auction에서 어떤 역할을 하는지 까먹을 까봐
	// 만들어놓았다.
	// by rtsummit
	uint32_t get_item_id () { return item_id; }
	uint32_t get_bidder_id () { return bidder_id; }
	int32_t get_bid_price () { return offer_price; }
	void set_bid_price (int32_t new_price) 
	{
		offer_price = new_price;
	}
	int32_t get_impur_price () { return price; }
	
	const char* get_bidder_name () { return shown_name; }
	void set_bidder_name (const char* new_bidder_name)
	{
		thecore_memcpy(shown_name, new_bidder_name, strlen(new_bidder_name) + 1);
	}
} TAuctionItemInfo;

// primary key (item_id)
typedef struct _sale : public _base_auction
{
	_sale (){}

	_sale (uint32_t _item_num, int32_t _offer_price, uint32_t _offer_id,
		char* _shown_name, uint32_t _item_id, uint32_t _wisher_id)
	{
		item_num = _item_num;
		offer_price= _offer_price;
		offer_id = _offer_id;
		thecore_memcpy(shown_name, _shown_name, strlen(_shown_name) + 1);
		item_id = _item_id;
		wisher_id = _wisher_id;
	}

	uint32_t item_id;
	uint32_t wisher_id;

} TSaleItemInfo;

// wish는 실제하는 아이템은 없다.
// primary key (item_num, wisher_id)
typedef struct _wish : public _base_auction
{
	_wish (){}
	
	_wish (uint32_t _item_num, int32_t _offer_price, uint32_t _offer_id, 
		char* _shown_name, int32_t _expired_time, uint8_t _empire)
	{
		item_num = _item_num;
		offer_price= _offer_price;
		offer_id = _offer_id;
		thecore_memcpy(shown_name, _shown_name, strlen(_shown_name) + 1);
		expired_time = _expired_time;
		empire = _empire;
	}
} TWishItemInfo;

enum AuctionType {_AUCTION, _WISH_AUCTION, _MY_AUCTION, _MY_WISH_AUCTION, _AUCTION_MAX};

enum AuctionCmd {OPEN_AUCTION, OPEN_WISH_AUCTION, OPEN_MY_AUCTION, OPEN_MY_WISH_AUCTION, 
	AUCTION_BID, AUCTION_IMME_PUR, AUCTION_ENR_AUC, AUCTION_ENR_WISH, AUCTION_ENR_SALE, 
	AUCTION_GET_AUC, AUCTION_BUY_SOLD, 
	AUCTION_CANCEL_AUC, AUCTION_CANCEL_WISH, AUCTION_CANCEL_SALE,
	AUCTION_DELETE_AUCTION_ITEM, AUCTION_DELETE_SALE_ITEM,
	AUCTION_CHANGING_MONEY,
	AUCTION_REBID, AUCTION_BID_CANCEL,
};

// 반드시 FAIL 앞에, 실패 류 들이 와야한다.
// 왜냐, <= AUCTION_FAIL 이런 CHECK을 할 거거든
// 반대로 SUCCESS 뒤에, 성공 류 들이 와야한다. 근데 성공류가 있긴 하려나...

enum AuctionResult { AUCTION_EXPIRED, AUCTION_NOT_EXPIRED, AUCTION_NOT_ENOUGH_MONEY,
	AUCTION_SOLD, AUCTION_CANCEL, AUCTION_ALREADY_IN, AUCTION_NOT_IN, AUCTION_FAIL, AUCTION_SUCCESS };

enum AuctionSort { AUCTION_NO_ORDER, 
		AUCTION_ITEM_NAME_AC, AUCTION_ITEM_NAME_DC,
		AUCTION_CATEGORY_AC, AUCTION_CATEGORY_DC, 
		AUCTION_TIME_AC, AUCTION_TIME_DC, 
		AUCTION_CHAR_NAME_AC, AUCTION_CHAR_NAME_DC,
		AUCTION_PRICE_AC, AUCTION_PRICE_DC,
};

typedef struct command_get_auction_list
{
	AuctionCmd	cmd;
	uint32_t		start_idx;
	uint8_t		size;
} TPacketGDGetAuctionList;

typedef struct command_auction
{
	void enroll_product (uint32_t _item_id, uint8_t _empire, int32_t _bidPrice, int32_t _impurPrice)
	{
		cmd = AUCTION_ENR_AUC;
		item = _item_id;
		empire = _empire;
		price1 = _bidPrice;
		price2 = _impurPrice;
	}
	void enroll_sale (uint32_t _item_id, uint32_t _wisher_id, int32_t _salePrice)
	{
		cmd = AUCTION_ENR_SALE;
		item = _item_id;
		price1 = _salePrice;
		player_id = _wisher_id;
	}
	void enroll_wish (uint32_t _item_num, uint8_t _empire, int32_t _wishPrice)
	{
		cmd = AUCTION_ENR_WISH;
		item = _item_num;
		empire = _empire;
		price1 = _wishPrice;
	}
	void bid (uint32_t _item_id, int32_t _bidPrice)
	{
		cmd = AUCTION_BID;
		item = _item_id;
		price1 = _bidPrice;
	}
	void impur (uint32_t _item_id)
	{
		cmd = AUCTION_IMME_PUR;
		item = _item_id;
	}
	void get_auctioned_item (uint32_t _item_id)
	{
		cmd = AUCTION_GET_AUC;
		item = _item_id;
	}
	void buy_sold_item (uint32_t _item_id)
	{
		cmd = AUCTION_BUY_SOLD;
		item = _item_id;
	}
	void cancel_auction (uint32_t _item_id)
	{
		cmd = AUCTION_CANCEL_AUC;
		item = _item_id;
	}
	void cancel_wish (uint32_t _item_num)
	{
		cmd = AUCTION_CANCEL_WISH;
		item = _item_num;
	}
	void cancel_sale (uint32_t _item_id)
	{
		cmd = AUCTION_CANCEL_SALE;
		item = _item_id;
	}

	void delete_auction_item (uint32_t _item_id)
	{
		cmd = AUCTION_DELETE_AUCTION_ITEM;
		item = _item_id;
	}

	void delete_sale_item (uint32_t _item_id)
	{
		cmd = AUCTION_DELETE_SALE_ITEM;
		item = _item_id;
	}

	void changing_money (int32_t _money)
	{
		cmd = AUCTION_CHANGING_MONEY;
		price1 = _money;
	}
	// bid랑 cmd만 다르다.
	void rebid (uint32_t _item_id, int32_t _bidPrice)
	{
		cmd = AUCTION_REBID;
		item = _item_id;
		price1 = _bidPrice;
	}
	void bid_cancel (uint32_t _item_id)
	{
		cmd = AUCTION_BID_CANCEL;
		item = _item_id;
	}
	uint32_t get_item () { return item; }

protected:
	AuctionCmd	cmd;
	uint32_t		player_id;
	uint32_t		item;
	uint8_t		empire;
	int32_t			price1;
	int32_t			price2;

public:
	AuctionCmd get_cmd() { return cmd; }
	uint8_t get_empire () { return empire; }
} TPacketGDCommnadAuction;

typedef struct result_auction
{
	AuctionCmd cmd;
	uint8_t result;
	uint32_t target;
} TPacketDGResultAuction;

// wrapper struct
typedef struct auction_enroll_product : public command_auction
{
	uint32_t get_item_id() { return item; }
	int32_t get_bid_price() { return price1; }
	int32_t get_impur_price() { return price2; }
} AuctionEnrollProductInfo;

typedef struct auction_enroll_sale : public command_auction
{
	uint32_t get_item_id() { return item; }
	uint32_t get_wisher_id() { return player_id; }
	int32_t get_sale_price() { return price1; }
} AuctionEnrollSaleInfo;

typedef struct auction_enroll_wish : public command_auction
{
	uint32_t get_item_num() { return item; }
	int32_t get_wish_price() { return price1; }
} AuctionEnrollWishInfo;

typedef struct auction_bid : public command_auction
{
	uint32_t get_item_id() { return item; }
	int32_t get_bid_price() { return price1; }
} AuctionBidInfo;

typedef struct auction_impur : public command_auction
{
	uint32_t get_item_id() { return item; }
} AuctionImpurInfo;


//typedef struct get_auction_list
//
//bid
//{
//	item_id;
//	bidder_id;
//	price;
//}
//impur
//{
//	item_id;
//	purchaser_id;
//}
//enroll_wish
//{
//	item_num;
//	wisher_id;
//	wish_price;
//}
//enroll_sale
//{
//	item_id;
//	seller_id;
//	sale_price;
//}
//
//return_packet
//{
//	isSuccess;
//}
//
//
//get_auction_simple_item_info_list
//{
//	auction_type;
//	start_idx;
//	size;
//	conditions; 정렬은 승철님께 조언을 구해보자.ㅇㅇ
//}
//
//get_auction_detail_item_info
//{
//	item_id;
//}


#endif

