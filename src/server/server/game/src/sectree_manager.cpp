#include "stdafx.h"
#include <sstream>
#include "../../libgame/include/targa.h"
#include "../../libgame/include/attribute.h"
#include "config.h"
#include "utils.h"
#include "sectree_manager.h"
#include "regen.h"
#include "lzo_manager.h"
#include "desc.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "item.h"
#include "item_manager.h"
#include "buffer_manager.h"
#include "packet.h"
#include "start_position.h"
#include "dev_log.h"

uint16_t SECTREE_MANAGER::current_sectree_version = MAKEWORD(0, 3);

SECTREE_MAP::SECTREE_MAP()
{
	memset( &m_setting, 0, sizeof(m_setting) );
}

SECTREE_MAP::~SECTREE_MAP()
{
	MapType::iterator it = map_.begin();

	while (it != map_.end()) {
		LPSECTREE sectree = (it++)->second;
		M2_DELETE(sectree);
	}

	map_.clear();
}

SECTREE_MAP::SECTREE_MAP(SECTREE_MAP & r)
{
	m_setting = r.m_setting;

	MapType::iterator it = r.map_.begin();

	while (it != r.map_.end())
	{
		LPSECTREE tree = M2_NEW SECTREE;

		tree->m_id.coord = it->second->m_id.coord;
		tree->CloneAttribute(it->second);

		map_.insert(MapType::value_type(it->first, tree));
		++it;
	}

	Build();
}

LPSECTREE SECTREE_MAP::Find(uint32_t dwPackage)
{
	MapType::iterator it = map_.find(dwPackage);

	if (it == map_.end())
		return NULL;

	return it->second;
}

LPSECTREE SECTREE_MAP::Find(uint32_t x, uint32_t y)
{
	SECTREEID id;
	id.coord.x = x / SECTREE_SIZE;
	id.coord.y = y / SECTREE_SIZE;
	return Find(id.package);
}

void SECTREE_MAP::Build()
{
    // 클라이언트에게 반경 150m 캐릭터의 정보를 주기위해
    // 3x3칸 -> 5x5 칸으로 주변sectree 확대(한국)
    if (LC_IsYMIR() || LC_IsKorea())
    {
#define NEIGHBOR_LENGTH		5
#define NUM_OF_NEIGHBORS	(NEIGHBOR_LENGTH * NEIGHBOR_LENGTH - 1)
	int32_t	width = NEIGHBOR_LENGTH / 2;
	struct neighbor_coord_s
	{
		int32_t x;
		int32_t y;
	} neighbor_coord[NUM_OF_NEIGHBORS];

	{
	    int32_t i = 0;
	    for (int32_t x = -width; x <= width; ++x)
	    {
		for (int32_t y = -width; y <= width; ++y)
		{
		    if (x == 0 && y == 0)
			continue;

		    neighbor_coord[i].x = x * SECTREE_SIZE;
		    neighbor_coord[i].y = y * SECTREE_SIZE;
		    ++i;
		}
	    }
	}

	//
	// 모든 sectree에 대해 주위 sectree들 리스트를 만든다.
	//
	MapType::iterator it = map_.begin();

	while (it != map_.end())
	{
		LPSECTREE tree = it->second;

		tree->m_neighbor_list.push_back(tree); // 자신을 넣는다.

		sys_log(3, "%dx%d", tree->m_id.coord.x, tree->m_id.coord.y);

		int32_t x = tree->m_id.coord.x * SECTREE_SIZE;
		int32_t y = tree->m_id.coord.y * SECTREE_SIZE;

		for (uint32_t i = 0; i < NUM_OF_NEIGHBORS; ++i)
		{
			LPSECTREE tree2 = Find(x + neighbor_coord[i].x, y + neighbor_coord[i].y);

			if (tree2)
			{
				sys_log(3, "   %d %dx%d", i, tree2->m_id.coord.x, tree2->m_id.coord.y);
				tree->m_neighbor_list.push_back(tree2);
			}
		}

		++it;
	}
    }
    else
    {
	struct neighbor_coord_s
	{
		int32_t x;
		int32_t y;
	} neighbor_coord[8] = {
		{ -SECTREE_SIZE,	0		},
		{  SECTREE_SIZE,	0		},
		{ 0	       ,	-SECTREE_SIZE	},
		{ 0	       ,	 SECTREE_SIZE	},
		{ -SECTREE_SIZE,	 SECTREE_SIZE	},
		{  SECTREE_SIZE,	-SECTREE_SIZE	},
		{ -SECTREE_SIZE,	-SECTREE_SIZE	},
		{  SECTREE_SIZE,	 SECTREE_SIZE	},
	};

	//
	// 모든 sectree에 대해 주위 sectree들 리스트를 만든다.
	//
	MapType::iterator it = map_.begin();

	while (it != map_.end())
	{
		LPSECTREE tree = it->second;

		tree->m_neighbor_list.push_back(tree); // 자신을 넣는다.

		sys_log(3, "%dx%d", tree->m_id.coord.x, tree->m_id.coord.y);

		int32_t x = tree->m_id.coord.x * SECTREE_SIZE;
		int32_t y = tree->m_id.coord.y * SECTREE_SIZE;

		for (uint32_t i = 0; i < 8; ++i)
		{
			LPSECTREE tree2 = Find(x + neighbor_coord[i].x, y + neighbor_coord[i].y);

			if (tree2)
			{
				sys_log(3, "   %d %dx%d", i, tree2->m_id.coord.x, tree2->m_id.coord.y);
				tree->m_neighbor_list.push_back(tree2);
			}
		}

		++it;
	}
    }
}

SECTREE_MANAGER::SECTREE_MANAGER()
{
}

SECTREE_MANAGER::~SECTREE_MANAGER()
{
	/*
	   std::map<uint32_t, LPSECTREE_MAP>::iterator it = m_map_pkSectree.begin();

	   while (it != m_map_pkSectree.end())
	   {
	   M2_DELETE(it->second);
	   ++it;
	   }
	 */
}

LPSECTREE_MAP SECTREE_MANAGER::GetMap(int32_t lMapIndex)
{
	std::map<uint32_t, LPSECTREE_MAP>::iterator it = m_map_pkSectree.find(lMapIndex);

	if (it == m_map_pkSectree.end())
		return NULL;

	return it->second;
}

LPSECTREE SECTREE_MANAGER::Get(uint32_t dwIndex, uint32_t package)
{
	LPSECTREE_MAP pkSectreeMap = GetMap(dwIndex);

	if (!pkSectreeMap)
		return NULL;

	return pkSectreeMap->Find(package);
}

