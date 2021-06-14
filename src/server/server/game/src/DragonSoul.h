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
	// fixme : titempos��
	uint16_t	GetBasePosition(const LPITEM pItem) const;
	bool	IsValidCellForThisItem(const LPITEM pItem, const TItemPos& Cell) const;
	int32_t		GetDuration(const LPITEM pItem) const;
	
	// ��ȥ���� �޾Ƽ� Ư�� ����� �����ϴ� �Լ�
	bool	ExtractDragonHeart(LPCHARACTER ch, LPITEM pItem, LPITEM pExtractor = NULL);

	// Ư�� ��ȥ��(pItem)�� ���â���� ������ ���� ���� ���θ� �����ϰ�, 
	// ���н� �λ깰�� �ִ� �Լ�.(�λ깰�� dragon_soul_table.txt�� ����)
	// DestCell�� invalid�� ���� ������ ���� ��, ��ȥ���� �� ������ �ڵ� �߰�.
	// ���� ��, ��ȥ��(pItem)�� delete��.
	// ����������� �ִٸ� ���� ���� Ȯ���� pExtractor->GetValue(0)%��ŭ ������.
	// �λ깰�� ������ �ڵ� �߰�.
	bool	PullOut(LPCHARACTER ch, TItemPos DestCell, IN OUT LPITEM& pItem, LPITEM pExtractor = NULL);

	// ��ȥ�� ���׷��̵� �Լ�
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

	// ĳ������ ��ȥ�� ���� ���캸��, Ȱ��ȭ �� ��ȥ���� ���ٸ�, ĳ������ ��ȥ�� Ȱ�� ���¸� off ��Ű�� �Լ�.
	void	RefreshDragonSoulState(LPCHARACTER ch);

	uint32_t	MakeDragonSoulVnum(uint8_t bType, uint8_t grade, uint8_t step, uint8_t refine);
	bool	PutAttributes(LPITEM pDS);
	bool	RefreshItemAttributes(LPITEM pItem);

	DragonSoulTable*	m_pTable;
};

#endif
