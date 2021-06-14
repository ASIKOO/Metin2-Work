// vim:ts=4 sw=4
#ifndef __INC_METIN_II_ITEM_ID_RANGE_MANAGER_H__
#define __INC_METIN_II_ITEM_ID_RANGE_MANAGER_H__

class CItemIDRangeManager : public singleton<CItemIDRangeManager>
{
	private :
		const static uint32_t cs_dwMaxItemID = 4290000000UL;
		const static uint32_t cs_dwMinimumRange = 10000000UL;
		const static uint32_t cs_dwMinimumRemainCount = 10000UL;

		std::list<TItemIDRangeTable> m_listData;

	public :
		CItemIDRangeManager();

		void Build();
		bool BuildRange(uint32_t dwMin, uint32_t dwMax, TItemIDRangeTable& range);
		void UpdateRange(uint32_t dwMin, uint32_t dwMax);

		TItemIDRangeTable GetRange();
};

#endif
