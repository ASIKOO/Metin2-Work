#ifndef __INC_METIN_II_GROUP_TEXT_PARSE_TREE_H__
#define __INC_METIN_II_GROUP_TEXT_PARSE_TREE_H__

#include "../../common/d3dtype.h"
#include "../../common/pool.h"
#include "file_loader.h"
#include <sstream>
typedef std::map<std::string, TTokenVector>	TTokenVectorMap;
typedef std::map<std::string, int32_t> TMapNameToIndex;

class CGroupNode
{
public:
	class CGroupNodeRow
	{
	public:
		CGroupNodeRow(CGroupNode* pGroupNode, TTokenVector& vec_values);
		virtual ~CGroupNodeRow();

		template <typename T>
		bool GetValue(const std::string & stColKey, OUT T& value) const;
		template <typename T>
		bool GetValue(int32_t idx, OUT T& value) const;

		int32_t GetSize() const;

	private:
		CGroupNode*		m_pOwnerGroupNode;
		TTokenVector	m_vec_values;
	};
public:
	CGroupNode();
	virtual ~CGroupNode();

	bool Load(const char * c_szFileName);
	const char * GetFileName();

	uint32_t GetChildNodeCount();
	bool SetChildNode(const char * c_szKey, CGroupNode* pChildNode);
	CGroupNode* GetChildNode(const std::string & c_rstrKey) const;
	std::string GetNodeName() const;

	bool IsToken(const std::string & c_rstrKey) const;

	int32_t GetRowCount();
	
	template <typename T>
	bool GetValue(uint32_t i, const std::string & c_rstrColKey, T& tValue) const;	// n번째(map에 들어있는 순서일 뿐, txt의 순서와는 관계 없음) row의 특정 컬럼의 값을 반환하는 함수. 
																				// 이질적이긴 하지만, 편의를 위한 함수.
	template <typename T>
	bool GetValue(const std::string & c_rstrRowKey, const std::string & c_rstrColKey, T& tValue) const;
	template <typename T>
	bool GetValue(const std::string & c_rstrRowKey, int32_t index, T& tValue) const;

	bool GetRow(const std::string & c_rstrKey, OUT const CGroupNodeRow ** ppRow) const;
	// 참고로, idx랑 txt에 쓰여진 순서랑 관계 없음.
	bool GetRow(int32_t idx, OUT const CGroupNodeRow ** ppRow) const;
	bool GetGroupRow(const std::string& stGroupName, const std::string& stRow, OUT const CGroupNode::CGroupNodeRow ** ppRow) const;

	template <typename T>
	bool GetGroupValue(const std::string& stGroupName, const std::string& stRow, int32_t iCol, OUT T& tValue) const;
	template <typename T>
	bool GetGroupValue(const std::string& stGroupName, const std::string& stRow, const std::string& stCol, OUT T& tValue) const;

	int32_t	GetColumnIndexFromName(const std::string& stName) const;

private:
	typedef std::map <std::string, CGroupNode*> TMapGroup;
	typedef std::map <std::string, CGroupNode::CGroupNodeRow> TMapRow;
	TMapGroup				m_mapChildNodes;
	std::string strGroupName;

	TMapNameToIndex			m_map_columnNameToIndex;
	TMapRow					m_map_rows;
	friend class CGroupTextParseTreeLoader;
};

class CGroupTextParseTreeLoader
{
public:
	CGroupTextParseTreeLoader();
	virtual ~CGroupTextParseTreeLoader();

	bool Load(const char * c_szFileName);
	const char * GetFileName();

	CGroupNode*	GetGroup(const char * c_szGroupName);
private:
	bool LoadGroup(CGroupNode * pGroupNode);

	CGroupNode *				m_pRootGroupNode;
	std::string					m_strFileName;
	uint32_t						m_dwcurLineIndex;

	CMemoryTextFileLoader		m_fileLoader;
};

template <typename T>
bool from_string(OUT T& t, IN const std::string& s)
{
	std::istringstream iss(s);
	return !(iss >> t).fail();
}

