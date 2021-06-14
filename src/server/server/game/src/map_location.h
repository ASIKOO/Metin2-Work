
#include "../../common/stl.h"

class CMapLocation : public singleton<CMapLocation>
{
	public:
		typedef struct SLocation
		{
			int32_t        addr;
			uint16_t        port;
		} TLocation;    

		bool    Get(int32_t x, int32_t y, int32_t & lMapIndex, int32_t & lAddr, uint16_t & wPort);
		bool	Get(int32_t iIndex, int32_t & lAddr, uint16_t & wPort);
		void    Insert(int32_t lIndex, const char * c_pszHost, uint16_t wPort);

	protected:
		std::map<int32_t, TLocation> m_map_address;
};      

