#ifndef __INC_ITEM_MANAGER__
#define __INC_ITEM_MANAGER__

#ifdef M2_USE_POOL
#include "pool.h"
#endif

// special_item_group.txt에서 정의하는 속성 그룹
// type attr로 선언할 수 있다.
// 이 속성 그룹을 이용할 수 있는 것은 special_item_group.txt에서 Special type으로 정의된 그룹에 속한 UNIQUE ITEM이다.
class CSpecialAttrGroup
{
public:
	CSpecialAttrGroup(uint32_t vnum)
		: m_dwVnum(vnum)
	{}
	struct CSpecialAttrInfo
	{
		CSpecialAttrInfo (uint32_t _apply_type, uint32_t _apply_value)
			: apply_type(_apply_type), apply_value(_apply_value)
		{}
		uint32_t apply_type;
		uint32_t apply_value;

	};
	uint32_t m_dwVnum;
	std::string	m_stEffectFileName;
	std::vector<CSpecialAttrInfo> m_vecAttrs;
};

class CSpecialItemGroup
{
	public:
		enum EGiveType
		{
			NONE,
			GOLD,
			EXP,
			MOB,
			SLOW,
			DRAIN_HP,
			POISON,
			MOB_GROUP,
		};

		// QUEST 타입은 퀘스트 스크립트에서 vnum.sig_use를 사용할 수 있는 그룹이다.
		//		단, 이 그룹에 들어가기 위해서는 ITEM 자체의 TYPE이 QUEST여야 한다.
		// SPECIAL 타입은 idx, item_vnum, attr_vnum을 입력한다. attr_vnum은 위에 CSpecialAttrGroup의 Vnum이다.
		//		이 그룹에 들어있는 아이템은 같이 착용할 수 없다.
		enum ESIGType { NORMAL, PCT, QUEST, SPECIAL };

		struct CSpecialItemInfo
		{
			uint32_t vnum;
			int32_t count;
			int32_t rare;

			CSpecialItemInfo(uint32_t _vnum, int32_t _count, int32_t _rare)
				: vnum(_vnum), count(_count), rare(_rare)
				{}
		};

		CSpecialItemGroup(uint32_t vnum, uint8_t type=0)
			: m_dwVnum(vnum), m_bType(type)
			{}

		void AddItem(uint32_t vnum, int32_t count, int32_t prob, int32_t rare)
		{
			if (!prob)
				return;
			if (!m_vecProbs.empty())
				prob += m_vecProbs.back();
			m_vecProbs.push_back(prob);
			m_vecItems.push_back(CSpecialItemInfo(vnum, count, rare));
		}

		bool IsEmpty() const
		{
			return m_vecProbs.empty();
		}

		// Type Multi, 즉 m_bType == PCT 인 경우,
		// 확률을 더해가지 않고, 독립적으로 계산하여 아이템을 생성한다.
		// 따라서 여러 개의 아이템이 생성될 수 있다.
		// by rtsummit
		int32_t GetMultiIndex(std::vector <int32_t> &idx_vec) const
		{
			idx_vec.clear();
			if (m_bType == PCT)
			{
				int32_t count = 0;
				if (number(1,100) <= m_vecProbs[0])
				{
					idx_vec.push_back(0);
					count++;
				}
				for (uint32_t i = 1; i < m_vecProbs.size(); i++)
				{
					if (number(1,100) <= m_vecProbs[i] - m_vecProbs[i-1])
					{
						idx_vec.push_back(i);
						count++;
					}
				}
				return count;
			}
			else
			{
				idx_vec.push_back(GetOneIndex());
				return 1;
			}
		}

		int32_t GetOneIndex() const
		{
			int32_t n = number(1, m_vecProbs.back());
			itertype(m_vecProbs) it = lower_bound(m_vecProbs.begin(), m_vecProbs.end(), n);
			return std::distance(m_vecProbs.begin(), it);
		}

		int32_t GetVnum(int32_t idx) const
		{
			return m_vecItems[idx].vnum;
		}

		int32_t GetCount(int32_t idx) const
		{
			return m_vecItems[idx].count;
		}

		int32_t GetRarePct(int32_t idx) const
		{
			return m_vecItems[idx].rare;
		}

		bool Contains(uint32_t dwVnum) const
		{
			for (uint32_t i = 0; i < m_vecItems.size(); i++)
			{
				if (m_vecItems[i].vnum == dwVnum)
					return true;
			}
			return false;
		}
		