template <>
inline bool from_string <uint8_t>(OUT uint8_t& t, IN const std::string& s)
{
	std::istringstream iss(s);
	int32_t temp;
	bool b = !(iss >> temp).fail();
	t = (uint8_t)temp;
	return b;
}

template <typename T>
bool CGroupNode::GetValue(uint32_t i, const std::string & c_rstrColKey, T& tValue) const
{
	if (i > m_map_rows.size())
		return FALSE;
	
	TMapRow::const_iterator row_it = m_map_rows.begin();
	std::advance(row_it, i);
	
	itertype(m_map_columnNameToIndex) col_idx_it = m_map_columnNameToIndex.find(c_rstrColKey);
	if (m_map_columnNameToIndex.end() == col_idx_it)
	{
		return FALSE;
	}

	int32_t index = col_idx_it->second;
	if (row_it->second.GetSize() <= index)
	{
		return FALSE;
	}
	
	return row_it->second.GetValue(index, tValue);
}

template <typename T>
bool CGroupNode::GetValue(const std::string & c_rstrRowKey, const std::string & c_rstrColKey, T& tValue) const
{
	TMapRow::const_iterator row_it = m_map_rows.find(c_rstrRowKey);
	if (m_map_rows.end() == row_it)
	{
		return FALSE;
	}
	itertype(m_map_columnNameToIndex) col_idx_it = m_map_columnNameToIndex.find(c_rstrColKey);
	if (m_map_columnNameToIndex.end() == col_idx_it)
	{
		return FALSE;
	}

	int32_t index = col_idx_it->second;
	if (row_it->second.GetSize() <= index)
	{
		return FALSE;
	}
	
	return row_it->second.GetValue(index, tValue);
}

template <typename T>
bool CGroupNode::GetValue(const std::string & c_rstrRowKey, int32_t index, T& tValue) const
{
	TMapRow::const_iterator row_it = m_map_rows.find(c_rstrRowKey);
	if (m_map_rows.end() == row_it)
	{
		return FALSE;
	}

	if (row_it->second.GetSize() <= index)
	{
		return FALSE;
	}
	return row_it->second.GetValue(index, tValue);
}

template <typename T>
bool CGroupNode::GetGroupValue(const std::string& stGroupName, const std::string& stRow, int32_t iCol, OUT T& tValue) const
{
	CGroupNode* pChildGroup = GetChildNode(stGroupName);
	if (NULL != pChildGroup)
	{
		if (pChildGroup->GetValue(stRow, iCol, tValue))
			return true;
	}
	// default group을 살펴봄.
	pChildGroup = GetChildNode("default");
	if (NULL != pChildGroup)
	{
		if (pChildGroup->GetValue(stRow, iCol, tValue))
			return true;
	}
	return false;
}

template <typename T>
bool CGroupNode::GetGroupValue(const std::string& stGroupName, const std::string& stRow, const std::string& stCol, OUT T& tValue) const
{
	CGroupNode* pChildGroup = GetChildNode(stGroupName);
	if (NULL != pChildGroup)
	{
		if (pChildGroup->GetValue(stRow, stCol, tValue))
			return true;
	}
	// default group을 살펴봄.
	pChildGroup = GetChildNode("default");
	if (NULL != pChildGroup)
	{
		if (pChildGroup->GetValue(stRow, stCol, tValue))
			return true;
	}
	return false;
}

template <typename T>
bool CGroupNode::CGroupNodeRow::GetValue(const std::string & stColKey, OUT T& value) const
{
	int32_t idx = m_pOwnerGroupNode->GetColumnIndexFromName(stColKey);
	if (idx < 0 || idx >= m_vec_values.size())
		return false;
	return from_string(value, m_vec_values[idx]);
}

template <typename T>
bool CGroupNode::CGroupNodeRow::GetValue(int32_t idx, OUT T& value) const
{
	if (idx < 0 || idx >= m_vec_values.size())
		return false;
	return from_string(value, m_vec_values[idx]);
}

#endif

