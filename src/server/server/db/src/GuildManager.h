// vim:ts=8 sw=4
#ifndef __INC_GUILD_MANAGER_H
#define __INC_GUILD_MANAGER_H

#include "Peer.h"
#include <queue>
#include <utility>
#include "../../libsql/libsql.h"
#include "../../libpoly/Poly.h"

enum
{
    GUILD_WARP_WAR_CHANNEL = 99
};

class CGuildWarReserve;

struct TGuildDeclareInfo
{
	uint8_t bType;
	uint32_t dwGuildID[2];

	TGuildDeclareInfo(uint8_t _bType, uint32_t _dwGuildID1, uint32_t _dwGuildID2)
		: bType(_bType)
	{
		dwGuildID[0] = _dwGuildID1;
		dwGuildID[1] = _dwGuildID2;
	}

	bool operator < (const TGuildDeclareInfo& r) const
	{
		return dwGuildID[0] < r.dwGuildID[0] || dwGuildID[0] == r.dwGuildID[0] && dwGuildID[1] < r.dwGuildID[1];
	}

	TGuildDeclareInfo& operator = (const TGuildDeclareInfo& r)
	{
		bType = r.bType;
		dwGuildID[0] = r.dwGuildID[0];
		dwGuildID[1] = r.dwGuildID[1];
		return *this;
	}
};

struct TGuildWaitStartInfo
{
	uint8_t			bType;
	uint32_t			GID[2];
	int32_t			lWarPrice;
	int32_t			lInitialScore;
	CGuildWarReserve *	pkReserve;

	TGuildWaitStartInfo(uint8_t _bType,
			uint32_t _g1,
			uint32_t _g2,
			int32_t _lWarPrice,
			int32_t _lInitialScore,
			CGuildWarReserve * _pkReserve)
		: bType(_bType), lWarPrice(_lWarPrice), lInitialScore(_lInitialScore), pkReserve(_pkReserve)
	{
		GID[0] = _g1;
		GID[1] = _g2;
	}

	bool operator < (const TGuildWaitStartInfo& r) const
	{
		return GID[0] < r.GID[0] || GID[0] == r.GID[0] && GID[1] < r.GID[1];
	}
};

struct TGuildWarPQElement
{
	bool	bEnd;
	uint8_t	bType;
	uint32_t	GID[2];
	uint32_t	iScore[2];
	uint32_t	iBetScore[2];

	TGuildWarPQElement(uint8_t _bType, uint32_t GID1, uint32_t GID2) : bEnd(false), bType(_bType)
	{
		bType = _bType;
		GID[0] = GID1;
		GID[1] = GID2;
		iScore[0] = iScore[1] = 0;
		iBetScore[0] = iBetScore[1] = 0;
	}
};

struct TGuildSkillUsed
{
    uint32_t GID;
    uint32_t dwSkillVnum;

    // GUILD_SKILL_COOLTIME_BUG_FIX
    TGuildSkillUsed(uint32_t _GID, uint32_t _dwSkillVnum) : GID(_GID), dwSkillVnum(_dwSkillVnum)
    {
    }
    // END_OF_GUILD_SKILL_COOLTIME_BUG_FIX
};

inline bool operator < (const TGuildSkillUsed& a, const TGuildSkillUsed& b)
{
    return a.GID < b.GID || a.GID == b.GID && a.dwSkillVnum < b.dwSkillVnum;
}

typedef struct SGuild
{
	SGuild() : ladder_point(0), win(0), draw(0), loss(0), gold(0), level(0)
	{
		memset(szName, 0, sizeof(szName));
	}

	char szName[GUILD_NAME_MAX_LEN+1];
	int32_t	ladder_point;
	int32_t	win;
	int32_t	draw;
	int32_t	loss;
	int32_t	gold;
	int32_t	level;
} TGuild;

typedef struct SGuildWarInfo
{
    int32_t		tEndTime;
    TGuildWarPQElement * pElement;
    CGuildWarReserve * pkReserve;

    SGuildWarInfo() : pElement(NULL)
    {
    }
} TGuildWarInfo;

class CGuildWarReserve
{
    public:
	CGuildWarReserve(const TGuildWarReserve& rTable);

	void Initialize();

	TGuildWarReserve & GetDataRef()
	{
	    return m_data;
	}

	void	OnSetup(CPeer * peer);
	bool	Bet(const char * pszLogin, uint32_t dwGold, uint32_t dwGuild);
	void	Draw();
	void	End(int32_t iScoreFrom, int32_t iScoreTo);

	int32_t	GetLastNoticeMin() { return m_iLastNoticeMin; }
	void	SetLastNoticeMin(int32_t iMin) { m_iLastNoticeMin = iMin; }

    private:
	CGuildWarReserve();  // 기본 생성자를 사용하지 못하도록 의도적으로 구현하지 않음

