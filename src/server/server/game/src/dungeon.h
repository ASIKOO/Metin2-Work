#ifndef __INC_METIN_II_GAME_DUNGEON_H
#define __INC_METIN_II_GAME_DUNGEON_H

#include "sectree_manager.h"

class CParty;

class CDungeon
{
	typedef std::unordered_map<LPPARTY, int32_t> TPartyMap;
	typedef std::map<std::string, LPCHARACTER> TUniqueMobMap;

	public:
	// <Factor> Non-persistent identifier type
	typedef uint32_t IdType;

	~CDungeon();

	// <Factor>
	IdType GetId() const { return m_id; }

	// DUNGEON_NOTICE
	void	Notice(const char* msg);
	// END_OF_DUNGEON_NOTICE

	void	JoinParty(LPPARTY pParty);
	void	QuitParty(LPPARTY pParty);

	void	Join(LPCHARACTER ch);

	void	IncMember(LPCHARACTER ch);
	void	DecMember(LPCHARACTER ch);

	// DUNGEON_KILL_ALL_BUG_FIX
	void	Purge();
	void	KillAll();
	// END_OF_DUNGEON_KILL_ALL_BUG_FIX

	void	IncMonster() { m_iMonsterCount++; sys_log(0, "MonsterCount %d", m_iMonsterCount); }
	void	DecMonster() { m_iMonsterCount--; CheckEliminated(); }
	int32_t	CountMonster() { return m_iMonsterCount; }	// 데이터로 리젠한 몬스터의 수
	int32_t	CountRealMonster();				// 실제로 맵상에 있는 몬스터

	void	IncPartyMember(LPPARTY pParty, LPCHARACTER ch);
	void	DecPartyMember(LPPARTY pParty, LPCHARACTER ch);

	void	IncKillCount(LPCHARACTER pkKiller, LPCHARACTER pkVictim);
	int32_t	GetKillMobCount();
	int32_t	GetKillStoneCount();
	bool	IsUsePotion();
	bool	IsUseRevive();
	void	UsePotion(LPCHARACTER ch);
	void	UseRevive(LPCHARACTER ch);

	int32_t	GetMapIndex() { return m_lMapIndex; }

	void	Spawn(uint32_t vnum, const char* pos);
	LPCHARACTER	SpawnMob(uint32_t vnum, int32_t x, int32_t y, int32_t dir = 0);
	LPCHARACTER	SpawnMob_ac_dir(uint32_t vnum, int32_t x, int32_t y, int32_t dir = 0);
	LPCHARACTER	SpawnGroup(uint32_t vnum, int32_t x, int32_t y, float radius, bool bAggressive=false, int32_t count=1);

	void	SpawnNameMob(uint32_t vnum, int32_t x, int32_t y, const char* name);
	void	SpawnGotoMob(int32_t lFromX, int32_t lFromY, int32_t lToX, int32_t lToY);

	void	SpawnRegen(const char* filename, bool bOnce = true);
	void	AddRegen(LPREGEN regen);
	void	ClearRegen();
	bool	IsValidRegen(LPREGEN regen, uint32_t regen_id);

	void	SetUnique(const char* key, uint32_t vid);
	void	SpawnMoveUnique(const char* key, uint32_t vnum, const char* pos_from, const char* pos_to);
	void	SpawnMoveGroup(uint32_t vnum, const char* pos_from, const char* pos_to, int32_t count=1);
	void	SpawnUnique(const char* key, uint32_t vnum, const char* pos);
	void	SpawnStoneDoor(const char* key, const char* pos);
	void	SpawnWoodenDoor(const char* key, const char* pos);
	void	KillUnique(const std::string& key);
	void	PurgeUnique(const std::string& key);
	bool	IsUniqueDead(const std::string& key);
	float	GetUniqueHpPerc(const std::string& key);
	uint32_t	GetUniqueVid(const std::string& key);

	void	DeadCharacter(LPCHARACTER ch);

	void	UniqueSetMaxHP(const std::string& key, int32_t iMaxHP);
	void	UniqueSetHP(const std::string& key, int32_t iHP);
	void	UniqueSetDefGrade(const std::string& key, int32_t iGrade);