LPSECTREE SECTREE_MANAGER::Get(uint32_t dwIndex, uint32_t x, uint32_t y)
{
	SECTREEID id;
	id.coord.x = x / SECTREE_SIZE;
	id.coord.y = y / SECTREE_SIZE;
	return Get(dwIndex, id.package);
}

// -----------------------------------------------------------------------------
// Setting.txt 로 부터 SECTREE 만들기
// -----------------------------------------------------------------------------
int32_t SECTREE_MANAGER::LoadSettingFile(int32_t lMapIndex, const char * c_pszSettingFileName, TMapSetting & r_setting)
{
	memset(&r_setting, 0, sizeof(TMapSetting));

	FILE * fp = fopen(c_pszSettingFileName, "r");

	if (!fp)
	{
		sys_err("cannot open file: %s", c_pszSettingFileName);
		return 0;
	}

	char buf[256], cmd[256];
	int32_t iWidth = 0, iHeight = 0;

	while (fgets(buf, 256, fp))
	{
		sscanf(buf, " %s ", cmd);

		if (!strcasecmp(cmd, "MapSize"))
		{
			sscanf(buf, " %s %d %d ", cmd, &iWidth, &iHeight);
		}
		else if (!strcasecmp(cmd, "BasePosition"))
		{
			sscanf(buf, " %s %d %d", cmd, &r_setting.iBaseX, &r_setting.iBaseY);
		}
		else if (!strcasecmp(cmd, "CellScale"))
		{
			sscanf(buf, " %s %d ", cmd, &r_setting.iCellScale);
		}
	}

	fclose(fp);

	if ((iWidth == 0 && iHeight == 0) || r_setting.iCellScale == 0)
	{
		sys_err("Invalid Settings file: %s", c_pszSettingFileName);
		return 0;
	}

	r_setting.iIndex = lMapIndex;
	r_setting.iWidth = (r_setting.iCellScale * 128 * iWidth);
	r_setting.iHeight = (r_setting.iCellScale * 128 * iHeight);
	return 1;
}

LPSECTREE_MAP SECTREE_MANAGER::BuildSectreeFromSetting(TMapSetting & r_setting)
{
	LPSECTREE_MAP pkMapSectree = M2_NEW SECTREE_MAP;

	pkMapSectree->m_setting = r_setting;

	int32_t x, y;
	LPSECTREE tree;

	for (x = r_setting.iBaseX; x < r_setting.iBaseX + r_setting.iWidth; x += SECTREE_SIZE)
	{
		for (y = r_setting.iBaseY; y < r_setting.iBaseY + r_setting.iHeight; y += SECTREE_SIZE)
		{
			tree = M2_NEW SECTREE;
			tree->m_id.coord.x = x / SECTREE_SIZE;
			tree->m_id.coord.y = y / SECTREE_SIZE;
			pkMapSectree->Add(tree->m_id.package, tree);
			sys_log(3, "new sectree %d x %d", tree->m_id.coord.x, tree->m_id.coord.y);
		}
	}

	if ((r_setting.iBaseX + r_setting.iWidth) % SECTREE_SIZE)
	{
		tree = M2_NEW SECTREE;
		tree->m_id.coord.x = ((r_setting.iBaseX + r_setting.iWidth) / SECTREE_SIZE) + 1;
		tree->m_id.coord.y = ((r_setting.iBaseY + r_setting.iHeight) / SECTREE_SIZE);
		pkMapSectree->Add(tree->m_id.package, tree);
	}

	if ((r_setting.iBaseY + r_setting.iHeight) % SECTREE_SIZE)
	{
		tree = M2_NEW SECTREE;
		tree->m_id.coord.x = ((r_setting.iBaseX + r_setting.iWidth) / SECTREE_SIZE);
		tree->m_id.coord.y = ((r_setting.iBaseX + r_setting.iHeight) / SECTREE_SIZE) + 1;
		pkMapSectree->Add(tree->m_id.package, tree);
	}

	return pkMapSectree;
}

void SECTREE_MANAGER::LoadDungeon(int32_t iIndex, const char * c_pszFileName)
{
	FILE* fp = fopen(c_pszFileName, "r");

	if (!fp)
		return;

	int32_t count = 0; // for debug

	while (!feof(fp))
	{
		char buf[1024];

		if (NULL == fgets(buf, 1024, fp))
			break;

		if (buf[0] == '#' || buf[0] == '/' && buf[1] == '/')
			continue;

		std::istringstream ins(buf, std::ios_base::in);
		std::string position_name;
		int32_t x, y, sx, sy, dir;

		ins >> position_name >> x >> y >> sx >> sy >> dir;

		if (ins.fail())
			continue;

		x -= sx;
		y -= sy;
		sx *= 2;
		sy *= 2;
		sx += x;
		sy += y;

		m_map_pkArea[iIndex].insert(std::make_pair(position_name, TAreaInfo(x, y, sx, sy, dir)));

		count++;
	}

	fclose(fp);

	sys_log(0, "Dungeon Position Load [%3d]%s count %d", iIndex, c_pszFileName, count);
}

// Fix me
// 현재 Town.txt에서 x, y를 그냥 받고, 그걸 이 코드 내에서 base 좌표를 더해주기 때문에
// 다른 맵에 있는 타운으로 절대 이동할 수 없게 되어있다.
// 앞에 map이라거나, 기타 다른 식별자가 있으면,
// 다른 맵의 타운으로도 이동할 수 있게 하자.
// by rtsummit
bool SECTREE_MANAGER::LoadMapRegion(const char * c_pszFileName, TMapSetting & r_setting, const char * c_pszMapName)
{
	FILE * fp = fopen(c_pszFileName, "r");

	if ( test_server )
		sys_log( 0, "[LoadMapRegion] file(%s)", c_pszFileName );

	if (!fp)
		return false;

	int32_t iX=0, iY=0;
	PIXEL_POSITION pos[3] = { {0,0,0}, {0,0,0}, {0,0,0} };

	fscanf(fp, " %d %d ", &iX, &iY);

	int32_t iEmpirePositionCount = fscanf(fp, " %d %d %d %d %d %d ", 
			&pos[0].x, &pos[0].y,
			&pos[1].x, &pos[1].y,
			&pos[2].x, &pos[2].y);

	fclose(fp);

	if( iEmpirePositionCount == 6 )
	{
		for ( int32_t n = 0; n < 3; ++n )
			sys_log( 0 ,"LoadMapRegion %d %d ", pos[n].x, pos[n].y );
	}
	else
	{
		sys_log( 0, "LoadMapRegion no empire specific start point" );
	}

	TMapRegion region;

	region.index = r_setting.iIndex;
	region.sx = r_setting.iBaseX;
	region.sy = r_setting.iBaseY;
	region.ex = r_setting.iBaseX + r_setting.iWidth;
	region.ey = r_setting.iBaseY + r_setting.iHeight;

	region.strMapName = c_pszMapName;

	region.posSpawn.x = r_setting.iBaseX + (iX * 100);
	region.posSpawn.y = r_setting.iBaseY + (iY * 100); 

	r_setting.posSpawn = region.posSpawn;

	sys_log(0, "LoadMapRegion %d x %d ~ %d y %d ~ %d, town %d %d", 
			region.index,
			region.sx,
			region.ex,
			region.sy,
			region.ey,
			region.posSpawn.x,
			region.posSpawn.y);

	if (iEmpirePositionCount == 6)
	{
		region.bEmpireSpawnDifferent = true;

		for (int32_t i = 0; i < 3; i++)
		{
			region.posEmpire[i].x = r_setting.iBaseX + (pos[i].x * 100);
			region.posEmpire[i].y = r_setting.iBaseY + (pos[i].y * 100);
		}
	}
	else
	{
		region.bEmpireSpawnDifferent = false;
	}

	m_vec_mapRegion.push_back(region);

	sys_log(0,"LoadMapRegion %d End", region.index);
	return true;
}

