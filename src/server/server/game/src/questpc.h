#ifndef __QUEST_PC_H
#define __QUEST_PC_H

#include "quest.h"

class CHARACTER;

namespace quest
{
	using namespace std;

	struct RewardData
	{
		enum RewardType
		{
			REWARD_TYPE_NONE,
			REWARD_TYPE_EXP,
			REWARD_TYPE_ITEM,
		} type;

		uint32_t value1;
		int32_t value2;	

		RewardData(RewardType t, uint32_t value1, int32_t value2 = 0) : 
			type(t),
			value1(value1),
			value2(value2)
		{
		}
	};

	class PC
	{
		public:
			enum 
			{
				QUEST_SEND_ISBEGIN		= (1 << 0),
				QUEST_SEND_TITLE		= (1 << 1),  // 30자 까지 
				QUEST_SEND_CLOCK_NAME		= (1 << 2),  // 16자 까지		
				QUEST_SEND_CLOCK_VALUE		= (1 << 3),
				QUEST_SEND_COUNTER_NAME		= (1 << 4),  // 16자 까지	
				QUEST_SEND_COUNTER_VALUE	= (1 << 5),
				QUEST_SEND_ICON_FILE		= (1 << 6),  // 24자 까지
			};

			typedef map<uint32_t, QuestState>	QuestInfo;
			typedef QuestInfo::iterator				QuestInfoIterator;

			PC();
			~PC();

			void		Destroy();
			void		SetID(uint32_t dwID);
			uint32_t		GetID() { return m_dwID; }

			bool		HasQuest(const string & quest_name);
			QuestState & GetQuest(const string& quest_name);

			inline QuestInfoIterator quest_begin();
			inline QuestInfoIterator quest_end();
			inline QuestInfoIterator quest_find(uint32_t quest_index);

			inline bool IsRunning();

			void		EndRunning();
			void		CancelRunning();

			inline QuestState *	GetRunningQuestState();

			void		SetQuest(const string& quest_name, QuestState& qs);
			void		SetCurrentQuestStateName(const string& state_name);
			void		SetQuestState(const string& quest_name, const string& state_name);
			void		SetQuestState(const string& quest_name, int32_t new_state_index);

			void		ClearQuest(const string& quest_name);

		private:
			void		AddQuestStateChange(const string& quest_name, int32_t prev_state, int32_t next_state);
			void		DoQuestStateChange();

			struct TQuestStateChangeInfo
			{
				uint32_t quest_idx;
				int32_t prev_state;
				int32_t next_state;

				TQuestStateChangeInfo(uint32_t _quest_idx, int32_t _prev_state, int32_t _next_state) :
					quest_idx(_quest_idx),
					prev_state(_prev_state),
					next_state(_next_state)
				{
				}
			};

			vector<TQuestStateChangeInfo> m_QuestStateChange;

		public:
			void		SetFlag(const string & name, int32_t value, bool bSkipSave = false);
			int32_t			GetFlag(const string & name);
			bool		DeleteFlag(const string & name);

			const string &	GetCurrentQuestName() const;
			int32_t			GetCurrentQuestIndex();

			void		RemoveTimer(const string& name);
			void		RemoveTimerNotCancel(const string& name);
			void		AddTimer(const string& name, LPEVENT pEvent);
			void		ClearTimer();

			void		SetCurrentQuestStartFlag();
			void		SetCurrentQuestDoneFlag();

			void		SetQuestTitle(const string& quest,const string & title);

			void		SetCurrentQuestTitle(const string & title);
			void		SetCurrentQuestClockName(const string & name);
			void		SetCurrentQuestClockValue(int32_t value);
			void		SetCurrentQuestCounterName(const string & name);
			void		SetCurrentQuestCounterValue(int32_t value);
			void		SetCurrentQuestIconFile(const string& icon_file);

			bool		IsLoaded() const	{ return m_bLoaded; }
			void		SetLoaded()	{ m_bLoaded = true; }
			void		Build();
			// DB에 저장
			void		Save();

			bool		HasReward() { return !m_vRewardData.empty() || m_bIsGivenReward; }
			void		Reward(LPCHARACTER ch);

			void		GiveItem(const string& label, uint32_t dwVnum, int32_t count);
			void		GiveExp(const string& label, uint32_t exp);

			void 		SetSendDoneFlag() { m_bShouldSendDone = true; }
			bool		GetAndResetDoneFlag() { bool temp = m_bShouldSendDone; m_bShouldSendDone = false; return temp; }

			void		SendFlagList(LPCHARACTER ch);

			void		SetQuestState(const char* szQuestName, const char* szStateName);

			void		SetConfirmWait(uint32_t dwPID) { m_bConfirmWait = true; m_dwWaitConfirmFromPID = dwPID; }
			void		ClearConfirmWait() { m_bConfirmWait = false; }
			bool		IsConfirmWait() const	{ return m_bConfirmWait; }
			bool		IsConfirmWait(uint32_t dwPID) const	{ return m_bConfirmWait && dwPID == m_dwWaitConfirmFromPID; }

		private:
			void		SetSendFlag(int32_t idx);
			void		ClearSendFlag() { m_iSendToClient = 0; }
			void		SaveFlag(const string & name, int32_t value);

			void		ClearCurrentQuestBeginFlag();
			void		SetCurrentQuestBeginFlag();
			int32_t			GetCurrentQuestBeginFlag();

			void		SendQuestInfoPakcet();

		private:
			vector<RewardData>	m_vRewardData;
			bool		m_bIsGivenReward;

			bool		m_bShouldSendDone;

			uint32_t		m_dwID;

			QuestInfo		m_QuestInfo;

			QuestState *	m_RunningQuestState;
			string		m_stCurQuest;

			typedef map<string, int32_t> TFlagMap;
			TFlagMap		m_FlagMap;

			TFlagMap		m_FlagSaveMap;

			typedef map<string, LPEVENT> TTimerMap;
			TTimerMap		m_TimerMap;

			int32_t			m_iSendToClient;
			bool		m_bLoaded; // 로드는 한번만 한다.

			int32_t			m_iLastState;

			uint32_t		m_dwWaitConfirmFromPID;
			bool		m_bConfirmWait;
	};

	inline PC::QuestInfoIterator PC::quest_begin()
	{
		return m_QuestInfo.begin();
	}

	inline PC::QuestInfoIterator PC::quest_end()
	{
		return m_QuestInfo.end();
	}

	inline PC::QuestInfoIterator PC::quest_find(uint32_t quest_index)
	{
		return m_QuestInfo.find(quest_index);
	}

	inline bool PC::IsRunning()
	{
		return m_RunningQuestState != NULL;
	}

	inline QuestState* PC::GetRunningQuestState()
	{
		return m_RunningQuestState;
	}
}

#endif
