class CItemDropInfo
{
public:
	CItemDropInfo(int32_t iLevelStart, int32_t iLevelEnd, int32_t iPercent, uint32_t dwVnum) :
	  m_iLevelStart(iLevelStart), m_iLevelEnd(iLevelEnd), m_iPercent(iPercent), m_dwVnum(dwVnum)
	  {
	  }

	  int32_t	m_iLevelStart;
	  int32_t	m_iLevelEnd;
	  int32_t	m_iPercent; // 1 ~ 1000
	  uint32_t	m_dwVnum;

	  friend bool operator < (const CItemDropInfo & l, const CItemDropInfo & r)
	  {
		  return l.m_iLevelEnd < r.m_iLevelEnd;
	  }
};

extern std::vector<CItemDropInfo> g_vec_pkCommonDropItem[MOB_RANK_MAX_NUM];

typedef struct SDropItem
{
	int32_t		iLvStart;
	int32_t		iLvEnd;
	float	fPercent;
	char	szItemName[ITEM_NAME_MAX_LEN + 1];
	int32_t		iCount;
} TDropItem;