bool SECTREE_MANAGER::LoadAttribute(LPSECTREE_MAP pkMapSectree, const char * c_pszFileName, TMapSetting & r_setting)
{
	FILE * fp = fopen(c_pszFileName, "rb");

	if (!fp)
	{
		sys_err("SECTREE_MANAGER::LoadAttribute : cannot open %s", c_pszFileName);
		return false;
	}

	int32_t iWidth, iHeight;

	fread(&iWidth, sizeof(int32_t), 1, fp);
	fread(&iHeight, sizeof(int32_t), 1, fp);

	int32_t maxMemSize = LZOManager::instance().GetMaxCompressedSize(sizeof(uint32_t) * (SECTREE_SIZE / CELL_SIZE) * (SECTREE_SIZE / CELL_SIZE));

	uint32_t uiSize;
	uint32_t uiDestSize;

#ifndef _MSC_VER
	uint8_t abComp[maxMemSize];
#else
	uint8_t* abComp = M2_NEW uint8_t[maxMemSize];
#endif
	uint32_t * attr = M2_NEW uint32_t[maxMemSize];

	for (int32_t y = 0; y < iHeight; ++y)
		for (int32_t x = 0; x < iWidth; ++x)
		{
			// UNION 으로 좌표를 합쳐만든 DWORD값을 아이디로 사용한다.
			SECTREEID id;
			id.coord.x = (r_setting.iBaseX / SECTREE_SIZE) + x;
			id.coord.y = (r_setting.iBaseY / SECTREE_SIZE) + y;

			LPSECTREE tree = pkMapSectree->Find(id.package);

			// SERVER_ATTR_LOAD_ERROR
			if (tree == NULL)
			{
				sys_err("FATAL ERROR! LoadAttribute(%s) - cannot find sectree(package=%x, coord=(%u, %u), map_index=%u, map_base=(%u, %u))", 
						c_pszFileName, id.package, id.coord.x, id.coord.y, r_setting.iIndex, r_setting.iBaseX, r_setting.iBaseY);
				sys_err("ERROR_ATTR_POS(%d, %d) attr_size(%d, %d)", x, y, iWidth, iHeight);
				sys_err("CHECK! 'Setting.txt' and 'server_attr' MAP_SIZE!!");

				pkMapSectree->DumpAllToSysErr();
				abort();

				M2_DELETE_ARRAY(attr);
#ifdef _MSC_VER
				M2_DELETE_ARRAY(abComp);
#endif
				return false;
			}
			// END_OF_SERVER_ATTR_LOAD_ERROR

			if (tree->m_id.package != id.package)
			{
				sys_err("returned tree id mismatch! return %u, request %u", 
						tree->m_id.package, id.package);
				fclose(fp);

				M2_DELETE_ARRAY(attr);
#ifdef _MSC_VER
				M2_DELETE_ARRAY(abComp);
#endif
				return false;
			}

			fread(&uiSize, sizeof(int32_t), 1, fp);
			fread(abComp, sizeof(char), uiSize, fp);

			//LZOManager::instance().Decompress(abComp, uiSize, (uint8_t *) tree->GetAttributePointer(), &uiDestSize);
			uiDestSize = sizeof(uint32_t) * maxMemSize;
			LZOManager::instance().Decompress(abComp, uiSize, (uint8_t *) attr, &uiDestSize);

			if (uiDestSize != sizeof(uint32_t) * (SECTREE_SIZE / CELL_SIZE) * (SECTREE_SIZE / CELL_SIZE))
			{
				sys_err("SECTREE_MANAGER::LoadAttribte : %s : %d %d size mismatch! %d",
						c_pszFileName, tree->m_id.coord.x, tree->m_id.coord.y, uiDestSize);
				fclose(fp);

				M2_DELETE_ARRAY(attr);
#ifdef _MSC_VER
				M2_DELETE_ARRAY(abComp);
#endif
				return false;
			}

			tree->BindAttribute(M2_NEW CAttribute(attr, SECTREE_SIZE / CELL_SIZE, SECTREE_SIZE / CELL_SIZE));
		}

	fclose(fp);

	M2_DELETE_ARRAY(attr);
#ifdef _MSC_VER
	M2_DELETE_ARRAY(abComp);
#endif
	return true;
}

bool SECTREE_MANAGER::GetRecallPositionByEmpire(int32_t iMapIndex, uint8_t bEmpire, PIXEL_POSITION & r_pos)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	// 10000을 넘는 맵은 인스턴스 던전에만 한정되어있다.
	if (iMapIndex >= 10000)
	{
		iMapIndex /= 10000;
	}

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (rRegion.index == iMapIndex)
		{
			if (rRegion.bEmpireSpawnDifferent && bEmpire >= 1 && bEmpire <= 3)
				r_pos = rRegion.posEmpire[bEmpire - 1];
			else
				r_pos = rRegion.posSpawn;

			return true;
		}
	}

	return false;
}

bool SECTREE_MANAGER::GetCenterPositionOfMap(int32_t lMapIndex, PIXEL_POSITION & r_pos)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (rRegion.index == lMapIndex)
		{
			r_pos.x = rRegion.sx + (rRegion.ex - rRegion.sx) / 2;
			r_pos.y = rRegion.sy + (rRegion.ey - rRegion.sy) / 2;
			r_pos.z = 0;
			return true;
		}
	}

	return false;
}

