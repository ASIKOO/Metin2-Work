#include "stdafx.h"
#include "empire_text_convert.h"

namespace 
{
	struct STextConvertTable 
	{
		char acUpper[26];
		char acLower[26];
		uint8_t aacHan[5000][2];
		uint8_t aacJaum[50][2];
		uint8_t aacMoum[50][2];
	} g_aTextConvTable[3];
}

bool LoadEmpireTextConvertTable(uint32_t dwEmpireID, const char* c_szFileName)
{
	if (dwEmpireID < 1 || dwEmpireID > 3)
		return false;

	FILE * fp = fopen(c_szFileName, "rb");

	if (!fp)
		return false;

	uint32_t dwEngCount = 26;
	uint32_t dwHanCount = (0xC8 - 0xB0+1) * (0xFE - 0xA1+1);
	uint32_t dwHanSize = dwHanCount * 2;

	STextConvertTable& rkTextConvTable=g_aTextConvTable[dwEmpireID-1];

	fread(rkTextConvTable.acUpper, 1, dwEngCount, fp);
	fread(rkTextConvTable.acLower, 1, dwEngCount, fp);
	fread(rkTextConvTable.aacHan, 1, dwHanSize, fp);

	fread(rkTextConvTable.aacJaum, 1, 60, fp);
	fread(rkTextConvTable.aacMoum, 1, 42, fp);

	fclose(fp);

	return true;
}

void ConvertEmpireText(uint32_t dwEmpireID, char* szText, uint32_t len, int32_t iPct)
{
	if (dwEmpireID < 1 || dwEmpireID > 3 || len == 0)
		return;

	const STextConvertTable& rkTextConvTable = g_aTextConvTable[dwEmpireID - 1];

	for (uint8_t* pbText = reinterpret_cast<uint8_t*>(szText) ; len > 0 && *pbText != '\0' ; --len, ++pbText)
	{
		if (number(1,100) > iPct)
		{
			if (*pbText & 0x80)
			{
				if (g_iUseLocale)
				{
					static char s_cChinaTable[][3] = {"¡ò","££","£¤","¡ù","¡ð" };
					int32_t n = number(0, 4);
					pbText[0] = s_cChinaTable[n][0];
					pbText[1] = s_cChinaTable[n][1];
				}
				else
				{
					if (pbText[0] >= 0xB0 && pbText[0] <= 0xC8 && pbText[1] >= 0xA1 && pbText[1] <= 0xFE)
					{
						UINT uHanPos = (pbText[0] - 0xB0) * (0xFE - 0xA1 + 1) + (pbText[1] - 0xA1);
						pbText[0] = rkTextConvTable.aacHan[uHanPos][0];
						pbText[1] = rkTextConvTable.aacHan[uHanPos][1];
					}
					else if ( pbText[0] == 0xA4 )
					{
						if ( pbText[1] >=0xA1 && pbText[1] <= 0xBE )
						{
							pbText[0] = rkTextConvTable.aacJaum[pbText[1]-0xA1][0];
							pbText[1] = rkTextConvTable.aacJaum[pbText[1]-0xA1][1];
						}
						else if ( pbText[1] >= 0xBF && pbText[1] <= 0xD3 )
						{
							pbText[0] = rkTextConvTable.aacMoum[pbText[1]-0xBF][0];
							pbText[1] = rkTextConvTable.aacMoum[pbText[1]-0xBF][1];
						}
					}
				}

				++pbText;
				--len;
			}
			else
			{
				if (*pbText >= 'a' && *pbText <= 'z')
				{
					*pbText = rkTextConvTable.acLower[*pbText - 'a'];
				}
				else if (*pbText >= 'A' && *pbText <= 'Z')
				{
					*pbText = rkTextConvTable.acUpper[*pbText - 'A'];
				}
			}
		}
		else
		{
			if (*pbText & 0x80)
			{
				++pbText;
				--len;
			}
		}
	}
}

