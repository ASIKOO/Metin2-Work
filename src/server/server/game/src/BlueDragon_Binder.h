
enum BLUEDRAGON_STONE_EFFECT
{
	DEF_BONUS	=	1,
	ATK_BONUS	=	2,
	REGEN_TIME_BONUS	=	3,
	REGEN_PECT_BONUS	=	4,
};

extern uint32_t BlueDragon_GetRangeFactor (const char* key, const int32_t val);
extern uint32_t BlueDragon_GetSkillFactor (const uint32_t cnt, ...);
extern uint32_t BlueDragon_GetIndexFactor (const char* container, const uint32_t idx, const char* key);

