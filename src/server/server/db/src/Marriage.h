// vim: ts=4 sw=4
#ifndef __MARRIAGE_H
#define __MARRIAGE_H

#include <set>
#include <queue>
#include <deque>

#include "Peer.h"

namespace marriage
{
	struct TWeddingInfo
	{
		uint32_t dwTime;
		uint32_t dwPID1;
		uint32_t dwPID2;
		TWeddingInfo(uint32_t time, uint32_t pid1, uint32_t pid2)
			: dwTime(time),
			dwPID1(pid1),
			dwPID2(pid2)
		{
		}
	};

	struct TWedding
	{
		uint32_t dwTime;
		uint32_t dwMapIndex;
		uint32_t dwPID1;
		uint32_t dwPID2;

		TWedding(uint32_t time, uint32_t dwMapIndex, uint32_t pid1, uint32_t pid2)
			: dwTime(time),
			dwMapIndex(dwMapIndex),
			dwPID1(pid1),
			dwPID2(pid2)
		{
		}
	};

	extern bool operator < (const TWedding& lhs, const TWedding& rhs);
	extern bool operator > (const TWedding& lhs, const TWedding& rhs);
	extern bool operator > (const TWeddingInfo& lhs, const TWeddingInfo& rhs);

	struct TMarriage
	{
		uint32_t pid1;
		uint32_t pid2;
		int32_t   love_point;
		uint32_t time;
		uint8_t is_married; // false : æ‡»• ªÛ≈¬, true : ∞·»• ªÛ≈¬
		std::string name1;
		std::string name2;

		TMarriage(uint32_t _pid1, uint32_t _pid2, int32_t _love_point, uint32_t _time, uint8_t _is_married, const char* name1, const char* name2)
			: pid1(_pid1), pid2(_pid2), love_point(_love_point), time(_time), is_married(_is_married), name1(name1), name2(name2)
		{
		}

		uint32_t GetOther(uint32_t PID)
		{
			if (pid1 == PID)
				return pid2;

			if (pid2 == PID)
				return pid1;

			return 0;
		}
	};

	class CManager : public singleton<CManager>
	{
		public:
			CManager();
			virtual ~CManager();

			bool Initialize();

			TMarriage* Get(uint32_t dwPlayerID);
			bool IsMarried(uint32_t dwPlayerID)
			{
				return Get(dwPlayerID) != NULL;
			}

			//void	Reserve(uint32_t dwPID1, uint32_t dwPID2);
			void	Add(uint32_t dwPID1, uint32_t dwPID2, const char* szName1, const char* szName2);
			void	Remove(uint32_t dwPID1, uint32_t dwPID2);
			void	Update(uint32_t dwPID1, uint32_t dwPID2, int32_t iLovePoint, uint8_t byMarried);

			void	EngageToMarriage(uint32_t dwPID1, uint32_t dwPID2);

			void	ReadyWedding(uint32_t dwMapIndex, uint32_t dwPID1, uint32_t dwPID2);
			void	EndWedding(uint32_t dwPID1, uint32_t dwPID2);

			void	OnSetup(CPeer* peer);

			void	Update();

		private:
			std::set<TMarriage *> m_Marriages;
			std::map<uint32_t, TMarriage *> m_MarriageByPID;

			std::priority_queue<TWedding, std::vector<TWedding>, std::greater<TWedding> > m_pqWeddingStart;

			std::priority_queue<TWeddingInfo, std::vector<TWeddingInfo>, std::greater<TWeddingInfo> > m_pqWeddingEnd;

			std::map<std::pair<uint32_t, uint32_t>, TWedding> m_mapRunningWedding;
	};
}

#endif