bool SECTREE_MANAGER::GetSpawnPositionByMapIndex(int32_t lMapIndex, PIXEL_POSITION& r_pos)
{
	if (lMapIndex> 10000) lMapIndex /= 10000;
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (lMapIndex == rRegion.index)
		{
			r_pos = rRegion.posSpawn;
			return true;
		}
	}

	return false;
}

bool SECTREE_MANAGER::GetSpawnPosition(int32_t x, int32_t y, PIXEL_POSITION & r_pos)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (x >= rRegion.sx && y >= rRegion.sy && x < rRegion.ex && y < rRegion.ey)
		{
			r_pos = rRegion.posSpawn;
			return true;
		}
	}

	return false;
}

bool SECTREE_MANAGER::GetMapBasePositionByMapIndex(int32_t lMapIndex, PIXEL_POSITION & r_pos)
{
	if (lMapIndex> 10000) lMapIndex /= 10000;
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		//if (x >= rRegion.sx && y >= rRegion.sy && x < rRegion.ex && y < rRegion.ey)
		if (lMapIndex == rRegion.index)
		{
			r_pos.x = rRegion.sx;
			r_pos.y = rRegion.sy;
			r_pos.z = 0;
			return true;
		}
	}

	return false;
}

bool SECTREE_MANAGER::GetMapBasePosition(int32_t x, int32_t y, PIXEL_POSITION & r_pos)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (x >= rRegion.sx && y >= rRegion.sy && x < rRegion.ex && y < rRegion.ey)
		{
			r_pos.x = rRegion.sx;
			r_pos.y = rRegion.sy;
			r_pos.z = 0;
			return true;
		}
	}

	return false;
}

const TMapRegion * SECTREE_MANAGER::FindRegionByPartialName(const char* szMapName)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		//if (rRegion.index == lMapIndex)
		//return &rRegion;
		if (rRegion.strMapName.find(szMapName))
			return &rRegion; // 캐싱 해서 빠르게 하자
	}

	return NULL;
}

const TMapRegion * SECTREE_MANAGER::GetMapRegion(int32_t lMapIndex)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (rRegion.index == lMapIndex)
			return &rRegion;
	}

	return NULL;
}

int32_t SECTREE_MANAGER::GetMapIndex(int32_t x, int32_t y)
{
	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (x >= rRegion.sx && y >= rRegion.sy && x < rRegion.ex && y < rRegion.ey)
			return rRegion.index;
	}

	sys_log(0, "SECTREE_MANAGER::GetMapIndex(%d, %d)", x, y);

	std::vector<TMapRegion>::iterator i;
	for (i = m_vec_mapRegion.begin(); i !=m_vec_mapRegion.end(); ++i)
	{
		TMapRegion & rRegion = *i;
		sys_log(0, "%d: (%d, %d) ~ (%d, %d)", rRegion.index, rRegion.sx, rRegion.sy, rRegion.ex, rRegion.ey);
	}

	return 0;
}

int32_t SECTREE_MANAGER::Build(const char * c_pszListFileName, const char* c_pszMapBasePath)
{
	if (true == test_server)
	{
		sys_log ( 0, "[BUILD] Build %s %s ", c_pszListFileName, c_pszMapBasePath );
	}

	FILE* fp = fopen(c_pszListFileName, "r");

	if (NULL == fp)
		return 0;

	char buf[256 + 1];
	char szFilename[256];
	char szMapName[256];
	int32_t iIndex;

	while (fgets(buf, 256, fp))
	{
		*strrchr(buf, '\n') = '\0';

		if (!strncmp(buf, "//", 2) || *buf == '#')
			continue;

		sscanf(buf, " %d %s ", &iIndex, szMapName);

		snprintf(szFilename, sizeof(szFilename), "%s/%s/Setting.txt", c_pszMapBasePath, szMapName);

		TMapSetting setting;
		setting.iIndex = iIndex;

		if (!LoadSettingFile(iIndex, szFilename, setting))
		{
			sys_err("can't load file %s in LoadSettingFile", szFilename);
			fclose(fp);
			return 0;
		}

		snprintf(szFilename, sizeof(szFilename), "%s/%s/Town.txt", c_pszMapBasePath, szMapName);

		if (!LoadMapRegion(szFilename, setting, szMapName))
		{
			sys_err("can't load file %s in LoadMapRegion", szFilename);
			fclose(fp);
			return 0;
		}

		if (true == test_server)
			sys_log ( 0,"[BUILD] Build %s %s %d ",c_pszMapBasePath, szMapName, iIndex );

		// 먼저 이 서버에서 이 맵의 몬스터를 스폰해야 하는가 확인 한다.
		if (map_allow_find(iIndex))
		{
			LPSECTREE_MAP pkMapSectree = BuildSectreeFromSetting(setting);
			m_map_pkSectree.insert(std::map<uint32_t, LPSECTREE_MAP>::value_type(iIndex, pkMapSectree));

			snprintf(szFilename, sizeof(szFilename), "%s/%s/server_attr", c_pszMapBasePath, szMapName);
			LoadAttribute(pkMapSectree, szFilename, setting);

			snprintf(szFilename, sizeof(szFilename), "%s/%s/regen.txt", c_pszMapBasePath, szMapName);
			regen_load(szFilename, setting.iIndex, setting.iBaseX, setting.iBaseY);

			snprintf(szFilename, sizeof(szFilename), "%s/%s/npc.txt", c_pszMapBasePath, szMapName);
			regen_load(szFilename, setting.iIndex, setting.iBaseX, setting.iBaseY);

			snprintf(szFilename, sizeof(szFilename), "%s/%s/boss.txt", c_pszMapBasePath, szMapName);
			regen_load(szFilename, setting.iIndex, setting.iBaseX, setting.iBaseY);

			snprintf(szFilename, sizeof(szFilename), "%s/%s/stone.txt", c_pszMapBasePath, szMapName);
			regen_load(szFilename, setting.iIndex, setting.iBaseX, setting.iBaseY);

			snprintf(szFilename, sizeof(szFilename), "%s/%s/dungeon.txt", c_pszMapBasePath, szMapName);
			LoadDungeon(iIndex, szFilename);

			pkMapSectree->Build();
		}
	}

	fclose(fp);

	return 1;
}

bool SECTREE_MANAGER::IsMovablePosition(int32_t lMapIndex, int32_t x, int32_t y)
{
	LPSECTREE tree = SECTREE_MANAGER::instance().Get(lMapIndex, x, y);

	if (!tree)
		return false;

	return (!tree->IsAttr(x, y, ATTR_BLOCK | ATTR_OBJECT));
}

