#ifndef __INC_METIN_II_GAME_CMD_H__
#define __INC_METIN_II_GAME_CMD_H__

#define ACMD(name)  void (name)(LPCHARACTER ch, const char *argument, int32_t cmd, int32_t subcmd)
#define CMD_NAME(name) cmd_info[cmd].command

struct command_info
{
	const char * command;
	void (*command_pointer) (LPCHARACTER ch, const char *argument, int32_t cmd, int32_t subcmd);
	int32_t subcmd;
	int32_t minimum_position;
	int32_t gm_level;
};

extern struct command_info cmd_info[];

extern void interpret_command(LPCHARACTER ch, const char * argument, uint32_t len);
extern void interpreter_set_privilege(const char * cmd, int32_t lvl);

enum SCMD_ACTION
{
	SCMD_SLAP,
	SCMD_KISS,
	SCMD_FRENCH_KISS,
	SCMD_HUG,
	SCMD_LONG_HUG,
	SCMD_SHOLDER,
	SCMD_FOLD_ARM
};

enum SCMD_CMD
{
	SCMD_LOGOUT,
	SCMD_QUIT,
	SCMD_PHASE_SELECT,
	SCMD_SHUTDOWN,
};

enum SCMD_RESTART
{
	SCMD_RESTART_TOWN,
	SCMD_RESTART_HERE
};

enum SCMD_XMAS
{
	SCMD_XMAS_BOOM,
	SCMD_XMAS_SNOW,
	SCMD_XMAS_SANTA,
};

extern void Shutdown(int32_t iSec);
extern void SendNotice(const char * c_pszBuf);		// �� ���Ӽ������� ����
extern void SendLog(const char * c_pszBuf);		// ��ڿ��Ը� ����
extern void BroadcastNotice(const char * c_pszBuf);	// �� ������ ����
extern void SendNoticeMap(const char* c_pszBuf, int32_t nMapIndex, bool bBigFont); // ���� �ʿ��� ����
extern void SendMonarchNotice(uint8_t bEmpire, const char * c_pszBuf);		// ���� �������� ����

// LUA_ADD_BGM_INFO
void CHARACTER_SetBGMVolumeEnable();
void CHARACTER_AddBGMInfo(uint32_t mapIndex, const char* name, float vol);
// END_OF_LUA_ADD_BGM_INFO

// LUA_ADD_GOTO_INFO
extern void CHARACTER_AddGotoInfo(const std::string& c_st_name, uint8_t empire, int32_t mapIndex, uint32_t x, uint32_t y);
// END_OF_LUA_ADD_GOTO_INFO

#endif