	void	SendDestPositionToParty(LPPARTY pParty, int32_t x, int32_t y);

	void	CheckEliminated();

	void	JumpAll(int32_t lFromMapIndex, int32_t x, int32_t y);
	void	WarpAll(int32_t lFromMapIndex, int32_t x, int32_t y);
	void	JumpParty(LPPARTY pParty, int32_t lFromMapIndex, int32_t x, int32_t y);

	void	ExitAll();
	void	ExitAllToStartPosition();
	void	JumpToEliminateLocation();
	void	SetExitAllAtEliminate(int32_t time);
	void	SetWarpAtEliminate(int32_t time, int32_t lMapIndex, int32_t x, int32_t y, const char* regen_file);

	int32_t	GetFlag(std::string name);
	void	SetFlag(std::string name, int32_t value);
	void	SetWarpLocation (int32_t map_index, int32_t x, int32_t y);

	// item group은 item_vnum과 item_count로 구성.
	typedef std::vector <std::pair <uint32_t, int32_t> > ItemGroup;
	void	CreateItemGroup (std::string& group_name, ItemGroup& item_group);
	const ItemGroup* GetItemGroup (std::string& group_name);
	//void	InsertItemGroup (std::string& group_name, uint32_t item_vnum);

	template <class Func> Func ForEachMember(Func f);

	bool IsAllPCNearTo( int32_t x, int32_t y, int32_t dist );

	protected:
	CDungeon(IdType id, int32_t lOriginalMapIndex, int32_t lMapIndex);

	void	Initialize();
	void	CheckDestroy();

	private:
	IdType 		m_id; // <Factor>
	uint32_t		m_lOrigMapIndex;
	uint32_t		m_lMapIndex;

	CHARACTER_SET	    m_set_pkCharacter;
	std::map<std::string, int32_t>  m_map_Flag;
	typedef std::map<std::string, ItemGroup> ItemGroupMap;
	ItemGroupMap m_map_ItemGroup;
	TPartyMap	m_map_pkParty;
	TAreaMap&	m_map_Area;
	TUniqueMobMap	m_map_UniqueMob;

	int32_t		m_iMobKill;
	int32_t		m_iStoneKill;
	bool		m_bUsePotion;
	bool		m_bUseRevive;

	int32_t		m_iMonsterCount;

	bool		m_bExitAllAtEliminate;
	bool		m_bWarpAtEliminate;

	// 적 전멸시 워프하는 위치
	int32_t		m_iWarpDelay;
	int32_t		m_lWarpMapIndex;
	int32_t		m_lWarpX;
	int32_t		m_lWarpY;
	std::string	m_stRegenFile;

	std::vector<LPREGEN> m_regen;

	LPEVENT		deadEvent;
	// <Factor>
	LPEVENT exit_all_event_;
	LPEVENT jump_to_event_;
	uint32_t regen_id_;

	friend class CDungeonManager;
	friend EVENTFUNC(dungeon_dead_event);
	// <Factor>
	friend EVENTFUNC(dungeon_exit_all_event);
	friend EVENTFUNC(dungeon_jump_to_event);

	// 파티 단위 던전 입장을 위한 임시 변수.
	// m_map_pkParty는 관리가 부실하여 사용할 수 없다고 판단하여,
	// 임시로 한 파티에 대한 관리를 하는 변수 생성.
	
	LPPARTY m_pParty;
	public :
	void SetPartyNull();
};

class CDungeonManager : public singleton<CDungeonManager>
{
	typedef std::map<CDungeon::IdType, LPDUNGEON> TDungeonMap;
	typedef std::map<int32_t, LPDUNGEON> TMapDungeon;

	public:
	CDungeonManager();
	virtual ~CDungeonManager();

	LPDUNGEON	Create(int32_t lOriginalMapIndex);
	void		Destroy(CDungeon::IdType dungeon_id);
	LPDUNGEON	Find(CDungeon::IdType dungeon_id);
	LPDUNGEON	FindByMapIndex(int32_t lMapIndex);

	private:
	TDungeonMap	m_map_pkDungeon;
	TMapDungeon m_map_pkMapDungeon;

	// <Factor> Introduced uint32_t 32-bit dungeon identifier
	CDungeon::IdType next_id_;
};

#endif