bool SECTREE_MANAGER::GetMovablePosition(int32_t lMapIndex, int32_t x, int32_t y, PIXEL_POSITION & pos)
{
	int32_t i = 0;

	do
	{
		int32_t dx = x + aArroundCoords[i].x;
		int32_t dy = y + aArroundCoords[i].y;

		LPSECTREE tree = SECTREE_MANAGER::instance().Get(lMapIndex, dx, dy);

		if (!tree)
			continue;

		if (!tree->IsAttr(dx, dy, ATTR_BLOCK | ATTR_OBJECT))
		{
			pos.x = dx;
			pos.y = dy;
			return true;
		}
	} while (++i < ARROUND_COORD_MAX_NUM);

	pos.x = x;
	pos.y = y;
	return false;
}

bool SECTREE_MANAGER::GetValidLocation(int32_t lMapIndex, int32_t x, int32_t y, int32_t & r_lValidMapIndex, PIXEL_POSITION & r_pos, uint8_t empire)
{
	LPSECTREE_MAP pkSectreeMap = GetMap(lMapIndex);

	if (!pkSectreeMap)
	{
		if (lMapIndex >= 10000)
		{
/*			int32_t m = lMapIndex / 10000;
			if (m == 216)
			{
				if (GetRecallPositionByEmpire (m, empire, r_pos))
				{
					r_lValidMapIndex = m;
					return true;
				}
				else 
					return false;
			}*/
			return GetValidLocation(lMapIndex / 10000, x, y, r_lValidMapIndex, r_pos);
		}
		else
		{
			sys_err("cannot find sectree_map by map index %d", lMapIndex);
			return false;
		}
	}

	int32_t lRealMapIndex = lMapIndex;

	if (lRealMapIndex >= 10000)
		lRealMapIndex = lRealMapIndex / 10000;

	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (rRegion.index == lRealMapIndex)
		{
			LPSECTREE tree = pkSectreeMap->Find(x, y);

			if (!tree)
			{
				sys_err("cannot find tree by %d %d (map index %d)", x, y, lMapIndex);
				return false;
			}

			r_lValidMapIndex = lMapIndex;
			r_pos.x = x;
			r_pos.y = y;
			return true;
		}
	}

	sys_err("invalid location (map index %d %d x %d)", lRealMapIndex, x, y);
	return false;
}

bool SECTREE_MANAGER::GetRandomLocation(int32_t lMapIndex, PIXEL_POSITION & r_pos, uint32_t dwCurrentX, uint32_t dwCurrentY, int32_t iMaxDistance)
{
	LPSECTREE_MAP pkSectreeMap = GetMap(lMapIndex);

	if (!pkSectreeMap)
		return false;

	uint32_t x, y;

	std::vector<TMapRegion>::iterator it = m_vec_mapRegion.begin();

	while (it != m_vec_mapRegion.end())
	{
		TMapRegion & rRegion = *(it++);

		if (rRegion.index != lMapIndex)
			continue;

		int32_t i = 0;

		while (i++ < 100)
		{
			x = number(rRegion.sx + 50, rRegion.ex - 50);
			y = number(rRegion.sy + 50, rRegion.ey - 50);

			if (iMaxDistance != 0)
			{
				int32_t d;

				d = abs((float)dwCurrentX - x);

				if (d > iMaxDistance)
				{
					if (x < dwCurrentX)
						x = dwCurrentX - iMaxDistance;
					else
						x = dwCurrentX + iMaxDistance;
				}

				d = abs((float)dwCurrentY - y);

				if (d > iMaxDistance)
				{
					if (y < dwCurrentY)
						y = dwCurrentY - iMaxDistance;
					else
						y = dwCurrentY + iMaxDistance;
				}
			}

			LPSECTREE tree = pkSectreeMap->Find(x, y);

			if (!tree)
				continue;

			if (tree->IsAttr(x, y, ATTR_BLOCK | ATTR_OBJECT))
				continue;

			r_pos.x = x;
			r_pos.y = y;
			return true;
		}
	}

	return false;
}

int32_t SECTREE_MANAGER::CreatePrivateMap(int32_t lMapIndex)
{
	if (lMapIndex >= 10000) // 10000번 이상의 맵은 없다. (혹은 이미 private 이다)
		return 0;

	LPSECTREE_MAP pkMapSectree = GetMap(lMapIndex);

	if (!pkMapSectree)
	{
		sys_err("Cannot find map index %d", lMapIndex);
		return 0;
	}

	// <Factor> Circular private map indexing
	int32_t base = lMapIndex * 10000;
	int32_t index_cap = 10000;
	if ( lMapIndex == 107 || lMapIndex == 108 || lMapIndex == 109 ) {
		index_cap = (test_server ? 1 : 51);
	}
	PrivateIndexMapType::iterator it = next_private_index_map_.find(lMapIndex);
	if (it == next_private_index_map_.end()) {
		it = next_private_index_map_.insert(PrivateIndexMapType::value_type(lMapIndex, 0)).first;
	}
	int32_t i, next_index = it->second;
	for (i = 0; i < index_cap; ++i) {
		if (GetMap(base + next_index) == NULL) {
			break; // available
		}
		if (++next_index >= index_cap) {
			next_index = 0;
		}
	}
	if (i == index_cap) {
		// No available index
		return 0;
	}
	int32_t lNewMapIndex = base + next_index;
	if (++next_index >= index_cap) {
		next_index = 0;
	}
	it->second = next_index;

	/*
	int32_t i;

	for (i = 0; i < 10000; ++i)
	{
		if (!GetMap((lMapIndex * 10000) + i))
			break;
	}
	
	if ( test_server )
		sys_log( 0, "Create Dungeon : OrginalMapindex %d NewMapindex %d", lMapIndex, i );
	
	if ( lMapIndex == 107 || lMapIndex == 108 || lMapIndex == 109 )
	{
		if ( test_server )
		{
			if ( i > 0 )
				return NULL;
		}
		else
		{
			if ( i > 50 )
				return NULL;
			
		}
	}

	if (i == 10000)
	{
		sys_err("not enough private map index (map_index %d)", lMapIndex);
		return 0;
	}

	int32_t lNewMapIndex = lMapIndex * 10000 + i;
	*/

	pkMapSectree = M2_NEW SECTREE_MAP(*pkMapSectree);
	m_map_pkSectree.insert(std::map<uint32_t, LPSECTREE_MAP>::value_type(lNewMapIndex, pkMapSectree));

	sys_log(0, "PRIVATE_MAP: %d created (original %d)", lNewMapIndex, lMapIndex);
	return lNewMapIndex;
}

