#ifndef __INC_METIN_II_GAME_SECTREE_MANAGER_H__
#define __INC_METIN_II_GAME_SECTREE_MANAGER_H__

#include "sectree.h"


typedef struct SMapRegion
{
	int32_t			index;
	int32_t			sx, sy, ex, ey;
	PIXEL_POSITION	posSpawn;

	bool		bEmpireSpawnDifferent;
	PIXEL_POSITION	posEmpire[3];

	std::string		strMapName;
} TMapRegion;

struct TAreaInfo
{
	int32_t sx, sy, ex, ey, dir;
	TAreaInfo(int32_t sx, int32_t sy, int32_t ex, int32_t ey, int32_t dir)
		: sx(sx), sy(sy), ex(ex), ey(ey), dir(dir)
		{}
};

struct npc_info
{
	uint8_t bType;
	const char* name;
	int32_t x, y;
	npc_info(uint8_t bType, const char* name, int32_t x, int32_t y)
		: bType(bType), name(name), x(x), y(y)
		{}
};

typedef std::map<std::string, TAreaInfo> TAreaMap;

typedef struct SSetting
{
	int32_t			iIndex;
	int32_t			iCellScale;
	int32_t			iBaseX;
	int32_t			iBaseY;
	int32_t			iWidth;
	int32_t			iHeight;

	PIXEL_POSITION	posSpawn;
} TMapSetting;

class SECTREE_MAP
{
	public:
		typedef std::map<uint32_t, LPSECTREE> MapType;

		SECTREE_MAP();
		SECTREE_MAP(SECTREE_MAP & r);
		virtual ~SECTREE_MAP();

		bool Add(uint32_t key, LPSECTREE sectree) {
			return map_.insert(MapType::value_type(key, sectree)).second;
		}

		LPSECTREE	Find(uint32_t dwPackage);
		LPSECTREE	Find(uint32_t x, uint32_t y);
		void		Build();

		TMapSetting	m_setting;

		template< typename Func >
		void for_each( Func & rfunc )
		{
			// <Factor> Using snapshot copy to avoid side-effects
			FCollectEntity collector;
			std::map<uint32_t, LPSECTREE>::iterator it = map_.begin();
			for ( ; it != map_.end(); ++it)
			{
				LPSECTREE sectree = it->second;
				sectree->for_each_entity(collector);
			}
			collector.ForEach(rfunc);
			/*
			std::map<uint32_t,LPSECTREE>::iterator i = map_.begin();
			for (; i != map_.end(); ++i )
			{
				LPSECTREE pSec = i->second;
				pSec->for_each_entity( rfunc );
			}
			*/
		}

		void DumpAllToSysErr() {
			SECTREE_MAP::MapType::iterator i;
			for (i = map_.begin(); i != map_.end(); ++i)
			{
				sys_err("SECTREE %x(%u, %u)", i->first, i->first & 0xffff, i->first >> 16);
			}
		}

	private:
		MapType map_;
};

enum EAttrRegionMode
{
	ATTR_REGION_MODE_SET,
	ATTR_REGION_MODE_REMOVE,
	ATTR_REGION_MODE_CHECK,
};

class SECTREE_MANAGER : public singleton<SECTREE_MANAGER>
{
	public:
		SECTREE_MANAGER();
		virtual ~SECTREE_MANAGER();

		LPSECTREE_MAP GetMap(int32_t lMapIndex);
		LPSECTREE 	Get(uint32_t dwIndex, uint32_t package);
		LPSECTREE 	Get(uint32_t dwIndex, uint32_t x, uint32_t y);

		template< typename Func >
		void for_each( int32_t iMapIndex, Func & rfunc )
		{
			LPSECTREE_MAP pSecMap = SECTREE_MANAGER::instance().GetMap( iMapIndex );
			if ( pSecMap )
			{
				pSecMap->for_each( rfunc );
			}
		}
		
		int32_t		LoadSettingFile(int32_t lIndex, const char * c_pszSettingFileName, TMapSetting & r_setting);
		bool		LoadMapRegion(const char * c_pszFileName, TMapSetting & r_Setting, const char * c_pszMapName);
		int32_t		Build(const char * c_pszListFileName, const char* c_pszBasePath);
		LPSECTREE_MAP BuildSectreeFromSetting(TMapSetting & r_setting);
		bool		LoadAttribute(LPSECTREE_MAP pkMapSectree, const char * c_pszFileName, TMapSetting & r_setting);
		void		LoadDungeon(int32_t iIndex, const char * c_pszFileName);
		bool		GetValidLocation(int32_t lMapIndex, int32_t x, int32_t y, int32_t & r_lValidMapIndex, PIXEL_POSITION & r_pos, uint8_t empire = 0);
		bool		GetSpawnPosition(int32_t x, int32_t y, PIXEL_POSITION & r_pos);
		bool		GetSpawnPositionByMapIndex(int32_t lMapIndex, PIXEL_POSITION & r_pos);
		bool		GetRecallPositionByEmpire(int32_t iMapIndex, uint8_t bEmpire, PIXEL_POSITION & r_pos);

		const TMapRegion *	GetMapRegion(int32_t lMapIndex);
		int32_t			GetMapIndex(int32_t x, int32_t y);
		const TMapRegion *	FindRegionByPartialName(const char* szMapName);

