#ifndef __HORSE_H
#define __HORSE_H

#include "constants.h"
#include "cmd.h"

const int32_t HORSE_MAX_LEVEL = 30;

struct THorseStat
{
	int32_t iMinLevel;      // 탑승할 수 있는 최소 레벨
	int32_t iNPCRace;
	int32_t iMaxHealth;     // 말의 최대 체력
	int32_t iMaxStamina;    // 말의 최대 스테미너
	int32_t iST;
	int32_t iDX;
	int32_t iHT;
	int32_t iIQ;
	int32_t iDamMean;
	int32_t iDamMin;
	int32_t iDamMax;
	int32_t iArmor;
};

extern THorseStat c_aHorseStat[HORSE_MAX_LEVEL+1];

class CHorseRider
{
	public:
		CHorseRider();
		virtual ~CHorseRider();
		
		uint8_t		GetHorseLevel() const { return m_Horse.bLevel; }
		uint8_t		GetHorseGrade();
		int16_t		GetHorseHealth() const	{ return m_Horse.sHealth; }
		int16_t		GetHorseStamina() const	{ return m_Horse.sStamina; }
		int16_t		GetHorseMaxHealth();
		int16_t		GetHorseMaxStamina();

		int32_t		GetHorseST()		{ return c_aHorseStat[GetHorseLevel()].iST; }
		int32_t		GetHorseDX()		{ return c_aHorseStat[GetHorseLevel()].iDX; }
		int32_t		GetHorseHT()		{ return c_aHorseStat[GetHorseLevel()].iHT; }
		int32_t		GetHorseIQ()		{ return c_aHorseStat[GetHorseLevel()].iIQ; }
		int32_t		GetHorseArmor()		{ return c_aHorseStat[GetHorseLevel()].iArmor; }

		virtual bool ReviveHorse();
		void FeedHorse();
		virtual void HorseDie();

		bool IsHorseRiding() const		{ return m_Horse.bRiding; }

		void ResetHorseHealthDropTime();

		virtual void SetHorseLevel(int32_t iLevel);

		void EnterHorse();

		virtual void SendHorseInfo() {}
		virtual void ClearHorseInfo() {}

		virtual void UpdateRideTime(int32_t interval) {}

	protected:
		void SetHorseData(const THorseInfo& crInfo);
		const THorseInfo& GetHorseData() const { return m_Horse; }

		void UpdateHorseDataByLogoff(uint32_t dwLogoffTime);

		virtual bool StartRiding();
		virtual bool StopRiding();

		virtual	uint32_t GetMyHorseVnum() const { return 20030; }

	private:
		void UpdateHorseStamina(int32_t iStamina, bool bSend = true);

		void StartStaminaConsumeEvent();
		void StartStaminaRegenEvent();

		void UpdateHorseHealth(int32_t iHealth, bool bSend = true);
		void CheckHorseHealthDropTime(bool bSend = true);

		void Initialize();
		void Destroy();

		THorseInfo m_Horse;

		LPEVENT	m_eventStaminaRegen;
		LPEVENT	m_eventStaminaConsume;

		friend EVENTFUNC(horse_stamina_regen_event);
		friend EVENTFUNC(horse_stamina_consume_event);
		friend ACMD(do_horse_set_stat);
};

#endif
