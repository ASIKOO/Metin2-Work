#ifndef __INC_XMAS_EVENT_H
#define __INC_XMAS_EVENT_H

namespace xmas
{
	enum
	{
		MOB_SANTA_VNUM = 20031,	//산타 
	//	MOB_SANTA_VNUM = 20095,	//노해
		MOB_XMAS_TREE_VNUM = 20032,
		MOB_XMAS_FIRWORK_SELLER_VNUM = 9004,
	};

	void ProcessEventFlag(const std::string& name, int32_t prev_value, int32_t value);
	void SpawnSanta(int32_t lMapIndex, int32_t iTimeGapSec);
	void SpawnEventHelper(bool spawn);
}
#endif