		bool		GetMapBasePosition(int32_t x, int32_t y, PIXEL_POSITION & r_pos);
		bool		GetMapBasePositionByMapIndex(int32_t lMapIndex, PIXEL_POSITION & r_pos);
		bool		GetMovablePosition(int32_t lMapIndex, int32_t x, int32_t y, PIXEL_POSITION & pos);
		bool		IsMovablePosition(int32_t lMapIndex, int32_t x, int32_t y);
		bool		GetCenterPositionOfMap(int32_t lMapIndex, PIXEL_POSITION & r_pos);
		bool        GetRandomLocation(int32_t lMapIndex, PIXEL_POSITION & r_pos, uint32_t dwCurrentX = 0, uint32_t dwCurrentY = 0, int32_t iMaxDistance = 0);

		int32_t		CreatePrivateMap(int32_t lMapIndex);	// returns new private map index, returns 0 when fail
		void		DestroyPrivateMap(int32_t lMapIndex);

		TAreaMap&	GetDungeonArea(int32_t lMapIndex);
		void		SendNPCPosition(LPCHARACTER ch);
		void		InsertNPCPosition(int32_t lMapIndex, uint8_t bType, const char* szName, int32_t x, int32_t y);

		uint8_t		GetEmpireFromMapIndex(int32_t lMapIndex);

		void		PurgeMonstersInMap(int32_t lMapIndex);
		void		PurgeStonesInMap(int32_t lMapIndex);
		void		PurgeNPCsInMap(int32_t lMapIndex);
		uint32_t		GetMonsterCountInMap(int32_t lMapIndex);
		uint32_t		GetMonsterCountInMap(int32_t lMpaIndex, uint32_t dwVnum);

		/// 영역에 대해 Sectree 의 Attribute 에 대해 특정한 처리를 수행한다.
		/**
		 * @param [in]	lMapIndex 적용할 Map index
		 * @param [in]	lStartX 사각형 영역의 가장 왼쪽 좌표
		 * @param [in]	lStartY 사각형 영역의 가장 위쪽 좌표
		 * @param [in]	lEndX 사각형 영역의 가장 오른쪽 좌표
		 * @param [in]	lEndY 사각형 영역의 가장 아랫쪽 좌표
		 * @param [in]	lRotate 영역에 대해 회전할 각
		 * @param [in]	dwAttr 적용할 Attribute
		 * @param [in]	mode Attribute 에 대해 처리할 type
		 */
		bool		ForAttrRegion(int32_t lMapIndex, int32_t lStartX, int32_t lStartY, int32_t lEndX, int32_t lEndY, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode);

		bool		SaveAttributeToImage(int32_t lMapIndex, const char * c_pszFileName, LPSECTREE_MAP pMapSrc = NULL);

	private:

		/// 직각의 사각형 영역에 대해 Sectree 의 Attribute 에 대해 특정한 처리를 수행한다.
		/**
		 * @param [in]	lMapIndex 적용할 Map index
		 * @param [in]	lCX 사각형 영역의 가장 왼쪽 Cell 의 좌표
		 * @param [in]	lCY 사각형 영역의 가장 위쪽 Cell 의 좌표
		 * @param [in]	lCW 사각형 영역의 Cell 단위 폭
		 * @param [in]	lCH 사각형 영역의 Cell 단위 높이
		 * @param [in]	lRotate 회전할 각(직각)
		 * @param [in]	dwAttr 적용할 Attribute
		 * @param [in]	mode Attribute 에 대해 처리할 type
		 */
		bool		ForAttrRegionRightAngle( int32_t lMapIndex, int32_t lCX, int32_t lCY, int32_t lCW, int32_t lCH, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode );

		/// 직각 이외의 사각형 영역에 대해 Sectree 의 Attribute 에 대해 특정한 처리를 수행한다.
		/**
		 * @param [in]	lMapIndex 적용할 Map index
		 * @param [in]	lCX 사각형 영역의 가장 왼쪽 Cell 의 좌표
		 * @param [in]	lCY 사각형 영역의 가장 위쪽 Cell 의 좌표
		 * @param [in]	lCW 사각형 영역의 Cell 단위 폭
		 * @param [in]	lCH 사각형 영역의 Cell 단위 높이
		 * @param [in]	lRotate 회전할 각(직각 이외의 각)
		 * @param [in]	dwAttr 적용할 Attribute
		 * @param [in]	mode Attribute 에 대해 처리할 type
		 */
		bool		ForAttrRegionFreeAngle( int32_t lMapIndex, int32_t lCX, int32_t lCY, int32_t lCW, int32_t lCH, int32_t lRotate, uint32_t dwAttr, EAttrRegionMode mode );

		/// 한 Cell 의 Attribute 에 대해 특정한 처리를 수행한다.
		/**
		 * @param [in]	lMapIndex 적용할 Map index
		 * @param [in]	lCX 적용할 Cell 의 X 좌표
		 * @param [in]	lCY 적용할 Cell 의 Y 좌표
		 * @param [in]	dwAttr 적용할 Attribute
		 * @param [in]	mode Attribute 에 대해 처리할 type
		 */
		bool		ForAttrRegionCell( int32_t lMapIndex, int32_t lCX, int32_t lCY, uint32_t dwAttr, EAttrRegionMode mode );

		static uint16_t			current_sectree_version;
		std::map<uint32_t, LPSECTREE_MAP>	m_map_pkSectree;
		std::map<int32_t, TAreaMap>	m_map_pkArea;
		std::vector<TMapRegion>		m_vec_mapRegion;
		std::map<uint32_t, std::vector<npc_info> > m_mapNPCPosition;

		// <Factor> Circular private map indexing
		typedef std::unordered_map<int32_t, int32_t> PrivateIndexMapType;
		PrivateIndexMapType next_private_index_map_;
};

#endif

