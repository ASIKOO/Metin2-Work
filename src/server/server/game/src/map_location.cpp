
#include "stdafx.h"

#include "map_location.h"

#include "sectree_manager.h"

CMapLocation g_mapLocations;

bool CMapLocation::Get(int32_t x, int32_t y, int32_t & lIndex, int32_t & lAddr, uint16_t & wPort)
{
	lIndex = SECTREE_MANAGER::instance().GetMapIndex(x, y);

	return Get(lIndex, lAddr, wPort);
}

bool CMapLocation::Get(int32_t iIndex, int32_t & lAddr, uint16_t & wPort)
{
	if (iIndex == 0)
	{
		sys_log(0, "CMapLocation::Get - Error MapIndex[%d]", iIndex);
		return false;
	}

	std::map<int32_t, TLocation>::iterator it = m_map_address.find(iIndex);

	if (m_map_address.end() == it)
	{
		sys_log(0, "CMapLocation::Get - Error MapIndex[%d]", iIndex);
		std::map<int32_t, TLocation>::iterator i;
		for ( i	= m_map_address.begin(); i != m_map_address.end(); ++i)
		{
			sys_log(0, "Map(%d): Server(%x:%d)", i->first, i->second.addr, i->second.port);
		}
		return false;
	}

	lAddr = it->second.addr;
	wPort = it->second.port;
	return true;
}

void CMapLocation::Insert(int32_t lIndex, const char * c_pszHost, uint16_t wPort)
{
	TLocation loc;

	loc.addr = inet_addr(c_pszHost);
	loc.port = wPort;

	m_map_address.insert(std::make_pair(lIndex, loc));
	sys_log(0, "MapLocation::Insert : %d %s %d", lIndex, c_pszHost, wPort);
}

