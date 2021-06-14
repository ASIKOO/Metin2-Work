#ifndef __METIN2_SERVER_QUEST_MANAGER__
#define __METIN2_SERVER_QUEST_MANAGER__

#include <boost/unordered_map.hpp>

#include "questnpc.h"

class ITEM;
class CHARACTER;
class CDungeon;

namespace quest
{
	using namespace std;

	bool IsScriptTrue(const char* code, int32_t size);
	string ScriptToString(const string& str);

	class CQuestManager : public singleton<CQuestManager>
	{
		public:
			enum
			{
				QUEST_SKIN_NOWINDOW,
				QUEST_SKIN_NORMAL,
				//QUEST_SKIN_CINEMATIC,
				QUEST_SKIN_SCROLL=4,
				QUEST_SKIN_CINEMATIC=5,
				QUEST_SKIN_COUNT
			};

			typedef map<string, int32_t>		TEventNameMap;
			typedef map<uint32_t, PC>	PCMap;

		public:
			CQuestManager();
			virtual ~CQuestManager();

			bool		Initialize();
			void		Destroy();

			bool		InitializeLua();
			lua_State *		GetLuaState() { return L; }
			void		AddLuaFunctionTable(const char * c_pszName, luaL_reg * preg);

			TEventNameMap	m_mapEventName;

			QuestState		OpenState(const string& quest_name, int32_t state_index);
			void		CloseState(QuestState& qs);
			bool		RunState(QuestState& qs);

			PC *		GetPC(uint32_t pc);
			PC *		GetPCForce(uint32_t pc);	// 현재 PC를 바꾸지 않고 PC 포인터를 가져온다.

			uint32_t	GetCurrentNPCRace();
			const string & 	GetCurrentQuestName();
			uint32_t	FindNPCIDByName(const string& name);

			//void		SetCurrentNPCCharacterPtr(LPCHARACTER ch) { m_pkCurrentNPC = ch; }
			LPCHARACTER		GetCurrentNPCCharacterPtr();

			void		SetCurrentEventIndex(int32_t index) { m_iRunningEventIndex = index; }

			bool		UseItem(uint32_t pc, LPITEM item, bool bReceiveAll);
			bool		PickupItem(uint32_t pc, LPITEM item);
			bool		SIGUse(uint32_t pc, uint32_t sig_vnum, LPITEM item, bool bReceiveAll);
			bool		TakeItem(uint32_t pc, uint32_t npc, LPITEM item);
			LPITEM		GetCurrentItem();
			void		ClearCurrentItem();
			void		SetCurrentItem(LPITEM item);
			void		AddServerTimer(const string& name, uint32_t arg, LPEVENT event);
			void		ClearServerTimer(const string& name, uint32_t arg);
			void		ClearServerTimerNotCancel(const string& name, uint32_t arg);
			void		CancelServerTimers(uint32_t arg);

			void		SetServerTimerArg(uint32_t dwArg);
			uint32_t		GetServerTimerArg();

			// event over state and stae
			bool		ServerTimer(uint32_t npc, uint32_t arg);

			void		Login(uint32_t pc, const char * c_pszQuestName = NULL);
			void		Logout(uint32_t pc);
			bool		Timer(uint32_t pc, uint32_t npc);
			bool		Click(uint32_t pc, LPCHARACTER pkNPC);
			void		Kill(uint32_t pc, uint32_t npc);
			void		LevelUp(uint32_t pc);
			void		AttrIn(uint32_t pc, LPCHARACTER ch, int32_t attr);
			void		AttrOut(uint32_t pc, LPCHARACTER ch, int32_t attr);
			bool		Target(uint32_t pc, uint32_t dwQuestIndex, const char * c_pszTargetName, const char * c_pszVerb);
			bool		GiveItemToPC(uint32_t pc, LPCHARACTER pkChr);
			void		Unmount(uint32_t pc);

			void		QuestButton(uint32_t pc, uint32_t quest_index);
			void		QuestInfo(uint32_t pc, uint32_t quest_index);

			void		EnterState(uint32_t pc, uint32_t quest_index, int32_t state);
			void		LeaveState(uint32_t pc, uint32_t quest_index, int32_t state);

			void		Letter(uint32_t pc);
			void		Letter(uint32_t pc, uint32_t quest_index, int32_t state);
			
			void		ItemInformer(uint32_t pc, uint32_t vnum);	//독일선물기능

			//

			bool		CheckQuestLoaded(PC* pc) { return pc && pc->IsLoaded(); }

			// event occurs in one state
			void		Select(uint32_t pc, uint32_t selection);
			void		Resume(uint32_t pc);
			void		Input(uint32_t pc, const char* msg);
			void		Confirm(uint32_t pc, EQuestConfirmType confirm, uint32_t pc2 = 0);
			void		SelectItem(uint32_t pc, uint32_t selection);

			void		LogoutPC(LPCHARACTER ch);
			void		DisconnectPC(LPCHARACTER ch);

			QuestState *	GetCurrentState()	{ return m_CurrentRunningState; }

