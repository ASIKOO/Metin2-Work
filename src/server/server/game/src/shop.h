#ifndef __INC_METIN_II_GAME_SHOP_H__
#define __INC_METIN_II_GAME_SHOP_H__

enum
{
	SHOP_MAX_DISTANCE = 1000
};

class CGrid;

/* ---------------------------------------------------------------------------------- */
class CShop
{
	public:
		typedef struct shop_item
		{
			uint32_t	vnum;		// 아이템 번호
			int32_t	price;		// 가격
			uint8_t	count;		// 아이템 개수

			LPITEM	pkItem;
			int32_t		itemid;		// 아이템 고유아이디

			shop_item()
			{
				vnum = 0;
				price = 0;
				count = 0;
				itemid = 0;
				pkItem = NULL;
			}
		} SHOP_ITEM;

		CShop();
		~CShop();

		bool	Create(uint32_t dwVnum, uint32_t dwNPCVnum, TShopItemTable * pItemTable);
		void	SetShopItems(TShopItemTable * pItemTable, uint8_t bItemCount);

		virtual void	SetPCShop(LPCHARACTER ch);
		virtual bool	IsPCShop()	{ return m_pkPC ? true : false; }

		// 게스트 추가/삭제
		virtual bool	AddGuest(LPCHARACTER ch,uint32_t owner_vid, bool bOtherEmpire);
		void	RemoveGuest(LPCHARACTER ch);

		// 물건 구입
		virtual int32_t	Buy(LPCHARACTER ch, uint8_t pos);

		// 게스트에게 패킷을 보냄
		void	BroadcastUpdateItem(uint8_t pos);

		// 판매중인 아이템의 갯수를 알려준다.
		int32_t		GetNumberByVnum(uint32_t dwVnum);

		// 아이템이 상점에 등록되어 있는지 알려준다.
		virtual bool	IsSellingItem(uint32_t itemID);

		uint32_t	GetVnum() { return m_dwVnum; }
		uint32_t	GetNPCVnum() { return m_dwNPCVnum; }

	protected:
		void	Broadcast(const void * data, int32_t bytes);

	protected:
		uint32_t				m_dwVnum;
		uint32_t				m_dwNPCVnum;

		CGrid *				m_pGrid;

		typedef std::unordered_map<LPCHARACTER, bool> GuestMapType;
		GuestMapType m_map_guest;
		std::vector<SHOP_ITEM>		m_itemVector;	// 이 상점에서 취급하는 물건들

		LPCHARACTER			m_pkPC;
};

#endif 
