#ifndef __GUILD_MANAGER_H
#define __GUILD_MANAGER_H

class CGuild;
struct TGuildCreateParameter;

#define GUILD_SYMBOL_FILENAME	"guild_symbol.tga"

class CGuildWarReserveForGame
{
	public:
		TGuildWarReserve				data;
		std::map<std::string, std::pair<uint32_t, uint32_t> > mapBet;
};

class CGuildManager : public singleton<CGuildManager>
{
	public:
		CGuildManager();
		virtual ~CGuildManager();

		uint32_t		CreateGuild(TGuildCreateParameter& gcp);
		CGuild *	FindGuild(uint32_t guild_id);
		CGuild *	FindGuildByName(const std::string guild_name);
		void		LoadGuild(uint32_t guild_id);
		CGuild *	TouchGuild(uint32_t guild_id);
		void		DisbandGuild(uint32_t guild_id);

		void		Initialize();

		void		Link(uint32_t pid, CGuild* guild);
		void		Unlink(uint32_t pid);
		CGuild *	GetLinkedGuild(uint32_t pid);

		void		LoginMember(LPCHARACTER ch);
		void		P2PLoginMember(uint32_t pid);
		void		P2PLogoutMember(uint32_t pid);

		void		SkillRecharge();

		void		ShowGuildWarList(LPCHARACTER ch);
		void		SendGuildWar(LPCHARACTER ch);

		void		RequestEndWar(uint32_t guild_id1, uint32_t guild_id2);
		void		RequestCancelWar(uint32_t guild_id1, uint32_t guild_id2);
		void		RequestWarOver(uint32_t dwGuild1, uint32_t dwGuild2, uint32_t dwGuildWinner, int32_t lReward);

		void		DeclareWar(uint32_t guild_id1, uint32_t guild_id2, uint8_t bType);
		void		RefuseWar(uint32_t guild_id1, uint32_t guild_id2);
		void		StartWar(uint32_t guild_id1, uint32_t guild_id2);
		void		WaitStartWar(uint32_t guild_id1, uint32_t guild_id2);
		void		WarOver(uint32_t guild_id1, uint32_t guild_id2, bool bDraw);
		void		CancelWar(uint32_t guild_id1, uint32_t guild_id2);
		bool		EndWar(uint32_t guild_id1, uint32_t guild_id2);
		void		ReserveWar(uint32_t dwGuild1, uint32_t dwGuild2, uint8_t bType);

		void            ReserveWarAdd(TGuildWarReserve * p);
		void            ReserveWarDelete(uint32_t dwID);
		std::vector<CGuildWarReserveForGame *> & GetReserveWarRef();
		void		ReserveWarBet(TPacketGDGuildWarBet * p);
		bool		IsBet(uint32_t dwID, const char * c_pszLogin);

		void		StopAllGuildWar();

		void		Kill(LPCHARACTER killer, LPCHARACTER victim);

		int32_t		GetRank(CGuild* g);
		//void		GetHighRankString(uint32_t dwMyGuild, char * buffer);
		//void		GetAroundRankString(uint32_t dwMyGuild, char * buffer);
		void		GetHighRankString(uint32_t dwMyGuild, char * buffer, uint32_t buflen);
		void		GetAroundRankString(uint32_t dwMyGuild, char * buffer, uint32_t buflen);

		template <typename Func> void for_each_war(Func & f);

		int32_t		GetDisbandDelay();
		int32_t		GetWithdrawDelay();

		void		ChangeMaster(uint32_t dwGID);

	private:
		typedef std::map<uint32_t, CGuild*> TGuildMap;	
		TGuildMap m_mapGuild;

		typedef std::set<std::pair<uint32_t, uint32_t> > TGuildWarContainer;
		TGuildWarContainer m_GuildWar;

		typedef std::map<std::pair<uint32_t, uint32_t>, uint32_t> TGuildWarEndTimeContainer;
		TGuildWarEndTimeContainer m_GuildWarEndTime;

		TGuildMap				m_map_pkGuildByPID;

		std::map<uint32_t, CGuildWarReserveForGame *>	m_map_kReserveWar;
		std::vector<CGuildWarReserveForGame *>		m_vec_kReserveWar;

		friend class CGuild;
};

template <typename Func> void CGuildManager::for_each_war(Func & f)
{
	for (itertype(m_GuildWar) it = m_GuildWar.begin(); it != m_GuildWar.end(); ++it)
	{
		f(it->first, it->second);
	}
}

extern void SendGuildWarScore(uint32_t dwGuild, uint32_t dwGuildOpp, int32_t iDelta, int32_t iBetScoreDelta = 0);

#endif
