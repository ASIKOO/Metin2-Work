#ifndef __INC_METIN_II_DRAGON_SOUL_TABLE_H__
#define __INC_METIN_II_DRAGON_SOUL_TABLE_H__

struct SApply
{
	SApply (EApplyTypes at, int32_t av, float p = 0.f) : apply_type(at), apply_value(av), prob(p) {}
	EApplyTypes apply_type;
	int32_t apply_value;
	float prob;
};
const int32_t DRAGON_SOUL_ADDITIONAL_ATTR_START_IDX = 3;

class CGroupNode;
class CGroupTextParseTreeLoader;

class DragonSoulTable
{
public:
	DragonSoulTable();
	~DragonSoulTable();
	typedef std::vector <SApply> TVecApplys;
	typedef std::map <uint8_t, TVecApplys> TMapApplyGroup;
	
	bool	ReadDragonSoulTableFile(const char * c_pszFileName);
	bool	GetDragonSoulGroupName(uint8_t bType, std::string& stGroupName) const;

	bool	GetBasicApplys(uint8_t ds_type, OUT TVecApplys& vec_basic_applys);
	bool	GetAdditionalApplys(uint8_t ds_type, OUT TVecApplys& vec_additional_attrs);

	bool	GetApplyNumSettings(uint8_t ds_type, uint8_t grade_idx, OUT int32_t& basis, OUT int32_t& add_min, OUT int32_t& add_max);
	bool	GetWeight(uint8_t ds_type, uint8_t grade_idx, uint8_t step_index, uint8_t strength_idx, OUT float& fWeight);
	bool	GetRefineGradeValues(uint8_t ds_type, uint8_t grade_idx, OUT int32_t& need_count, OUT int32_t& fee, OUT std::vector<float>& vec_probs);
	bool	GetRefineStepValues(uint8_t ds_type, uint8_t step_idx, OUT int32_t& need_count, OUT int32_t& fee, OUT std::vector<float>& vec_probs);
	bool	GetRefineStrengthValues(uint8_t ds_type, uint8_t material_type, uint8_t strength_idx, OUT int32_t& fee, OUT float& prob);
	bool	GetDragonHeartExtValues(uint8_t ds_type, uint8_t grade_idx, OUT std::vector<float>& vec_chargings, OUT std::vector<float>& vec_probs);
	bool	GetDragonSoulExtValues(uint8_t ds_type, uint8_t grade_idx, OUT float& prob, OUT uint32_t& by_product);

private:
	CGroupTextParseTreeLoader* m_pLoader;
	std::string stFileName;

	// caching m_pLoader's child nodes.
	CGroupNode*	m_pApplyNumSettingNode;
	CGroupNode*	m_pWeightTableNode;
	CGroupNode*	m_pRefineGradeTableNode;
	CGroupNode*	m_pRefineStepTableNode;
	CGroupNode*	m_pRefineStrengthTableNode;
	CGroupNode*	m_pDragonHeartExtTableNode;
	CGroupNode*	m_pDragonSoulExtTableNode;

	typedef std::map <std::string, uint8_t> TMapNameToType;
	typedef std::map <uint8_t, std::string> TMapTypeToName;
	std::vector <std::string> m_vecDragonSoulNames;
	std::vector <uint8_t> m_vecDragonSoulTypes;

	TMapNameToType m_map_name_to_type;
	TMapTypeToName m_map_type_to_name;
	TMapApplyGroup m_map_basic_applys_group;
	TMapApplyGroup m_map_additional_applys_group;

	bool	ReadVnumMapper();
	bool	ReadBasicApplys();
	bool	ReadAdditionalApplys();
	// table check functions.
	bool	CheckApplyNumSettings();
	bool	CheckWeightTables();
	bool	CheckRefineGradeTables();
	bool	CheckRefineStepTables();
	bool	CheckRefineStrengthTables();
	bool	CheckDragonHeartExtTables();
	bool	CheckDragonSoulExtTables();
};

#endif