			void 		LoadStartQuest(const string& quest_name, uint32_t idx);
			//bool		CanStartQuest(const string& quest_name, const PC& pc);
			bool		CanStartQuest(uint32_t quest_index, const PC& pc);
			bool		CanStartQuest(uint32_t quest_index);
			bool		CanEndQuestAtState(const string& quest_name, const string& state_name);

			LPCHARACTER		GetCurrentCharacterPtr() { return m_pCurrentCharacter; }
			LPCHARACTER		GetCurrentPartyMember() { return m_pCurrentPartyMember; }
			PC *		GetCurrentPC() { return m_pCurrentPC; }

			LPDUNGEON		GetCurrentDungeon();
			void		SelectDungeon(LPDUNGEON pDungeon);

			void		ClearScript();
			void		SendScript();
			void		AddScript(const string& str);

			void		BuildStateIndexToName(const char* questName);

			int32_t			GetQuestStateIndex(const string& quest_name, const string& state_name);
			const char*		GetQuestStateName(const string& quest_name, const int32_t state_index);

			void		SetSkinStyle(int32_t iStyle);

			void		SetNoSend() { m_bNoSend = true; }

			uint32_t	LoadTimerScript(const string& name);

			//uint32_t	RegisterQuestName(const string& name);

			void		RegisterQuest(const string & name, uint32_t idx);
			uint32_t 	GetQuestIndexByName(const string& name);
			const string& 	GetQuestNameByIndex(uint32_t idx);

			void		RequestSetEventFlag(const string& name, int32_t value);

			void		SetEventFlag(const string& name, int32_t value);
			int32_t			GetEventFlag(const string& name);
			void		BroadcastEventFlagOnLogin(LPCHARACTER ch);

			void		SendEventFlagList(LPCHARACTER ch);

			void		Reload();

			//void		CreateAllButton(const string& quest_name, const string& button_name);
			void		SetError() { m_bError = true; }
			void		ClearError() { m_bError = false; }
			bool		IsError() { return m_bError; }
			void		WriteRunningStateToSyserr();
#ifndef __WIN32__
			void		QuestError(const char* func, int32_t line, const char* fmt, ...);
#else
			//void		QuestError(const char* fmt, ...);
			void		QuestError(const char* func, int32_t line, const char* fmt, ...);
#endif

			void		RegisterNPCVnum(uint32_t dwVnum);

		private:
			LPDUNGEON			m_pSelectedDungeon;
			uint32_t			m_dwServerTimerArg;

			map<pair<string, uint32_t>, LPEVENT>	m_mapServerTimer;

			int32_t				m_iRunningEventIndex;

			map<string, int32_t>		m_mapEventFlag;

			void			GotoSelectState(QuestState& qs);
			void			GotoPauseState(QuestState& qs);
			void			GotoEndState(QuestState& qs);
			void			GotoInputState(QuestState& qs);
			void			GotoConfirmState(QuestState& qs);
			void			GotoSelectItemState(QuestState& qs);

			lua_State *		L;

			bool			m_bNoSend;

			set<uint32_t>			m_registeredNPCVnum;
			map<uint32_t, NPC>		m_mapNPC;
			map<string, uint32_t>	m_mapNPCNameID;
			map<string, uint32_t>	m_mapTimerID;

			QuestState *	m_CurrentRunningState;

			PCMap			m_mapPC;

			LPCHARACTER		m_pCurrentCharacter;
			LPCHARACTER		m_pCurrentNPCCharacter;
			LPCHARACTER		m_pCurrentPartyMember;
			PC*				m_pCurrentPC;

			string			m_strScript;

			int32_t				m_iCurrentSkin;

			struct stringhash
			{
				uint32_t operator () (const string& str) const
				{
					const uint8_t * s = (const uint8_t*) str.c_str();
					const uint8_t * end = s + str.size();
					uint32_t h = 0;

					while (s < end)
					{
						h *= 16777619;
						h ^= (uint8_t) *(uint8_t *) (s++);
					}

					return h;

				}
			};

			typedef boost::unordered_map<string, int32_t, stringhash> THashMapQuestName;
			typedef boost::unordered_map<uint32_t, vector<char> > THashMapQuestStartScript;

			THashMapQuestName			m_hmQuestName;
			THashMapQuestStartScript	m_hmQuestStartScript;
			map<uint32_t, string>	m_mapQuestNameByIndex;

			bool						m_bError;

		public:
			static bool ExecuteQuestScript(PC& pc, const string& quest_name, const int32_t state, const char* code, const int32_t code_size, vector<AArgScript*>* pChatScripts = NULL, bool bUseCache = true);
			static bool ExecuteQuestScript(PC& pc, uint32_t quest_index, const int32_t state, const char* code, const int32_t code_size, vector<AArgScript*>* pChatScripts = NULL, bool bUseCache = true);
		

		// begin_other_pc_blcok, end_other_pc_block을 위한 객체들.
		public:
			void		BeginOtherPCBlock(uint32_t pid);
			void		EndOtherPCBlock();
			bool		IsInOtherPCBlock();
			PC*			GetOtherPCBlockRootPC();
		private:
			PC*			m_pOtherPCBlockRootPC;
			std::vector <uint32_t>	m_vecPCStack;
	};
};

#endif
