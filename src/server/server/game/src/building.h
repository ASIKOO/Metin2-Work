#ifndef __INC_METIN_II_BUILDING_H__
#define __INC_METIN_II_BUILDING_H__

#include "../../common/building.h"

namespace building
{
	class CLand;

	class CObject : public CEntity
	{
		public:
			CObject(TObject * pData, TObjectProto * pProto);
			virtual ~CObject();

			void	Destroy();

			virtual void EncodeInsertPacket(LPENTITY entity);
			virtual void EncodeRemovePacket(LPENTITY entity);

			uint32_t	GetID() { return m_data.dwID; }

			void	SetVID(uint32_t dwVID);
			uint32_t	GetVID() { return m_dwVID; }

			bool	Show(int32_t lMapIndex, int32_t x, int32_t y);

			void	Save();

			void	SetLand(CLand * pkLand) { m_pkLand = pkLand; }
			CLand *	GetLand()		{ return m_pkLand; }

			uint32_t	GetVnum()		{ return m_pProto ? m_pProto->dwVnum : 0; }
			uint32_t	GetGroup()		{ return m_pProto ? m_pProto->dwGroupVnum : 0; }

			void	RegenNPC();

			// BUILDING_NPC
			void	ApplySpecialEffect();
			void	RemoveSpecialEffect();

			void	Reconstruct(uint32_t dwVnum);

			LPCHARACTER GetNPC() { return m_chNPC; }
			// END_OF_BUILDING_NPC

		protected:
			TObjectProto *	m_pProto;
			TObject		m_data;
			uint32_t		m_dwVID;
			CLand *		m_pkLand;

			LPCHARACTER		m_chNPC;
	};

	class CLand
	{
		public:
			CLand(TLand * pData);
			~CLand();

			void	Destroy();

			const TLand & GetData();
			void	PutData(const TLand * data);

			uint32_t	GetID() const { return m_data.dwID; }
			void	SetOwner(uint32_t dwGID);
			uint32_t	GetOwner() const { return m_data.dwGuildID; }

			void	InsertObject(LPOBJECT pkObj);
			LPOBJECT	FindObject(uint32_t dwID);
			LPOBJECT	FindObjectByVID(uint32_t dwVID);
			LPOBJECT	FindObjectByVnum(uint32_t dwVnum);
			LPOBJECT	FindObjectByGroup(uint32_t dwGroupVnum);
			LPOBJECT	FindObjectByNPC(LPCHARACTER npc);
			void DeleteObject(uint32_t dwID);

			bool	RequestCreateObject(uint32_t dwVnum, int32_t lMapIndex, int32_t x, int32_t y, float xRot, float yRot, float zRot, bool checkAnother);
			void	RequestDeleteObject(uint32_t dwID);
			void	RequestDeleteObjectByVID(uint32_t dwVID);

			void	RequestUpdate(uint32_t dwGuild);

			// LAND_CLEAR
			void	ClearLand();
			// END_LAND_CLEAR

			// BUILD_WALL
			bool RequestCreateWall(int32_t nMapIndex, float rot);
			void RequestDeleteWall();

			bool RequestCreateWallBlocks(uint32_t dwVnum, int32_t nMapIndex, char wallSize, bool doorEast, bool doorWest, bool doorSouth, bool doorNorth);
			void RequestDeleteWallBlocks(uint32_t dwVnum);
			// END_BUILD_WALL

			uint32_t GetMapIndex() { return m_data.lMapIndex; }

		protected:
			TLand			m_data;
			std::map<uint32_t, LPOBJECT>	m_map_pkObject;
			std::map<uint32_t, LPOBJECT>	m_map_pkObjectByVID;

			// BUILD_WALL
		private :
			void DrawWall(uint32_t dwVnum, int32_t nMapIndex, int32_t& centerX, int32_t& centerY, char length, float zRot);
			// END_BUILD_WALL
	};

	class CManager : public singleton<CManager>
	{
		public:
			CManager();
			virtual ~CManager();

			void	Destroy();

			void	FinalizeBoot();

			bool	LoadObjectProto(const TObjectProto * pProto, int32_t size);
			TObjectProto * GetObjectProto(uint32_t dwVnum);

			bool	LoadLand(TLand * pTable);
			CLand *	FindLand(uint32_t dwID);
			CLand *	FindLand(int32_t lMapIndex, int32_t x, int32_t y);
			CLand *	FindLandByGuild(uint32_t GID);
			void	UpdateLand(TLand * pTable);

			bool	LoadObject(TObject * pTable, bool isBoot=false);
			void	DeleteObject(uint32_t dwID);
			void	UnregisterObject(LPOBJECT pkObj);

			LPOBJECT	FindObjectByVID(uint32_t dwVID);

			void	SendLandList(LPDESC d, int32_t lMapIndex);

			// LAND_CLEAR
			void	ClearLand(uint32_t dwLandID);
			void	ClearLandByGuildID(uint32_t dwGuildID);
			// END_LAND_CLEAR

		protected:
			std::vector<TObjectProto>		m_vec_kObjectProto;
			std::map<uint32_t, TObjectProto *>	m_map_pkObjectProto;

			std::map<uint32_t, CLand *>		m_map_pkLand;
			std::map<uint32_t, LPOBJECT>		m_map_pkObjByID;
			std::map<uint32_t, LPOBJECT>		m_map_pkObjByVID;
	};
}

#endif
