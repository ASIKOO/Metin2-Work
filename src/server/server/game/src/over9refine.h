
#ifndef OVER_9_REFINE_MANAGER_H_
#define OVER_9_REFINE_MANAGER_H_

#include <boost/unordered_map.hpp>

class COver9RefineManager : public singleton<COver9RefineManager>
{
	private :
		typedef boost::unordered_map<uint32_t, uint32_t> OVER9ITEM_MAP;
		OVER9ITEM_MAP m_mapItem;

	public :
		void enableOver9Refine(uint32_t dwVnumFrom, uint32_t dwVnumTo);

		int32_t canOver9Refine(uint32_t dwVnum);

		bool Change9ToOver9(LPCHARACTER pChar, LPITEM item);
		bool Over9Refine(LPCHARACTER pChat, LPITEM item);

		uint32_t GetMaterialVnum(uint32_t baseVnum);
};

#endif /* OVER_9_REFINE_MANAGER_H_ */

