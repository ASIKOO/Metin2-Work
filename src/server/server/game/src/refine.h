#ifndef __INC_REFINE_H
#define __INC_REFINE_H

#include "constants.h"

enum
{
	BLACKSMITH_MOB = 20016, // Ȯ�� ����
	ALCHEMIST_MOB = 20001, // 100% ���� ���� 

	BLACKSMITH_WEAPON_MOB = 20044,
	BLACKSMITH_ARMOR_MOB = 20045,
	BLACKSMITH_ACCESSORY_MOB = 20046,

	DEVILTOWER_BLACKSMITH_WEAPON_MOB = 20074,
	DEVILTOWER_BLACKSMITH_ARMOR_MOB = 20075,
	DEVILTOWER_BLACKSMITH_ACCESSORY_MOB = 20076,

	BLACKSMITH2_MOB	= 20091,
};

class CRefineManager : public singleton<CRefineManager>
{
	typedef std::map<uint32_t, TRefineTable> TRefineRecipeMap;
	public:
	CRefineManager();
	virtual ~CRefineManager();

	bool	Initialize(TRefineTable * table, int32_t size);
	const TRefineTable* GetRefineRecipe(uint32_t id);

	private:
	TRefineRecipeMap    m_map_RefineRecipe;

};
#endif
