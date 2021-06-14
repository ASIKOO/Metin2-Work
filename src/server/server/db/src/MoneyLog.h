// vim: ts=8 sw=4
#ifndef __INC_MONEY_LOG
#define __INC_MONEY_LOG

#include <map>

class CMoneyLog : public singleton<CMoneyLog>
{
    public:
	CMoneyLog();
	virtual ~CMoneyLog();

	void Save();
	void AddLog(uint8_t bType, uint32_t dwVnum, int32_t iGold);

    private:
	std::map<uint32_t, int32_t> m_MoneyLogContainer[MONEY_LOG_TYPE_MAX_NUM];
};

#endif
