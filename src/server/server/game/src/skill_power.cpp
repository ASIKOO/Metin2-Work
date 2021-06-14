
#include "stdafx.h"

#include "../../common/length.h"

#include "skill_power.h"

bool CTableBySkill::Check() const
{
	for (int32_t job = 0; job < (JOB_MAX_NUM * 2); ++job)
	{
		if (!m_aiSkillPowerByLevelFromType[job])
		{
			fprintf( stderr, "[NO SETTING SKILL] aiSkillPowerByLevelFromType[%d]", job);
			return false;
		}
	}

	return true;
}

void CTableBySkill::DeleteAll()
{
	for ( int32_t job = 0; job < JOB_MAX_NUM * 2; ++job )
	{
		DeleteSkillPowerByLevelFromType( job );
	}

	DeleteSkillDamageByLevelTable();
}

int32_t CTableBySkill::GetSkillPowerByLevelFromType(int32_t job, int32_t skillgroup, int32_t skilllevel, bool bMob) const
{
	if (bMob)
	{
		return m_aiSkillPowerByLevelFromType[0][skilllevel];
	}

	if (job >= JOB_MAX_NUM || skillgroup == 0)
		return 0;

	int32_t idx = (job * 2) + (skillgroup - 1);

	return m_aiSkillPowerByLevelFromType[idx][skilllevel];
}

void CTableBySkill::SetSkillPowerByLevelFromType(int32_t idx, const int32_t* aTable)
{
	DeleteSkillPowerByLevelFromType(idx);

	int32_t* aiSkillTable = M2_NEW int32_t[SKILL_MAX_LEVEL+1];

	memcpy (aiSkillTable, aTable, sizeof(int32_t) * (SKILL_MAX_LEVEL + 1));
	m_aiSkillPowerByLevelFromType[idx] = aiSkillTable;
}

void CTableBySkill::DeleteSkillPowerByLevelFromType(int32_t idx)
{
	if (NULL != m_aiSkillPowerByLevelFromType[idx])
	{
		M2_DELETE_ARRAY(m_aiSkillPowerByLevelFromType[idx]);
		m_aiSkillPowerByLevelFromType[idx] = NULL;
	}
}

int32_t CTableBySkill::GetSkillDamageByLevel( int32_t Level ) const
{
	if ( Level < 0 || Level >= PLAYER_MAX_LEVEL_CONST )
		return 0;

	return m_aiSkillDamageByLevel[Level];
}

void CTableBySkill::SetSkillDamageByLevelTable( const int32_t* aTable )
{
	DeleteSkillDamageByLevelTable();

	int32_t* aiSkillDamageTable = M2_NEW int32_t[PLAYER_MAX_LEVEL_CONST];

	memcpy ( aiSkillDamageTable, aTable, sizeof( int32_t ) * ( PLAYER_MAX_LEVEL_CONST ) );

	m_aiSkillDamageByLevel = aiSkillDamageTable;
}

void CTableBySkill::DeleteSkillDamageByLevelTable()
{
	if (NULL != m_aiSkillDamageByLevel)
	{
		M2_DELETE_ARRAY(m_aiSkillDamageByLevel);
		m_aiSkillDamageByLevel = NULL;
	}
}

