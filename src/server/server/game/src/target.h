#ifndef __INC_METIN_II_GAME_TARGET_H__
#define __INC_METIN_II_GAME_TARGET_H__

enum ETargetTypes
{
	TARGET_TYPE_POS	= (1 << 0),
	TARGET_TYPE_VID	= (1 << 1),
};

EVENTINFO(TargetInfo)
{
	// <Factor> Removed unsafe copy of CHARACTER* here
	//LPCHARACTER pkChr;

	int32_t         iID;

	uint32_t       dwPID;
	uint32_t       dwQuestIndex;

	char        szTargetName[32+1]; // 퀘스트에서 사용하는 이름
	char        szTargetDesc[32+1]; // 실제 클라이언트에 전송되는 이름

	int32_t         iType;
	int32_t         iArg1;
	int32_t         iArg2;

	int32_t		iMapIndex;
	int32_t         iOldX;
	int32_t         iOldY;

	bool	bSendToClient;

	TargetInfo() 
	: iID( 0 )
	, dwPID( 0 )
	, dwQuestIndex( 0 )
	, iType( 0 )
	, iArg1( 0 )
	, iArg2( 0 )
	, iMapIndex( 0 )
	, iOldX( 0 )
	, iOldY( 0 )
	, bSendToClient( false )
	{
		::memset(szTargetName, 0, 32+1);
		::memset(szTargetDesc, 0, 32+1);
	}
};

class CTargetManager : public singleton<CTargetManager>
{
	public:
		CTargetManager();
		virtual ~CTargetManager();

		void CreateTarget(uint32_t dwPID, uint32_t dwQuestIndex, const char * c_pszTargetName, int32_t iType, int32_t iArg1, int32_t iArg2, int32_t iMapIndex, const char * c_pszTargetDesc = NULL, int32_t iSendFlag = 1);
		void DeleteTarget(uint32_t dwPID, uint32_t dwQuestIndex, const char * c_pszTargetName);

		void Logout(uint32_t dwPID);
		TargetInfo * GetTargetInfo(uint32_t dwPID, int32_t iType, int32_t iArg1);

		LPEVENT GetTargetEvent(uint32_t dwPID, uint32_t dwQuestIndex, const char * c_pszTargetName);

	protected:
		// first: PID
		std::map<uint32_t, std::list<LPEVENT> > m_map_kListEvent;
		int32_t m_iID;
};

#endif