struct FDestroyPrivateMapEntity
{
	void operator() (LPENTITY ent)
	{
		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER) ent;
			sys_log(0, "PRIVAE_MAP: removing character %s", ch->GetName());

			if (ch->GetDesc())
				DESC_MANAGER::instance().DestroyDesc(ch->GetDesc());
			else
				M2_DESTROY_CHARACTER(ch);
		}
		else if (ent->IsType(ENTITY_ITEM))
		{
			LPITEM item = (LPITEM) ent;
			sys_log(0, "PRIVATE_MAP: removing item %s", item->GetName());

			M2_DESTROY_ITEM(item);
		}
		else
			sys_err("PRIVAE_MAP: trying to remove unknown entity %d", ent->GetType());
	}
};

void SECTREE_MANAGER::DestroyPrivateMap(int32_t lMapIndex)
{
	if (lMapIndex < 10000) // private map 은 인덱스가 10000 이상 이다.
		return;

	LPSECTREE_MAP pkMapSectree = GetMap(lMapIndex);

	if (!pkMapSectree)
		return;

	// 이 맵 위에 현재 존재하는 것들을 전부 없앤다.
	// WARNING:
	// 이 맵에 있지만 어떤 Sectree에도 존재하지 않을 수 있음
	// 따라서 여기서 delete 할 수 없으므로 포인터가 깨질 수 있으니
	// 별도 처리를 해야함
	FDestroyPrivateMapEntity f;
	pkMapSectree->for_each(f);

	m_map_pkSectree.erase(lMapIndex);
	M2_DELETE(pkMapSectree);

	sys_log(0, "PRIVATE_MAP: %d destroyed", lMapIndex);
}

TAreaMap& SECTREE_MANAGER::GetDungeonArea(int32_t lMapIndex)
{
	itertype(m_map_pkArea) it = m_map_pkArea.find(lMapIndex);

	if (it == m_map_pkArea.end())
	{
		return m_map_pkArea[-1]; // 임시로 빈 Area를 리턴
	}
	return it->second;
}

void SECTREE_MANAGER::SendNPCPosition(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();
	if (!d)
		return;

	int32_t lMapIndex = ch->GetMapIndex();

	if (m_mapNPCPosition[lMapIndex].empty())
		return;

	TEMP_BUFFER buf;
	TPacketGCNPCPosition p;
	p.header = HEADER_GC_NPC_POSITION;
	p.count = m_mapNPCPosition[lMapIndex].size();

	TNPCPosition np;

	// TODO m_mapNPCPosition[lMapIndex] 를 보내주세요
	itertype(m_mapNPCPosition[lMapIndex]) it;

	for (it = m_mapNPCPosition[lMapIndex].begin(); it != m_mapNPCPosition[lMapIndex].end(); ++it)
	{
		np.bType = it->bType;
		strlcpy(np.name, it->name, sizeof(np.name));
		np.x = it->x;
		np.y = it->y;
		buf.write(&np, sizeof(np));
	}

	p.size = sizeof(p) + buf.size();

	if (buf.size())
	{
		d->BufferedPacket(&p, sizeof(TPacketGCNPCPosition));
		d->Packet(buf.read_peek(), buf.size());
	}
	else
		d->Packet(&p, sizeof(TPacketGCNPCPosition));
}

void SECTREE_MANAGER::InsertNPCPosition(int32_t lMapIndex, uint8_t bType, const char* szName, int32_t x, int32_t y)
{
	m_mapNPCPosition[lMapIndex].push_back(npc_info(bType, szName, x, y));
}

uint8_t SECTREE_MANAGER::GetEmpireFromMapIndex(int32_t lMapIndex)
{
	if (lMapIndex >= 1 && lMapIndex <= 20)
		return 1;

	if (lMapIndex >= 21 && lMapIndex <= 40)
		return 2;

	if (lMapIndex >= 41 && lMapIndex <= 60)
		return 3;

	if ( lMapIndex == 184 || lMapIndex == 185 )
		return 1;
	
	if ( lMapIndex == 186 || lMapIndex == 187 )
		return 2;
	
	if ( lMapIndex == 188 || lMapIndex == 189 )
		return 3;

	switch ( lMapIndex )
	{
		case 190 :
			return 1;
		case 191 :
			return 2;
		case 192 :
			return 3;
	}
	
	return 0;
}

class FRemoveIfAttr
{
	public:
		FRemoveIfAttr(LPSECTREE pkTree, uint32_t dwAttr) : m_pkTree(pkTree), m_dwCheckAttr(dwAttr)
		{
		}

		void operator () (LPENTITY entity)
		{
			if (!m_pkTree->IsAttr(entity->GetX(), entity->GetY(), m_dwCheckAttr))
				return;

			if (entity->IsType(ENTITY_ITEM))
			{
				M2_DESTROY_ITEM((LPITEM) entity);
			}
			else if (entity->IsType(ENTITY_CHARACTER))
			{
				LPCHARACTER ch = (LPCHARACTER) entity;

				if (ch->IsPC())
				{
					PIXEL_POSITION pos;

					if (SECTREE_MANAGER::instance().GetRecallPositionByEmpire(ch->GetMapIndex(), ch->GetEmpire(), pos))
						ch->WarpSet(pos.x, pos.y);
					else
						ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));
				}
				else
					ch->Dead();
			}
		}

		LPSECTREE m_pkTree;
		uint32_t m_dwCheckAttr;
};

bool SECTREE_MANAGER::ForAttrRegionCell( int32_t lMapIndex, int32_t lCX, int32_t lCY, uint32_t dwAttr, EAttrRegionMode mode )
{
	SECTREEID id;

	id.coord.x = lCX / (SECTREE_SIZE / CELL_SIZE);
	id.coord.y = lCY / (SECTREE_SIZE / CELL_SIZE);

	int32_t lTreeCX = id.coord.x * (SECTREE_SIZE / CELL_SIZE);
	int32_t lTreeCY = id.coord.y * (SECTREE_SIZE / CELL_SIZE);

	LPSECTREE pSec = Get( lMapIndex, id.package );
	if ( !pSec )
		return false;

	switch (mode)
	{
		case ATTR_REGION_MODE_SET:
			pSec->SetAttribute( lCX - lTreeCX, lCY - lTreeCY, dwAttr );
			break;

		case ATTR_REGION_MODE_REMOVE:
			pSec->RemoveAttribute( lCX - lTreeCX, lCY - lTreeCY, dwAttr );
			break;

		case ATTR_REGION_MODE_CHECK:
			if ( pSec->IsAttr( lCX * CELL_SIZE, lCY * CELL_SIZE, ATTR_OBJECT ) )
				return true;
			break;

		default:
			sys_err("Unknown region mode %u", mode);
			break;
	}

	return false;
}