	TGuildWarReserve				m_data;
	// <login, <guild, gold>>
	std::map<std::string, std::pair<uint32_t, uint32_t> > mapBet;
	int32_t						m_iLastNoticeMin;
};

class CGuildManager : public singleton<CGuildManager>
{
    public:
	CGuildManager();
	virtual ~CGuildManager();

	void	Initialize();

	void	Load(uint32_t dwGuildID);

	TGuild & TouchGuild(uint32_t GID);

	void	Update();

	void	OnSetup(CPeer * peer);
	void	StartWar(uint8_t bType, uint32_t GID1, uint32_t GID2, CGuildWarReserve * pkReserve = NULL);

	void	UpdateScore(uint32_t guild_gain_point, uint32_t guild_opponent, int32_t iScore, int32_t iBetScore);

	void	AddDeclare(uint8_t bType, uint32_t guild_from, uint32_t guild_to);
	void	RemoveDeclare(uint32_t guild_from, uint32_t guild_to);

	bool	TakeBetPrice(uint32_t dwGuildTo, uint32_t dwGuildFrom, int32_t lWarPrice);

	bool	WaitStart(TPacketGuildWar * p);

	void	RecvWarEnd(uint32_t GID1, uint32_t GID2);
	void	RecvWarOver(uint32_t dwGuildWinner, uint32_t dwGuildLoser, bool bDraw, int32_t lWarPrice);

	void	ChangeLadderPoint(uint32_t GID, int32_t change);

	void	UseSkill(uint32_t dwGuild, uint32_t dwSkillVnum, uint32_t dwCooltime);

	int32_t		GetGuildGold(uint32_t dwGuild);
	void	DepositMoney(uint32_t dwGuild, int32_t lGold);
	void	WithdrawMoney(CPeer* peer, uint32_t dwGuild, int32_t lGold);
	void	WithdrawMoneyReply(uint32_t dwGuild, uint8_t bGiveSuccess, int32_t lGold);

	void	MoneyChange(uint32_t dwGuild, uint32_t dwGold);

	void	QueryRanking();
	void	ResultRanking(MYSQL_RES * pRes);
	int32_t	GetRanking(uint32_t dwGID);

	//
	// Reserve War
	//
	void	BootReserveWar();
	bool	ReserveWar(TPacketGuildWar * p);
	void	ProcessReserveWar();
	bool	Bet(uint32_t dwID, const char * c_pszLogin, uint32_t dwGold, uint32_t dwGuild);

	void	CancelWar(uint32_t GID1, uint32_t GID2);

	bool	ChangeMaster(uint32_t dwGID, uint32_t dwFrom, uint32_t dwTo);

    private:
	void ParseResult(SQLResult * pRes);

	void RemoveWar(uint32_t GID1, uint32_t GID2);	// erase war from m_WarMap and set end on priority queue

	void WarEnd(uint32_t GID1, uint32_t GID2, bool bDraw = false);

	int32_t GetLadderPoint(uint32_t GID);

	void GuildWarWin(uint32_t GID);
	void GuildWarDraw(uint32_t GID);
	void GuildWarLose(uint32_t GID);

	void ProcessDraw(uint32_t dwGuildID1, uint32_t dwGuildID2);
	void ProcessWinLose(uint32_t dwGuildWinner, uint32_t dwGuildLoser);

	bool IsHalfWinLadderPoint(uint32_t dwGuildWinner, uint32_t dwGuildLoser);

	std::map<uint32_t, TGuild>					m_map_kGuild;
	std::map<uint32_t, std::map<uint32_t, int32_t> >		m_mapGuildWarEndTime;

	std::set<TGuildDeclareInfo>				m_DeclareMap; // 선전 포고 상태를 저장
	std::map<uint32_t, std::map<uint32_t, TGuildWarInfo> >	m_WarMap;

	typedef std::pair<int32_t, TGuildWarPQElement *>	stPairGuildWar;
	typedef std::pair<int32_t, TGuildSkillUsed>	stPairSkillUsed;
	typedef std::pair<int32_t, TGuildWaitStartInfo>	stPairWaitStart;

	std::priority_queue<stPairGuildWar, std::vector<stPairGuildWar>, std::greater<stPairGuildWar> >
	    m_pqOnWar;
	std::priority_queue<stPairWaitStart, std::vector<stPairWaitStart>, std::greater<stPairWaitStart> >
	    m_pqWaitStart;
	std::priority_queue<stPairSkillUsed, std::vector<stPairSkillUsed>, std::greater<stPairSkillUsed> >
	    m_pqSkill;

	std::map<uint32_t, CGuildWarReserve *>			m_map_kWarReserve;
	CPoly							polyPower;
	CPoly							polyHandicap;

	// GID Ranking
	std::map<uint32_t, int32_t>					map_kLadderPointRankingByGID;
};

#endif
