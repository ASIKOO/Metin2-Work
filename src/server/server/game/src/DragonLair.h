
#include <boost/unordered_map.hpp>

#include "../../common/stl.h"

class CDragonLair
{
	public:
		CDragonLair (uint32_t dwGuildID, int32_t BaseMapID, int32_t PrivateMapID);
		virtual ~CDragonLair ();

		uint32_t GetEstimatedTime () const;

		void OnDragonDead (LPCHARACTER pDragon);

	private:
		uint32_t StartTime_;
		uint32_t GuildID_;
		int32_t BaseMapIndex_;
		int32_t PrivateMapIndex_;
};

class CDragonLairManager : public singleton<CDragonLairManager>
{
	public:
		CDragonLairManager ();
		virtual ~CDragonLairManager ();

		bool Start (int32_t MapIndexFrom, int32_t BaseMapIndex, uint32_t GuildID);
		void OnDragonDead (LPCHARACTER pDragon, uint32_t KillerGuildID);

		uint32_t GetLairCount () const { return LairMap_.size(); }

	private:
		boost::unordered_map<uint32_t, CDragonLair*> LairMap_;
};