bool SECTREE_MANAGER::ForAttrRegionRightAngle( int32_t lMapIndex, int32_t lCX, int32_t lCY, int32_t lCW, int32_t lCH, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode )
{
	if (1 == lRotate/90 || 3 == lRotate/90)
	{
		for (int32_t x = 0; x < lCH; ++x)
			for (int32_t y = 0; y < lCW; ++y)
			{
				if ( ForAttrRegionCell( lMapIndex, lCX + x, lCY + y, dwAttr, mode ) )
					return true;
			}
	}
	if (0 == lRotate/90 || 2 == lRotate/90)
	{
		for (int32_t x = 0; x < lCW; ++x)
			for (int32_t y = 0; y < lCH; ++y)
			{
				if ( ForAttrRegionCell( lMapIndex, lCX + x, lCY + y, dwAttr, mode) )
					return true;
			}
	}

	return mode == ATTR_REGION_MODE_CHECK ? false : true;
}

#define min( l, r )	((l) < (r) ? (l) : (r))
#define max( l, r )	((l) < (r) ? (r) : (l))

bool SECTREE_MANAGER::ForAttrRegionFreeAngle( int32_t lMapIndex, int32_t lCX, int32_t lCY, int32_t lCW, int32_t lCH, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode )
{
	float fx1 = (-lCW/2) * sinf(float(lRotate)/180.0f*3.14f) + (-lCH/2) * cosf(float(lRotate)/180.0f*3.14f);
	float fy1 = (-lCW/2) * cosf(float(lRotate)/180.0f*3.14f) - (-lCH/2) * sinf(float(lRotate)/180.0f*3.14f);

	float fx2 = (+lCW/2) * sinf(float(lRotate)/180.0f*3.14f) + (-lCH/2) * cosf(float(lRotate)/180.0f*3.14f);
	float fy2 = (+lCW/2) * cosf(float(lRotate)/180.0f*3.14f) - (-lCH/2) * sinf(float(lRotate)/180.0f*3.14f);

	float fx3 = (-lCW/2) * sinf(float(lRotate)/180.0f*3.14f) + (+lCH/2) * cosf(float(lRotate)/180.0f*3.14f);
	float fy3 = (-lCW/2) * cosf(float(lRotate)/180.0f*3.14f) - (+lCH/2) * sinf(float(lRotate)/180.0f*3.14f);

	float fx4 = (+lCW/2) * sinf(float(lRotate)/180.0f*3.14f) + (+lCH/2) * cosf(float(lRotate)/180.0f*3.14f);
	float fy4 = (+lCW/2) * cosf(float(lRotate)/180.0f*3.14f) - (+lCH/2) * sinf(float(lRotate)/180.0f*3.14f);

	float fdx1 = fx2 - fx1;
	float fdy1 = fy2 - fy1;
	float fdx2 = fx1 - fx3;
	float fdy2 = fy1 - fy3;

	if (0 == fdx1 || 0 == fdx2)
	{
		sys_err( "SECTREE_MANAGER::ForAttrRegion - Unhandled exception. MapIndex: %d", lMapIndex );
		return false;
	}

	float fTilt1 = float(fdy1) / float(fdx1);
	float fTilt2 = float(fdy2) / float(fdx2);
	float fb1 = fy1 - fTilt1*fx1;
	float fb2 = fy1 - fTilt2*fx1;
	float fb3 = fy4 - fTilt1*fx4;
	float fb4 = fy4 - fTilt2*fx4;

	float fxMin = min(fx1, min(fx2, min(fx3, fx4)));
	float fxMax = max(fx1, max(fx2, max(fx3, fx4)));
	for (int32_t i = int32_t(fxMin); i < int32_t(fxMax); ++i)
	{
		float fyValue1 = fTilt1*i + min(fb1, fb3);
		float fyValue2 = fTilt2*i + min(fb2, fb4);

		float fyValue3 = fTilt1*i + max(fb1, fb3);
		float fyValue4 = fTilt2*i + max(fb2, fb4);

		float fMinValue;
		float fMaxValue;
		if (abs(int32_t(fyValue1)) < abs(int32_t(fyValue2)))
			fMaxValue = fyValue1;
		else
			fMaxValue = fyValue2;
		if (abs(int32_t(fyValue3)) < abs(int32_t(fyValue4)))
			fMinValue = fyValue3;
		else
			fMinValue = fyValue4;

		for (int32_t j = int32_t(min(fMinValue, fMaxValue)); j < int32_t(max(fMinValue, fMaxValue)); ++j) {
			if ( ForAttrRegionCell( lMapIndex, lCX + (lCW / 2) + i, lCY + (lCH / 2) + j, dwAttr, mode ) )
				return true;
		}
	}

	return mode == ATTR_REGION_MODE_CHECK ? false : true;
}

bool SECTREE_MANAGER::ForAttrRegion(int32_t lMapIndex, int32_t lStartX, int32_t lStartY, int32_t lEndX, int32_t lEndY, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode)
{
	LPSECTREE_MAP pkMapSectree = GetMap(lMapIndex);

	if (!pkMapSectree)
	{
		sys_err("Cannot find SECTREE_MAP by map index %d", lMapIndex);
		return mode == ATTR_REGION_MODE_CHECK ? true : false;
	}

	//
	// 영역의 좌표를 Cell 의 크기에 맞춰 확장한다.
	//

	lStartX	-= lStartX % CELL_SIZE;
	lStartY	-= lStartY % CELL_SIZE;
	lEndX	+= lEndX % CELL_SIZE;
	lEndY	+= lEndY % CELL_SIZE;

	//
	// Cell 좌표를 구한다.
	// 

	int32_t lCX = lStartX / CELL_SIZE;
	int32_t lCY = lStartY / CELL_SIZE;
	int32_t lCW = (lEndX - lStartX) / CELL_SIZE;
	int32_t lCH = (lEndY - lStartY) / CELL_SIZE;

	sys_log(1, "ForAttrRegion %d %d ~ %d %d", lStartX, lStartY, lEndX, lEndY);

	lRotate = lRotate % 360;

	if (0 == lRotate % 90)
		return ForAttrRegionRightAngle( lMapIndex, lCX, lCY, lCW, lCH, lRotate, dwAttr, mode );

	return ForAttrRegionFreeAngle( lMapIndex, lCX, lCY, lCW, lCH, lRotate, dwAttr, mode );
}