		// Group의 Type이 Special인 경우에
		// dwVnum에 매칭되는 AttrVnum을 return해준다.
		uint32_t GetAttrVnum(uint32_t dwVnum) const
		{
			if (CSpecialItemGroup::SPECIAL != m_bType)
				return 0;
			for (itertype(m_vecItems) it = m_vecItems.begin(); it != m_vecItems.end(); it++)
			{
				if (it->vnum == dwVnum)
				{
					return it->count;
				}
			}
			return 0;
		}

		// Group의 Size를 return해준다.
		int32_t GetGroupSize() const
		{
			return m_vecProbs.size();
		}

		uint32_t m_dwVnum;
		uint8_t	m_bType;
		std::vector<int32_t> m_vecProbs;
		std::vector<CSpecialItemInfo> m_vecItems; // vnum, count
};

class CMobItemGroup
{
	public:
		struct SMobItemGroupInfo
		{
			uint32_t dwItemVnum;
			int32_t iCount;
			int32_t iRarePct;

			SMobItemGroupInfo(uint32_t dwItemVnum, int32_t iCount, int32_t iRarePct)
				: dwItemVnum(dwItemVnum),
			iCount(iCount),
			iRarePct(iRarePct)
			{
			}
		};

		CMobItemGroup(uint32_t dwMobVnum, int32_t iKillDrop, const std::string& r_stName)
			:
			m_dwMobVnum(dwMobVnum),
		m_iKillDrop(iKillDrop),
		m_stName(r_stName)
		{
		}

		int32_t GetKillPerDrop() const
		{
			return m_iKillDrop;
		}

		void AddItem(uint32_t dwItemVnum, int32_t iCount, int32_t iPartPct, int32_t iRarePct)
		{
			if (!m_vecProbs.empty())
				iPartPct += m_vecProbs.back();
			m_vecProbs.push_back(iPartPct);
			m_vecItems.push_back(SMobItemGroupInfo(dwItemVnum, iCount, iRarePct));
		}

		// MOB_DROP_ITEM_BUG_FIX
		bool IsEmpty() const
		{
			return m_vecProbs.empty();
		}

		int32_t GetOneIndex() const
		{
			int32_t n = number(1, m_vecProbs.back());
			itertype(m_vecProbs) it = lower_bound(m_vecProbs.begin(), m_vecProbs.end(), n);
			return std::distance(m_vecProbs.begin(), it);
		}
		// END_OF_MOB_DROP_ITEM_BUG_FIX

		const SMobItemGroupInfo& GetOne() const
		{
			return m_vecItems[GetOneIndex()];
		}

	private:
		uint32_t m_dwMobVnum;
		int32_t m_iKillDrop;
		std::string m_stName;
		std::vector<int32_t> m_vecProbs;
		std::vector<SMobItemGroupInfo> m_vecItems;
};

class CDropItemGroup
{
	struct SDropItemGroupInfo
	{
		uint32_t	dwVnum;
		uint32_t	dwPct;
		int32_t	iCount;

		SDropItemGroupInfo(uint32_t dwVnum, uint32_t dwPct, int32_t iCount)
			: dwVnum(dwVnum), dwPct(dwPct), iCount(iCount)
			{}
	};

	public:
	CDropItemGroup(uint32_t dwVnum, uint32_t dwMobVnum, const std::string& r_stName)
		:
		m_dwVnum(dwVnum),
	m_dwMobVnum(dwMobVnum),
	m_stName(r_stName)
	{
	}

	const std::vector<SDropItemGroupInfo> & GetVector()
	{
		return m_vec_items;
	}

	void AddItem(uint32_t dwItemVnum, uint32_t dwPct, int32_t iCount)
	{
		m_vec_items.push_back(SDropItemGroupInfo(dwItemVnum, dwPct, iCount));
	}

	private:
	uint32_t m_dwVnum;
	uint32_t m_dwMobVnum;
	std::string m_stName;
	std::vector<SDropItemGroupInfo> m_vec_items;
};

class CLevelItemGroup
{
	struct SLevelItemGroupInfo
	{
		uint32_t dwVNum;
		uint32_t dwPct;
		int32_t iCount;

		SLevelItemGroupInfo(uint32_t dwVnum, uint32_t dwPct, int32_t iCount)
			: dwVNum(dwVnum), dwPct(dwPct), iCount(iCount)
		{ }
	};

	private :
		uint32_t m_dwLevelLimit;
		std::string m_stName;
		std::vector<SLevelItemGroupInfo> m_vec_items;

	public :
		CLevelItemGroup(uint32_t dwLevelLimit)
			: m_dwLevelLimit(dwLevelLimit)
		{}

		uint32_t GetLevelLimit() { return m_dwLevelLimit; }

