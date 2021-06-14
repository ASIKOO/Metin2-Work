#ifndef __INC_FISHING_H
#define __INC_FISHING_H

#include "item.h"

namespace fishing
{
	enum
	{
		CAMPFIRE_MOB = 12000,
		FISHER_MOB = 9009,
		FISH_MIND_PILL_VNUM = 27610,
	};

	EVENTINFO(fishing_event_info)
	{
		uint32_t	pid;
		int32_t		step;
		uint32_t	hang_time;
		int32_t		fish_id;

		fishing_event_info()
		: pid(0)
		, step(0)
		, hang_time(0)
		, fish_id(0)
		{
		}
	};

	extern void Initialize();
	extern LPEVENT CreateFishingEvent(LPCHARACTER ch);
	extern void Take(fishing_event_info* info, LPCHARACTER ch);
	extern void Simulation(int32_t level, int32_t count, int32_t map_grade, LPCHARACTER ch);
	extern void UseFish(LPCHARACTER ch, LPITEM item);
	extern void Grill(LPCHARACTER ch, LPITEM item);

	extern bool RefinableRod(LPITEM rod);
	extern int32_t RealRefineRod(LPCHARACTER ch, LPITEM rod);
}
#endif
