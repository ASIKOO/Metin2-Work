#ifndef __INC_METIN_II_GAME_SHOP_MANAGER_H__
#define __INC_METIN_II_GAME_SHOP_MANAGER_H__

class CShop;
typedef class CShop * LPSHOP;

class CShopManager : public singleton<CShopManager>
{
public:
	typedef std::map<uint32_t, CShop *> TShopMap;

public:
	CShopManager();
	virtual ~CShopManager();

	bool	Initialize(TShopTable * table, int32_t size);
	void	Destroy();

	LPSHOP	Get(uint32_t dwVnum);
	LPSHOP	GetByNPCVnum(uint32_t dwVnum);

	bool	StartShopping(LPCHARACTER pkChr, LPCHARACTER pkShopKeeper, int32_t iShopVnum = 0);
	void	StopShopping(LPCHARACTER ch);

	void	Buy(LPCHARACTER ch, uint8_t pos);
	void	Sell(LPCHARACTER ch, uint8_t bCell, uint8_t bCount=0);

	LPSHOP	CreatePCShop(LPCHARACTER ch, TShopItemTable * pTable, uint8_t bItemCount);
	LPSHOP	FindPCShop(uint32_t dwVID);
	void	DestroyPCShop(LPCHARACTER ch);

private:
	TShopMap	m_map_pkShop;
	TShopMap	m_map_pkShopByNPCVnum;
	TShopMap	m_map_pkShopByPC;

	bool	ReadShopTableEx(const char* stFileName);
};

#endif