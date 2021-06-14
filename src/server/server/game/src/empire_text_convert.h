#ifndef __INC_EMPIRE_CHAT_CONVERT
#define __INC_EMPIRE_CHAT_CONVERT

bool LoadEmpireTextConvertTable(uint32_t dwEmpireID, const char* c_szFileName);
void ConvertEmpireText(uint32_t dwEmpireID, char* szText, uint32_t len, int32_t iPct);

#endif
