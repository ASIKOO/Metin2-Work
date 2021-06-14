#ifndef __INC_METIN_II_GAME_BATTLE_H__
#define __INC_METIN_II_GAME_BATTLE_H__

#include "char.h"

enum EBattleTypes       // 상대방 기준
{
	BATTLE_NONE,
	BATTLE_DAMAGE,
	BATTLE_DEFENSE,
	BATTLE_DEAD
};

extern int32_t	CalcAttBonus(LPCHARACTER pkAttacker, LPCHARACTER pkVictim, int32_t iAtk);
extern int32_t	CalcBattleDamage(int32_t iDam, int32_t iAttackerLev, int32_t iVictimLev);
extern int32_t	CalcMeleeDamage(LPCHARACTER pAttacker, LPCHARACTER pVictim, bool bIgnoreDefense = false, bool bIgnoreTargetRating = false);
extern int32_t	CalcMagicDamage(LPCHARACTER pAttacker, LPCHARACTER pVictim);
extern int32_t	CalcArrowDamage(LPCHARACTER pkAttacker, LPCHARACTER pkVictim, LPITEM pkBow, LPITEM pkArrow, bool bIgnoreDefense = false);
extern float	CalcAttackRating(LPCHARACTER pkAttacker, LPCHARACTER pkVictim, bool bIgnoreTargetRating = false);

extern bool	battle_is_attackable(LPCHARACTER ch, LPCHARACTER victim);
extern int32_t	battle_melee_attack(LPCHARACTER ch, LPCHARACTER victim);
extern void	battle_end(LPCHARACTER ch);

extern bool	battle_distance_valid_by_xy(int32_t x, int32_t y, int32_t tx, int32_t ty);
extern bool	battle_distance_valid(LPCHARACTER ch, LPCHARACTER victim);
extern int32_t	battle_count_attackers(LPCHARACTER ch);

extern void	NormalAttackAffect(LPCHARACTER pkAttacker, LPCHARACTER pkVictim);

// 특성 공격
inline void AttackAffect(LPCHARACTER pkAttacker,
		LPCHARACTER pkVictim,
		uint8_t att_point,
		uint32_t immune_flag,
		uint32_t affect_idx,
		uint8_t affect_point,
		int32_t affect_amount,
		uint32_t affect_flag,
		int32_t time,
		const char* name)
{
	if (pkAttacker->GetPoint(att_point) && !pkVictim->IsAffectFlag(affect_flag))
	{
		if (number(1, 100) <= pkAttacker->GetPoint(att_point) && !pkVictim->IsImmune(immune_flag))
		{
			pkVictim->AddAffect(affect_idx, affect_point, affect_amount, affect_flag, time, 0, true);

			if (test_server)
			{
				pkVictim->ChatPacket(CHAT_TYPE_PARTY, "%s %s(%ld%%) SUCCESS", pkAttacker->GetName(), name, pkAttacker->GetPoint(att_point));
			}
		}
		else if (test_server)
		{
			pkVictim->ChatPacket(CHAT_TYPE_PARTY, "%s %s(%ld%%) FAIL", pkAttacker->GetName(), name, pkAttacker->GetPoint(att_point));
		}
	}
}

inline void SkillAttackAffect(LPCHARACTER pkVictim,
		int32_t success_pct,
		uint32_t immune_flag,
		uint32_t affect_idx,
		uint8_t affect_point,
		int32_t affect_amount,
		uint32_t affect_flag,
		int32_t time,
		const char* name)
{
	if (success_pct && !pkVictim->IsAffectFlag(affect_flag))
	{
		if (number(1, 1000) <= success_pct && !pkVictim->IsImmune(immune_flag))
		{
			pkVictim->AddAffect(affect_idx, affect_point, affect_amount, affect_flag, time, 0, true);

			// SKILL_ATTACK_NO_LOG_TARGET_NAME_FIX
			if (test_server)
				pkVictim->ChatPacket(CHAT_TYPE_PARTY, 
						"%s(%d%%) -> %s SUCCESS", name, success_pct, name);
			// END_OF_SKILL_ATTACK_LOG_NO_TARGET_NAME_FIX
		}
		else if (test_server)
		{
			// SKILL_ATTACK_NO_LOG_TARGET_NAME_FIX
			pkVictim->ChatPacket(CHAT_TYPE_PARTY, "%s(%d%%) -> %s FAIL", name, success_pct, name);
			// END_OF_SKILL_ATTACK_LOG_NO_TARGET_NAME_FIX
		}
	}
} 


#define GET_SPEED_HACK_COUNT(ch)		((ch)->m_speed_hack_count)
#define INCREASE_SPEED_HACK_COUNT(ch)	(++GET_SPEED_HACK_COUNT(ch))
uint32_t	GET_ATTACK_SPEED(LPCHARACTER ch);
void	SET_ATTACK_TIME(LPCHARACTER ch, LPCHARACTER victim, uint32_t current_time);
void	SET_ATTACKED_TIME(LPCHARACTER ch, LPCHARACTER victim, uint32_t current_time);
bool	IS_SPEED_HACK(LPCHARACTER ch, LPCHARACTER victim, uint32_t current_time);

#endif
