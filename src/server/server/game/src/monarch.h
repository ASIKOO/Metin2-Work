#ifndef __INC_METIN_II_MONARCH_H__
#define __INC_METIN_II_MONARCH_H__

#include "../../common/tables.h"

class CMonarch : public singleton<CMonarch>
{
	public:
		CMonarch();
		virtual ~CMonarch();

		bool Initialize();

		int32_t HealMyEmpire(LPCHARACTER ch, uint32_t price);
		void SetMonarchInfo(TMonarchInfo * pInfo);

		bool IsMonarch(uint32_t pid, uint8_t bEmpire);
		bool IsMoneyOk(int32_t price, uint8_t bEmpire);
		bool SendtoDBAddMoney(int32_t Money, uint8_t bEmpire, LPCHARACTER ch);
		bool SendtoDBDecMoney(int32_t Money, uint8_t bEmpire, LPCHARACTER ch);

		bool AddMoney(int32_t Money, uint8_t bEmpire);
		bool DecMoney(int32_t Money, uint8_t bEmpire);
		int32_t GetMoney(uint8_t bEmpire);

		TMonarchInfo* GetMonarch();

		uint32_t GetMonarchPID(uint8_t Empire);

		bool IsPowerUp(uint8_t Empire);
		bool IsDefenceUp(uint8_t Empire);

		int32_t	GetPowerUpCT(uint8_t Empire)
		{
			return Empire < _countof(m_PowerUpCT) ? m_PowerUpCT[Empire] : 0;
		}

		bool CheckPowerUpCT(uint8_t Empire);
		bool CheckDefenseUpCT(uint8_t Empire);

		int32_t	GetDefenseUpCT(uint8_t Empire)
		{
			return Empire < _countof(m_DefenseUpCT) ? m_DefenseUpCT[Empire] : 0;
		}

		void PowerUp(uint8_t Empire, bool On);
		void DefenseUp(uint8_t Empire, bool On);

	private:
		TMonarchInfo m_MonarchInfo;	

		int32_t m_PowerUp[4]; ///< 군주의 사자후
		int32_t m_DefenseUp[4]; ///< 군주의 금강권

		int32_t m_PowerUpCT[4]; ///< 군주의 사자후
		int32_t m_DefenseUpCT[4]; ///< 군주의 금강권
};

bool IsMonarchWarpZone (int32_t map_idx);

#endif
