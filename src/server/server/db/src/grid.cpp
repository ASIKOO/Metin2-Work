#include <string.h>
#include <stdio.h>
#include "../../libthecore/include/memcpy.h"
#include "../../common/stl.h"
#include "grid.h"

CGrid::CGrid(int32_t w, int32_t h) : m_iWidth(w), m_iHeight(h)
{
	m_pGrid = new char[m_iWidth * m_iHeight];
	memset(m_pGrid, 0, sizeof(char) * m_iWidth * m_iHeight);
}

CGrid::CGrid(CGrid * pkGrid, int32_t w, int32_t h) : m_iWidth(w), m_iHeight(h)
{
	m_pGrid = new char[m_iWidth * m_iHeight];
	int32_t iSize = std::MIN(w * h, pkGrid->m_iWidth * pkGrid->m_iHeight);
	thecore_memcpy(m_pGrid, pkGrid->m_pGrid, sizeof(char) * iSize);
}

CGrid::~CGrid()
{
	delete [] m_pGrid;
}

void CGrid::Clear()
{
	memset(m_pGrid, 0, sizeof(char) * m_iWidth * m_iHeight);
}

int32_t CGrid::FindBlank(int32_t w, int32_t h)
{
	// 크기가 더 크다면 확인할 필요 없이 그냥 리턴
	if (w > m_iWidth || h > m_iHeight)
		return -1;

	int32_t iRow;

	for (iRow = 0; iRow < m_iHeight; ++iRow)
	{
		for (int32_t iCol = 0; iCol < m_iWidth; ++iCol)
		{
			int32_t iIndex = iRow * m_iWidth + iCol;

			if (IsEmpty(iIndex, w, h))
				return iIndex;
		}
	}

	return -1;
}

bool CGrid::Put(int32_t iPos, int32_t w, int32_t h)
{
	if (!IsEmpty(iPos, w, h))
		return false;

	for (int32_t y = 0; y < h; ++y)
	{
		int32_t iStart = iPos + (y * m_iWidth);
		m_pGrid[iStart] = true;

		int32_t x = 1;
		while (x < w)
			m_pGrid[iStart + x++] = true;
	}

	return true;
}

void CGrid::Get(int32_t iPos, int32_t w, int32_t h)
{
	if (iPos >= m_iWidth * m_iHeight)
		return;

	for (int32_t y = 0; y < h; ++y)
	{
		int32_t iStart = iPos + (y * m_iWidth);
		m_pGrid[iStart] = false;

		int32_t x = 1;
		while (x < w)
			m_pGrid[iStart + x++] = false;
	}
}

bool CGrid::IsEmpty(int32_t iPos, int32_t w, int32_t h)
{
	int32_t iRow = iPos / m_iWidth;

	// Grid 안쪽인가를 먼저 검사
	if (iRow + h > m_iHeight)
		return false;

	if (iPos + w > iRow * m_iWidth + m_iWidth)
		return false;

	for (int32_t y = 0; y < h; ++y)
	{
		int32_t iStart = iPos + (y * m_iWidth);

		if (m_pGrid[iStart])
			return false;

		int32_t x = 1;
		while (x < w)
			if (m_pGrid[iStart + x++])
				return false;
	}

	return true;
}

void CGrid::Print()
{
	printf("Grid %p\n", this);

	for (int32_t y = 0; y < m_iHeight; ++y)
	{
		for (int32_t x = 0; x < m_iWidth; ++x)
			printf("%d", m_pGrid[y * m_iWidth + x]);

		printf("\n");
	}
}

uint32_t CGrid::GetSize()
{
	return m_iWidth * m_iHeight;
}

