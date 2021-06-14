
#ifndef THREE_WAY_WAR_EVENT_
#define THREE_WAY_WAR_EVENT_

#include <boost/unordered_map.hpp>

#include "../../common/stl.h"

struct ForkedSungziMapInfo
{
	int32_t m_iForkedSung;
	int32_t m_iForkedSungziStartPosition[3][2];
	std::string m_stMapName;
	int32_t m_iBossMobVnum;
};

struct ForkedPassMapInfo
{
	int32_t m_iForkedPass[3];
	int32_t m_iForkedPassStartPosition[3][2];
	std::string m_stMapName[3];
};

class CThreeWayWar : public singleton<CThreeWayWar>
{
	public:
		CThreeWayWar ();
		virtual ~CThreeWayWar ();

		void Initialize ();
		bool LoadSetting (const char* szFileName);

		int32_t GetKillScore (uint8_t empire) const;
		void SetKillScore (uint8_t empire, int32_t count);

		void SetReviveTokenForPlayer (uint32_t PlayerID, int32_t count);
		int32_t GetReviveTokenForPlayer (uint32_t PlayerID);
		void DecreaseReviveTokenForPlayer (uint32_t PlayerID);

		const ForkedPassMapInfo& GetEventPassMapInfo () const;
		const ForkedSungziMapInfo& GetEventSungZiMapInfo () const;

		bool IsThreeWayWarMapIndex (int32_t iMapIndex) const;
		bool IsSungZiMapIndex (int32_t iMapIndex) const;

		void RandomEventMapSet ();

		void RegisterUser (uint32_t PlayerID);
		bool IsRegisteredUser (uint32_t PlayerID) const;

		void onDead (LPCHARACTER pChar, LPCHARACTER pKiller);

		void SetRegenFlag (int32_t flag) { RegenFlag_ = flag; }
		int32_t GetRegenFlag () const { return RegenFlag_; }

		void RemoveAllMonstersInThreeWay () const;

	private:
		int32_t KillScore_[3];
		int32_t RegenFlag_;

		std::set<int32_t>	MapIndexSet_;
		std::vector<ForkedPassMapInfo>	PassInfoMap_;
		std::vector<ForkedSungziMapInfo>	SungZiInfoMap_;

		boost::unordered_map<uint32_t, uint32_t>	RegisterUserMap_;
		boost::unordered_map<uint32_t, int32_t>	ReviveTokenMap_;
};

const char* GetSungziMapPath();
const char* GetPassMapPath( uint8_t bEmpire );
int32_t GetPassMapIndex( uint8_t bEmpire );
int32_t GetSungziMapIndex();

int32_t GetSungziStartX( uint8_t bEmpire );
int32_t GetSungziStartY( uint8_t bEmpire );
int32_t GetPassStartX( uint8_t bEmpire );
int32_t GetPassStartY( uint8_t bEmpire );

#endif /* THREE_WAY_WAR_EVENT_ */

