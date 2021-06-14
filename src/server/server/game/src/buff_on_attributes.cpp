#include "stdafx.h"
#include "../../common/tables.h"
#include "item.h"
#include "char.h"
#include "buff_on_attributes.h"
#include <algorithm>

CBuffOnAttributes::CBuffOnAttributes(LPCHARACTER pOwner, uint8_t point_type, std::vector <uint8_t>* p_vec_buff_wear_targets)
:	m_pBuffOwner(pOwner), m_bPointType(point_type), m_p_vec_buff_wear_targets(p_vec_buff_wear_targets)
{
	Initialize();
}

CBuffOnAttributes::~CBuffOnAttributes()
{
	Off();
}

void CBuffOnAttributes::Initialize()
{
	m_bBuffValue = 0;
	m_map_additional_attrs.clear();
}

void CBuffOnAttributes::RemoveBuffFromItem(LPITEM pItem)
{
	if (0 == m_bBuffValue)
		return ;
	if (NULL != pItem)
	{
		if (pItem->GetCell() < INVENTORY_MAX_NUM)
			return;
		std::vector <uint8_t>::iterator it = find (m_p_vec_buff_wear_targets->begin(), m_p_vec_buff_wear_targets->end(), pItem->GetCell() - INVENTORY_MAX_NUM);
		if (m_p_vec_buff_wear_targets->end() == it)
			return;

		int32_t m = pItem->GetAttributeCount();
		for (int32_t j = 0; j < m; j++)
		{
			TPlayerItemAttribute attr = pItem->GetAttribute(j);
			TMapAttr::iterator it = m_map_additional_attrs.find(attr.bType);
			// m_map_additional_attrs에서 해당 attribute type에 대한 값을 제거하고,
			// 변경된 값의 (m_bBuffValue)%만큼의 버프 효과 감소
			if (it != m_map_additional_attrs.end())
			{
				int32_t& sum_of_attr_value = it->second;
				int32_t old_value = sum_of_attr_value * m_bBuffValue / 100;
				int32_t new_value = (sum_of_attr_value - attr.sValue) * m_bBuffValue / 100;
				m_pBuffOwner->ApplyPoint(attr.bType, new_value - old_value);
				sum_of_attr_value -= attr.sValue;
			}
			else
			{
				sys_err ("Buff ERROR(type %d). This item(%d) attr_type(%d) was not in buff pool", m_bPointType, pItem->GetVnum(), attr.bType);
				return;
			}
		}
	}
}

void CBuffOnAttributes::AddBuffFromItem(LPITEM pItem)
{
	if (0 == m_bBuffValue)
		return ;
	if (NULL != pItem)
	{
		if (pItem->GetCell() < INVENTORY_MAX_NUM)
			return;
		std::vector <uint8_t>::iterator it = find (m_p_vec_buff_wear_targets->begin(), m_p_vec_buff_wear_targets->end(), pItem->GetCell() - INVENTORY_MAX_NUM);
		if (m_p_vec_buff_wear_targets->end() == it)
			return;

		int32_t m = pItem->GetAttributeCount();
		for (int32_t j = 0; j < m; j++)
		{
			TPlayerItemAttribute attr = pItem->GetAttribute(j);
			TMapAttr::iterator it = m_map_additional_attrs.find(attr.bType);
			
			// m_map_additional_attrs에서 해당 attribute type에 대한 값이 없다면 추가.
			// 추가된 값의 (m_bBuffValue)%만큼의 버프 효과 추가
			if (it == m_map_additional_attrs.end())
			{
				m_pBuffOwner->ApplyPoint(attr.bType, attr.sValue * m_bBuffValue / 100);
				m_map_additional_attrs.insert(TMapAttr::value_type(attr.bType, attr.sValue));
			}
			// m_map_additional_attrs에서 해당 attribute type에 대한 값이 있다면, 그 값을 증가시키고,
			// 변경된 값의 (m_bBuffValue)%만큼의 버프 효과 추가
			else
			{
				int32_t& sum_of_attr_value = it->second;
				int32_t old_value = sum_of_attr_value * m_bBuffValue / 100;
				int32_t new_value = (sum_of_attr_value + attr.sValue) * m_bBuffValue / 100;
				m_pBuffOwner->ApplyPoint(attr.bType, new_value - old_value);
				sum_of_attr_value += attr.sValue;
			}
		}
	}
}

void CBuffOnAttributes::ChangeBuffValue(uint8_t bNewValue)
{
	if (0 == m_bBuffValue)
		On(bNewValue);
	else if (0 == bNewValue)
		Off();
	else
	{
		// 기존에, m_map_additional_attrs의 값의 (m_bBuffValue)%만큼이 버프로 들어가 있었으므로,
		// (bNewValue)%만큼으로 값을 변경함.
		for (TMapAttr::iterator it = m_map_additional_attrs.begin(); it != m_map_additional_attrs.end(); it++)
		{
			int32_t& sum_of_attr_value = it->second;
			int32_t old_value = sum_of_attr_value * m_bBuffValue / 100;
			int32_t new_value = sum_of_attr_value * bNewValue / 100;
			
			m_pBuffOwner->ApplyPoint(it->first, -sum_of_attr_value * m_bBuffValue / 100);
		}
		m_bBuffValue = bNewValue;
	}
}

void CBuffOnAttributes::GiveAllAttributes()
{
	if (0 == m_bBuffValue)
		return;
	for (TMapAttr::iterator it = m_map_additional_attrs.begin(); it != m_map_additional_attrs.end(); it++)
	{
		uint8_t apply_type = it->first;
		int32_t apply_value = it->second * m_bBuffValue / 100;
		
		m_pBuffOwner->ApplyPoint(apply_type, apply_value);
	}
}

bool CBuffOnAttributes::On(uint8_t bValue)
{
	if (0 != m_bBuffValue || 0 == bValue)
		return false;
	
	int32_t n = m_p_vec_buff_wear_targets->size();
	m_map_additional_attrs.clear();
	for (int32_t i = 0; i < n; i++)
	{
		LPITEM pItem = m_pBuffOwner->GetWear(m_p_vec_buff_wear_targets->at(i));
		if (NULL != pItem)
		{
			int32_t m = pItem->GetAttributeCount();
			for (int32_t j = 0; j < m; j++)
			{
				TPlayerItemAttribute attr = pItem->GetAttribute(j);
				TMapAttr::iterator it = m_map_additional_attrs.find(attr.bType);
				if (it != m_map_additional_attrs.end())
				{
					it->second += attr.sValue;
				}
				else
				{
					m_map_additional_attrs.insert(TMapAttr::value_type(attr.bType, attr.sValue));
				}
			}
		}
	}

	for (TMapAttr::iterator it = m_map_additional_attrs.begin(); it != m_map_additional_attrs.end(); it++)
	{
		m_pBuffOwner->ApplyPoint(it->first, it->second * bValue / 100);
	}
	
	m_bBuffValue = bValue;

	return true;
}

void CBuffOnAttributes::Off()
{
	if (0 == m_bBuffValue)
		return ;

	for (TMapAttr::iterator it = m_map_additional_attrs.begin(); it != m_map_additional_attrs.end(); it++)
	{
		m_pBuffOwner->ApplyPoint(it->first, -it->second * m_bBuffValue / 100);
	}
	Initialize();
}
