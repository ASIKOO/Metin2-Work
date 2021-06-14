#ifndef __INC_METIN_II_GAME_DRAGON_SOUL_H__
#define __INC_METIN_II_GAME_DRAGON_SOUL_H__

#include "../../common/length.h"

class CHARACTER;
class CItem;

class DragonSoulTable;

class DSManager : public singleton<DSManager>
{
public:
	DSManager();
	~DSManager();
	bool	ReadDragonSoulTableFile(const char * c_pszFileName);

	void	GetDragonSoulInfo(uint32_t dwVnum, OUT uint8_t& bType, OUT uint8_t& bGrade, OUT uint8_t& bStep, OUT uint8_t& bRefine) const;
	// fixme : titempos로
	uint16_t	GetBasePosition(const LPITEM pItem) const;
	bool	IsValidCellForThisItem(const LPITEM pItem, const TItemPos& Cell) const;
	int32_t		GetDuration(const LPITEM pItem) const;
	
	// 용혼석을 받아서 특정 용심을 추출하는 함수
	bool	ExtractDragonHeart(LPCHARACTER ch, LPITEM pItem, LPITEM pExtractor = NULL);

	// 특정 용혼석(pItem)을 장비창에서 제거할 때에 성공 여부를 결정하고, 
	// 실패시 부산물을 주는 함수.(부산물은 dragon_soul_table.txt에 정의)
	// DestCell에 invalid한 값을 넣으면 성공 시, 용혼석을 빈 공간에 자동 추가.
	// 실패 시, 용혼석(pItem)은 delete됨.
	// 추출아이템이 있다면 추출 성공 확률이 pExtractor->GetValue(0)%만큼 증가함.
	// 부산물은 언제나 자동 추가.
	bool	PullOut(LPCHARACTER ch, TItemPos DestCell, IN OUT LPITEM& pItem, LPITEM pExtractor = NULL);

	// 용혼석 업그레이드 함수
	bool	DoRefineGrade(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	bool	DoRefineStep(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	bool	DoRefineStrength(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	
	bool	DragonSoulItemInitialize(LPITEM pItem);

	bool	IsTimeLeftDragonSoul(LPITEM pItem) const;
	int32_t		LeftTime(LPITEM pItem) const;
	bool	ActivateDragonSoul(LPITEM pItem);
	bool	DeactivateDragonSoul(LPITEM pItem, bool bSkipRefreshOwnerActiveState = false);
	bool	IsActiveDragonSoul(LPITEM pItem) const;
private:
	void	SendRefineResultPacket(LPCHARACTER ch, uint8_t bSubHeader, const TItemPos& pos);

	// 캐릭터의 용혼석 덱을 살펴보고, 활성화 된 용혼석이 없다면, 캐릭터의 용혼석 활성 상태를 off 시키는 함수.
	void	RefreshDragonSoulState(LPCHARACTER ch);

	uint32_t	MakeDragonSoulVnum(uint8_t bType, uint8_t grade, uint8_t step, uint8_t refine);
	bool	PutAttributes(LPITEM pDS);
	bool	RefreshItemAttributes(LPITEM pItem);

	DragonSoulTable*	m_pTable;
};

#endif