		void AddItem(uint32_t dwItemVnum, uint32_t dwPct, int32_t iCount)
		{
			m_vec_items.push_back(SLevelItemGroupInfo(dwItemVnum, dwPct, iCount));
		}

		const std::vector<SLevelItemGroupInfo> & GetVector()
		{
			return m_vec_items;
		}
};

class CBuyerThiefGlovesItemGroup
{
	struct SThiefGroupInfo
	{
		uint32_t	dwVnum;
		uint32_t	dwPct;
		int32_t	iCount;

		SThiefGroupInfo(uint32_t dwVnum, uint32_t dwPct, int32_t iCount)
			: dwVnum(dwVnum), dwPct(dwPct), iCount(iCount)
			{}
	};

	public:
	CBuyerThiefGlovesItemGroup(uint32_t dwVnum, uint32_t dwMobVnum, const std::string& r_stName)
		:
		m_dwVnum(dwVnum),
	m_dwMobVnum(dwMobVnum),
	m_stName(r_stName)
	{
	}

	const std::vector<SThiefGroupInfo> & GetVector()
	{
		return m_vec_items;
	}

	void AddItem(uint32_t dwItemVnum, uint32_t dwPct, int32_t iCount)
	{
		m_vec_items.push_back(SThiefGroupInfo(dwItemVnum, dwPct, iCount));
	}

	private:
	uint32_t m_dwVnum;
	uint32_t m_dwMobVnum;
	std::string m_stName;
	std::vector<SThiefGroupInfo> m_vec_items;
};

class ITEM;

class ITEM_MANAGER : public singleton<ITEM_MANAGER>
{
	public:
		ITEM_MANAGER();
		virtual ~ITEM_MANAGER();

		bool                    Initialize(TItemTable * table, int32_t size);
		void			Destroy();
		void			Update();	// 매 루프마다 부른다.
		void			GracefulShutdown();

		uint32_t			GetNewID();
		bool			SetMaxItemID(TItemIDRangeTable range); // 최대 고유 아이디를 지정
		bool			SetMaxSpareItemID(TItemIDRangeTable range);

		// DelayedSave: 어떠한 루틴 내에서 저장을 해야 할 짓을 많이 하면 저장
		// 쿼리가 너무 많아지므로 "저장을 한다" 라고 표시만 해두고 잠깐
		// (예: 1 frame) 후에 저장시킨다.
		void			DelayedSave(LPITEM item);
		void			FlushDelayedSave(LPITEM item); // Delayed 리스트에 있다면 지우고 저장한다. 끊김 처리시 사용 됨.
		void			SaveSingleItem(LPITEM item);

		LPITEM                  CreateItem(uint32_t vnum, uint32_t count = 1, uint32_t dwID = 0, bool bTryMagic = false, int32_t iRarePct = -1, bool bSkipSave = false);
#ifndef DEBUG_ALLOC
		void DestroyItem(LPITEM item);
#else
		void DestroyItem(LPITEM item, const char* file, uint32_t line);
#endif
		void			RemoveItem(LPITEM item, const char * c_pszReason=NULL); // 사용자로 부터 아이템을 제거

		LPITEM			Find(uint32_t id);
		LPITEM                  FindByVID(uint32_t vid);
		TItemTable *            GetTable(uint32_t vnum);
		bool			GetVnum(const char * c_pszName, uint32_t & r_dwVnum);
		bool			GetVnumByOriginalName(const char * c_pszName, uint32_t & r_dwVnum);

