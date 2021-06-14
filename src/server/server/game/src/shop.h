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
			uint32_t	vnum;		// ������ ��ȣ
			int32_t	price;		// ����
			uint8_t	count;		// ������ ����

			LPITEM	pkItem;
			int32_t		itemid;		// ������ �������̵�

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

		// �Խ�Ʈ �߰�/����
		virtual bool	AddGuest(LPCHARACTER ch,uint32_t owner_vid, bool bOtherEmpire);
		void	RemoveGuest(LPCHARACTER ch);

		// ���� ����
		virtual int32_t	Buy(LPCHARACTER ch, uint8_t pos);

		// �Խ�Ʈ���� ��Ŷ�� ����
		void	BroadcastUpdateItem(uint8_t pos);

		// �Ǹ����� �������� ������ �˷��ش�.
		int32_t		GetNumberByVnum(uint32_t dwVnum);

		// �������� ������ ��ϵǾ� �ִ��� �˷��ش�.
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
		std::vector<SHOP_ITEM>		m_itemVector;	// �� �������� ����ϴ� ���ǵ�

		LPCHARACTER			m_pkPC;
};

#endif 
