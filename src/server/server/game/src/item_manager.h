#ifndef __INC_ITEM_MANAGER__
#define __INC_ITEM_MANAGER__

#ifdef M2_USE_POOL
#include "pool.h"
#endif

// special_item_group.txt���� �����ϴ� �Ӽ� �׷�
// type attr�� ������ �� �ִ�.
// �� �Ӽ� �׷��� �̿��� �� �ִ� ���� special_item_group.txt���� Special type���� ���ǵ� �׷쿡 ���� UNIQUE ITEM�̴�.
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

		// QUEST Ÿ���� ����Ʈ ��ũ��Ʈ���� vnum.sig_use�� ����� �� �ִ� �׷��̴�.
		//		��, �� �׷쿡 ���� ���ؼ��� ITEM ��ü�� TYPE�� QUEST���� �Ѵ�.
		// SPECIAL Ÿ���� idx, item_vnum, attr_vnum�� �Է��Ѵ�. attr_vnum�� ���� CSpecialAttrGroup�� Vnum�̴�.
		//		�� �׷쿡 ����ִ� �������� ���� ������ �� ����.
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

		// Type Multi, �� m_bType == PCT �� ���,
		// Ȯ���� ���ذ��� �ʰ�, ���������� ����Ͽ� �������� �����Ѵ�.
		// ���� ���� ���� �������� ������ �� �ִ�.
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
		
		// Group�� Type�� Special�� ��쿡
		// dwVnum�� ��Ī�Ǵ� AttrVnum�� return���ش�.
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

		// Group�� Size�� return���ش�.
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
		void			Update();	// �� �������� �θ���.
		void			GracefulShutdown();

		uint32_t			GetNewID();
		bool			SetMaxItemID(TItemIDRangeTable range); // �ִ� ���� ���̵� ����
		bool			SetMaxSpareItemID(TItemIDRangeTable range);

		// DelayedSave: ��� ��ƾ ������ ������ �ؾ� �� ���� ���� �ϸ� ����
		// ������ �ʹ� �������Ƿ� "������ �Ѵ�" ��� ǥ�ø� �صΰ� ���
		// (��: 1 frame) �Ŀ� �����Ų��.
		void			DelayedSave(LPITEM item);
		void			FlushDelayedSave(LPITEM item); // Delayed ����Ʈ�� �ִٸ� ����� �����Ѵ�. ���� ó���� ��� ��.
		void			SaveSingleItem(LPITEM item);

		LPITEM                  CreateItem(uint32_t vnum, uint32_t count = 1, uint32_t dwID = 0, bool bTryMagic = false, int32_t iRarePct = -1, bool bSkipSave = false);
#ifndef DEBUG_ALLOC
		void DestroyItem(LPITEM item);
#else
		void DestroyItem(LPITEM item, const char* file, uint32_t line);
#endif
		void			RemoveItem(LPITEM item, const char * c_pszReason=NULL); // ����ڷ� ���� �������� ����

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

		static void		CopyAllAttrTo(LPITEM pkOldItem, LPITEM pkNewItem);		// pkNewItem���� ��� �Ӽ��� ���� ������ ����ϴ� �Լ�.


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

		ITEM_VID_MAP			m_VIDMap;			///< m_dwVIDCount �� �������� �������� �����Ѵ�.
		uint32_t				m_dwVIDCount;			///< �̳༮ VID�� �ƴ϶� �׳� ���μ��� ���� ����ũ ��ȣ��.
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
		// ���Ͽ��� ���� ĳ�� �����۰� ������, ��ȯ ������ ĳ�� �������� ����ٰ� �Ͽ�,
		// �������� �����ۿ� ��ȯ ���� �÷��׸� ������ ���ο� �����۵��� �����,
		// ���ο� ������ �뿪�� �Ҵ��Ͽ���.
		// ������ ���ο� �����۵� �������� �����۰� ���� ȿ���� �����ϴµ�,
		// ������, Ŭ���, vnum ������� �Ǿ��־�
		// ���ο� vnum�� �˴� ������ ���� �� �ھƾ��ϴ� ��Ÿ��� ��Ȳ�� �´�Ҵ�.
		// �׷��� �� vnum�� �������̸�, �������� ���ư� ���� �������� ������ vnum���� �ٲ㼭 ���� �ϰ�,
		// ������ ���� ���� vnum���� �ٲ��ֵ��� �Ѵ�.
		// �̸� ���� �������� vnum�� ���ο� vnum�� ��������ִ� ���� ����.
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
