#ifndef __INC_METIN_II_GAME_SHOP_SECONDARY_COIN_H__
#define __INC_METIN_II_GAME_SHOP_SECONDARY_COIN_H__
#include "typedef.h"
#include "shop.h"

struct SShopTable;
typedef struct SShopTableEx : SShopTable
{
	std::string name;
	EShopCoinType coinType;
} TShopTableEx;

class CGroupNode;

// Ȯ�� shop.
// ������ ȭ��� �� �� �ְ�, �������� ���� �ǿ� ���� ��ġ�� �� �ִ�.
// ��, pc ���� �������� ����.
// Ŭ��� ����� ���� ���� pos 45 ������ ����.
// ���� ���� m_itemVector�� ������� �ʴ´�.
class CShopEx: public CShop
{
public:
	bool			Create(uint32_t dwVnum, uint32_t dwNPCVnum);
	bool			AddShopTable(TShopTableEx& shopTable);

	virtual bool	AddGuest(LPCHARACTER ch,uint32_t owner_vid, bool bOtherEmpire);
	virtual void	SetPCShop(LPCHARACTER ch) { return; }
	virtual bool	IsPCShop() { return false; }
	virtual int32_t		Buy(LPCHARACTER ch, uint8_t pos);
	virtual bool	IsSellingItem(uint32_t itemID) { return false; }
	
	uint32_t			GetTabCount() { return m_vec_shopTabs.size(); }
private:
	std::vector <TShopTableEx> m_vec_shopTabs;
};
typedef CShopEx* LPSHOPEX;

#endif