bool SECTREE_MANAGER::SaveAttributeToImage(int32_t lMapIndex, const char * c_pszFileName, LPSECTREE_MAP pMapSrc)
{
	LPSECTREE_MAP pMap = SECTREE_MANAGER::GetMap(lMapIndex);

	if (!pMap)
	{
		if (pMapSrc)
			pMap = pMapSrc;
		else
		{
			sys_err("cannot find sectree_map %d", lMapIndex);
			return false;
		}
	}

	int32_t iMapHeight = pMap->m_setting.iHeight / 128 / 200;
	int32_t iMapWidth = pMap->m_setting.iWidth / 128 / 200;

	if (iMapHeight < 0 || iMapWidth < 0)
	{
		sys_err("map size error w %d h %d", iMapWidth, iMapHeight);
		return false;
	}

	sys_log(0, "SaveAttributeToImage w %d h %d file %s", iMapWidth, iMapHeight, c_pszFileName);

	CTargaImage image;

	image.Create(512 * iMapWidth, 512 * iMapHeight);

	sys_log(0, "1");

	uint32_t * pdwDest = (uint32_t *) image.GetBasePointer();

	int32_t pixels = 0;
	int32_t x, x2;
	int32_t y, y2;

	sys_log(0, "2 %p", pdwDest);

	uint32_t * pdwLine = M2_NEW uint32_t[SECTREE_SIZE / CELL_SIZE];

	for (y = 0; y < 4 * iMapHeight; ++y)
	{
		for (y2 = 0; y2 < SECTREE_SIZE / CELL_SIZE; ++y2)
		{
			for (x = 0; x < 4 * iMapWidth; ++x)
			{
				SECTREEID id;

				id.coord.x = x + pMap->m_setting.iBaseX / SECTREE_SIZE;
				id.coord.y = y + pMap->m_setting.iBaseY / SECTREE_SIZE;

				LPSECTREE pSec = pMap->Find(id.package);

				if (!pSec)
				{
					sys_err("cannot get sectree for %d %d %d %d", id.coord.x, id.coord.y, pMap->m_setting.iBaseX, pMap->m_setting.iBaseY);
					continue;
				}

				pSec->m_pkAttribute->CopyRow(y2, pdwLine);

				if (!pdwLine)
				{
					sys_err("cannot get attribute line pointer");
					M2_DELETE_ARRAY(pdwLine);
					continue;
				}

				for (x2 = 0; x2 < SECTREE_SIZE / CELL_SIZE; ++x2)
				{
					uint32_t dwColor;

					if (IS_SET(pdwLine[x2], ATTR_WATER))
						dwColor = 0xff0000ff;
					else if (IS_SET(pdwLine[x2], ATTR_BANPK))
						dwColor = 0xff00ff00;
					else if (IS_SET(pdwLine[x2], ATTR_BLOCK))
						dwColor = 0xffff0000;
					else
						dwColor = 0xffffffff;

					*(pdwDest++) = dwColor;
					pixels++;
				}
			}
		}
	}

	M2_DELETE_ARRAY(pdwLine);
	sys_log(0, "3");

	if (image.Save(c_pszFileName))
	{
		sys_log(0, "SECTREE: map %d attribute saved to %s (%d bytes)", lMapIndex, c_pszFileName, pixels);
		return true;
	}
	else
	{
		sys_err("cannot save file, map_index %d filename %s", lMapIndex, c_pszFileName);
		return false;
	}
}

struct FPurgeMonsters
{
	void operator() (LPENTITY ent)
	{
		if ( ent->IsType(ENTITY_CHARACTER) == true )
		{
			LPCHARACTER lpChar = (LPCHARACTER)ent;

			if ( lpChar->IsMonster() == true && !lpChar->IsPet())
			{
				M2_DESTROY_CHARACTER(lpChar);
			}
		}
	}
};

void SECTREE_MANAGER::PurgeMonstersInMap(int32_t lMapIndex)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if ( sectree != NULL )
	{
		struct FPurgeMonsters f;

		sectree->for_each( f );
	}
}

struct FPurgeStones
{
	void operator() (LPENTITY ent)
	{
		if ( ent->IsType(ENTITY_CHARACTER) == true )
		{
			LPCHARACTER lpChar = (LPCHARACTER)ent;

			if ( lpChar->IsStone() == true )
			{
				M2_DESTROY_CHARACTER(lpChar);
			}
		}
	}
};

void SECTREE_MANAGER::PurgeStonesInMap(int32_t lMapIndex)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if ( sectree != NULL )
	{
		struct FPurgeStones f;

		sectree->for_each( f );
	}
}

struct FPurgeNPCs
{
	void operator() (LPENTITY ent)
	{
		if ( ent->IsType(ENTITY_CHARACTER) == true )
		{
			LPCHARACTER lpChar = (LPCHARACTER)ent;

			if ( lpChar->IsNPC() == true && !lpChar->IsPet())
			{
				M2_DESTROY_CHARACTER(lpChar);
			}
		}
	}
};

void SECTREE_MANAGER::PurgeNPCsInMap(int32_t lMapIndex)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if ( sectree != NULL )
	{
		struct FPurgeNPCs f;

		sectree->for_each( f );
	}
}

struct FCountMonsters
{
	std::map<VID, VID> m_map_Monsters;

	void operator() (LPENTITY ent)
	{
		if ( ent->IsType(ENTITY_CHARACTER) == true )
		{
			LPCHARACTER lpChar = (LPCHARACTER)ent;

			if ( lpChar->IsMonster() == true )
			{
				m_map_Monsters[lpChar->GetVID()] = lpChar->GetVID();
			}
		}
	}
};

uint32_t SECTREE_MANAGER::GetMonsterCountInMap(int32_t lMapIndex)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if ( sectree != NULL )
	{
		struct FCountMonsters f;

		sectree->for_each( f );

		return f.m_map_Monsters.size();
	}

	return 0;
}

struct FCountSpecifiedMonster
{
	uint32_t SpecifiedVnum;
	uint32_t cnt;

	FCountSpecifiedMonster(uint32_t id)
		: SpecifiedVnum(id), cnt(0)
	{}

	void operator() (LPENTITY ent)
	{
		if (true == ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER pChar = static_cast<LPCHARACTER>(ent);

			if (true == pChar->IsStone())
			{
				if (pChar->GetMobTable().dwVnum == SpecifiedVnum)
					cnt++;
			}
		}
	}
};

uint32_t SECTREE_MANAGER::GetMonsterCountInMap(int32_t lMapIndex, uint32_t dwVnum)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if (NULL != sectree)
	{
		struct FCountSpecifiedMonster f(dwVnum);

		sectree->for_each( f );

		return f.cnt;
	}

	return 0;
}


