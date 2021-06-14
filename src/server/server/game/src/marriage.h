#ifndef __MARRIAGE_H
#define __MARRIAGE_H

namespace marriage
{
	struct TWeddingInfo
	{
		uint32_t dwMapIndex;
	};

	extern const int32_t MARRIAGE_POINT_PER_DAY;
	struct TMarriage
	{
		uint32_t m_pid1;
		uint32_t m_pid2;
		int32_t   love_point;
		int32_t marry_time;
		LPCHARACTER ch1;
		LPCHARACTER ch2;
		bool bSave;
		bool is_married;
		std::string name1;
		std::string name2;

		TWeddingInfo * pWeddingInfo;

		TMarriage(uint32_t pid1, uint32_t pid2, int32_t _love_point, int32_t _marry_time, const char* name1, const char* name2) : 
			m_pid1(pid1), 
			m_pid2(pid2), 
			love_point(_love_point),
			marry_time(_marry_time), 
			is_married(false),
			name1(name1),
			name2(name2),
			pWeddingInfo(NULL),
			eventNearCheck(NULL)
		{
			ch1 = ch2 = NULL;
			bSave = false;
			isLastNear = false;
			byLastLovePoint = 0;
		}

		~TMarriage();

		void Login(LPCHARACTER ch);
		void Logout(uint32_t pid);

		bool IsOnline()
		{
			return ch1 && ch2;
		}

		bool IsNear();

		uint32_t GetOther(uint32_t PID) const
		{
			if (m_pid1 == PID)
				return m_pid2;

			if (m_pid2 == PID)
				return m_pid1;

			return 0;
		}

		int32_t GetMarriagePoint();
		int32_t GetMarriageGrade();

		int32_t GetBonus(uint32_t dwItemVnum, bool bShare = true, LPCHARACTER me = NULL);

		void WarpToWeddingMap(uint32_t dwPID);
		void Save();
		void SetMarried();

		void Update(uint32_t point);
		void RequestEndWedding();

		void StartNearCheckEvent();
		void StopNearCheckEvent();
		void NearCheck();

		bool isLastNear;
		uint8_t byLastLovePoint;
		LPEVENT eventNearCheck;
	};

	class CManager : public singleton<CManager>
	{
		public:
			CManager();
			virtual ~CManager();

			bool	Initialize();
			void	Destroy();

			TMarriage*	Get(uint32_t dwPlayerID);

			bool	IsMarriageUniqueItem(uint32_t dwItemVnum);

			bool	IsMarried(uint32_t dwPlayerID);
			bool	IsEngaged(uint32_t dwPlayerID);
			bool	IsEngagedOrMarried(uint32_t dwPlayerID);

			void	RequestAdd(uint32_t dwPID1, uint32_t dwPID2, const char* szName1, const char* szName2);
			void	Add(uint32_t dwPID1, uint32_t dwPID2, int32_t tMarryTime, const char* szName1, const char* szName2);

			void	RequestUpdate(uint32_t dwPID1, uint32_t dwPID2, int32_t iUpdatePoint, uint8_t byMarried);
			void	Update(uint32_t dwPID1, uint32_t dwPID2, int32_t lTotalPoint, uint8_t byMarried);

			void	RequestRemove(uint32_t dwPID1, uint32_t dwPID2);
			void	Remove(uint32_t dwPID1, uint32_t dwPID2);

			//void	P2PLogin(uint32_t dwPID);
			//void	P2PLogout(uint32_t dwPID);

			void	Login(LPCHARACTER ch);

			void	Logout(uint32_t pid);
			void	Logout(LPCHARACTER ch);

			void	WeddingReady(uint32_t dwPID1, uint32_t dwPID2, uint32_t dwMapIndex);
			void	WeddingStart(uint32_t dwPID1, uint32_t dwPID2);
			void	WeddingEnd(uint32_t dwPID1, uint32_t dwPID2);

			void	RequestEndWedding(uint32_t dwPID1, uint32_t dwPID2);

			template <typename Func>
				Func	for_each_wedding(Func f);

		private:
			std::unordered_set<TMarriage*> m_Marriages;
			std::map<uint32_t, TMarriage *> m_MarriageByPID;
			std::set<std::pair<uint32_t, uint32_t> > m_setWedding;
	};

	template <typename Func>
		Func CManager::for_each_wedding(Func f)
		{
			for (itertype(m_setWedding) it = m_setWedding.begin(); it!=m_setWedding.end(); ++it)
			{
				TMarriage* pMarriage = Get(it->first);
				if (pMarriage)
					f(pMarriage);
			}
			return f;
		}

}

#endif