		bool			GetDropPct(LPCHARACTER pkChr, LPCHARACTER pkKiller, OUT int32_t& iDeltaPercent, OUT int32_t& iRandRange);
		bool			CreateDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM> & vec_item);

		bool			ReadCommonDropItemFile(const char * c_pszFileName);
		bool			ReadEtcDropItemFile(const char * c_pszFileName);
		bool			ReadDropItemGroup(const char * c_pszFileName);
		bool			ReadMonsterDropItemGroup(const char * c_pszFileName);
		bool			ReadSpecialDropItemFile(const char * c_pszFileName);
		
		// convert name -> vnum special_item_group.txt
		bool			ConvSpecialDropItemFile();
		// convert name -> vnum special_item_group.txt

		uint32_t			GetRefineFromVnum(uint32_t dwVnum);

		static void		CopyAllAttrTo(LPITEM pkOldItem, LPITEM pkNewItem);		// pkNewItem으로 모든 속성과 소켓 값들을 목사하는 함수.


		const CSpecialItemGroup* GetSpecialItemGroup(uint32_t dwVnum);
		const CSpecialAttrGroup* GetSpecialAttrGroup(uint32_t dwVnum);

		const std::vector<TItemTable> & GetTable() { return m_vec_prototype; }

		// CHECK_UNIQUE_GROUP
		int32_t			GetSpecialGroupFromItem(uint32_t dwVnum) const { itertype(m_ItemToSpecialGroup) it = m_ItemToSpecialGroup.find(dwVnum); return (it == m_ItemToSpecialGroup.end()) ? 0 : it->second; }
		// END_OF_CHECK_UNIQUE_GROUP

	protected:
		int32_t                     RealNumber(uint32_t vnum);
		void			CreateQuestDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM> & vec_item, int32_t iDeltaPercent, int32_t iRandRange);

	protected:
		typedef std::map<uint32_t, LPITEM> ITEM_VID_MAP;		

		std::vector<TItemTable>		m_vec_prototype;
		std::vector<TItemTable*> m_vec_item_vnum_range_info;
		std::map<uint32_t, uint32_t>		m_map_ItemRefineFrom;
		int32_t				m_iTopOfTable;

		ITEM_VID_MAP			m_VIDMap;			///< m_dwVIDCount 의 값단위로 아이템을 저장한다.
		uint32_t				m_dwVIDCount;			///< 이녀석 VID가 아니라 그냥 프로세스 단위 유니크 번호다.
		uint32_t				m_dwCurrentID;
		TItemIDRangeTable	m_ItemIDRange;
		TItemIDRangeTable	m_ItemIDSpareRange;

		std::unordered_set<LPITEM> m_set_pkItemForDelayedSave;
		std::map<uint32_t, LPITEM>		m_map_pkItemByID;
		std::map<uint32_t, uint32_t>		m_map_dwEtcItemDropProb;
		std::map<uint32_t, CDropItemGroup*> m_map_pkDropItemGroup;
		std::map<uint32_t, CSpecialItemGroup*> m_map_pkSpecialItemGroup;
		std::map<uint32_t, CSpecialItemGroup*> m_map_pkQuestItemGroup;
		std::map<uint32_t, CSpecialAttrGroup*> m_map_pkSpecialAttrGroup;
		std::map<uint32_t, CMobItemGroup*> m_map_pkMobItemGroup;
		std::map<uint32_t, CLevelItemGroup*> m_map_pkLevelItemGroup;
		std::map<uint32_t, CBuyerThiefGlovesItemGroup*> m_map_pkGloveItemGroup;

		// CHECK_UNIQUE_GROUP
		std::map<uint32_t, int32_t>		m_ItemToSpecialGroup;
		// END_OF_CHECK_UNIQUE_GROUP
	
	private:
		// 독일에서 기존 캐시 아이템과 같지만, 교환 가능한 캐시 아이템을 만든다고 하여,
		// 오리지널 아이템에 교환 금지 플래그만 삭제한 새로운 아이템들을 만들어,
		// 새로운 아이템 대역을 할당하였다.
		// 문제는 새로운 아이템도 오리지널 아이템과 같은 효과를 내야하는데,
		// 서버건, 클라건, vnum 기반으로 되어있어
		// 새로운 vnum을 죄다 서버에 새로 다 박아야하는 안타까운 상황에 맞닿았다.
		// 그래서 새 vnum의 아이템이면, 서버에서 돌아갈 때는 오리지널 아이템 vnum으로 바꿔서 돌고 하고,
		// 저장할 때에 본래 vnum으로 바꿔주도록 한다.
		// 이를 위해 오리지널 vnum과 새로운 vnum을 연결시켜주는 맵을 만듦.
		typedef std::map <uint32_t, uint32_t> TMapDW2DW;
		TMapDW2DW	m_map_new_to_ori;

	public:	
		uint32_t	GetMaskVnum(uint32_t dwVnum);
		std::map<uint32_t, TItemTable>  m_map_vid;
		std::map<uint32_t, TItemTable>&  GetVIDMap() { return m_map_vid; }
		std::vector<TItemTable>& GetVecProto() { return m_vec_prototype; }	
		
		const static int32_t MAX_NORM_ATTR_NUM = 5;
		const static int32_t MAX_RARE_ATTR_NUM = 2;
		bool ReadItemVnumMaskTable(const char * c_pszFileName);
	private:
#ifdef M2_USE_POOL
		ObjectPool<CItem> pool_;
#endif
};

#ifndef DEBUG_ALLOC
#define M2_DESTROY_ITEM(ptr) ITEM_MANAGER::instance().DestroyItem(ptr)
#else
#define M2_DESTROY_ITEM(ptr) ITEM_MANAGER::instance().DestroyItem(ptr, __FILE__, __LINE__)
#endif

#endif
