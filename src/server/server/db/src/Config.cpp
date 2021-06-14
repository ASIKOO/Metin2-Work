#include "stdafx.h"
#include "Config.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
	Destroy();
}

void CConfig::Destroy()
{
	m_valueMap.clear();
}

void CConfig::NextLine(FILE *fp)
{
	int32_t c;

	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
			return;
	}
}

bool CConfig::GetWord(FILE *fp, char *tar)
{
	int32_t i = 0;
	int32_t c;

	int32_t semicolon_mode = 0;

	while ((c = fgetc(fp)) != EOF)
	{
		if (c == 13) 
			continue;

		if (semicolon_mode)
		{
			if (c == '"')
			{
				tar[i] = '\0';
				return true;
			}

			tar[i++] = c;
			continue;
		}
		else
		{
			if (i == 0)
			{
				if (c == '"')
				{
					semicolon_mode = 1;
					continue;
				}

				if (c == ' ' || c == '\t' || c == '\n')
				{
					continue;
				}
			}

			if ((c == ' ' || c == '\t' || c == '\n'))
			{
				// ÅÜ.
				tar[i] = '\0';
				return true;
			}

			tar[i] = c;
			++i;
		}
	}

	return (i != 0);
}

bool CConfig::GetLine(FILE* fp, char*dest)
{
	int32_t c;
	int32_t i = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
			return true;
		dest[i] = c;
		++i;
	}
	return true;	
}

bool CConfig::LoadFile(const char* filename)
{
	char 	szTmp[256];
	char 	comment[256];

	FILE *	fp = fopen(filename, "rb");

	if (fp == NULL)
		return false;

	int32_t mode = 0;

	while (GetWord(fp, szTmp))
	{
		if (strcmp(szTmp, "//") == 0)
		{
			NextLine(fp);
			continue;
		}

		switch (mode)
		{
			case 0:
				strlcpy(comment, szTmp, sizeof(comment));
				++mode;
				break;

			case 1:
				if (*szTmp == '=')
					++mode;				
				break;

			case 2:
				mode = 0;
				m_valueMap.insert(TValueMap::value_type(comment, szTmp));
				break;
		}

		// ITEM_ID_RANGE
		if (mode == 2 && strcmp(comment, "ITEM_ID_RANGE") == 0)
		{
			GetLine(fp, szTmp);
			m_valueMap.insert(TValueMap::value_type(comment, szTmp));
			mode = 0;	

		}
		// ITEM_ID_RANGE_END
	}


	// ÆÄÀÏ ´İ´Â ºÎºĞ.
	fclose(fp);
	return true;
}

std::string * CConfig::Search(const char* key)
{
	itertype(m_valueMap) i = m_valueMap.find(key); 

	if (i == m_valueMap.end())
		return NULL;
	else
		return (&i->second);
}

bool CConfig::GetParam(const char*key, int32_t index, uint32_t *Param)
{
	std::string * pstStr = Search(key);
	if (!pstStr)
		return false;

	char szParam[5][32];

	sscanf(pstStr->c_str(), "%s %s %s %s %s", szParam[0],szParam[1],szParam[2],szParam[3],szParam[4]);

	str_to_number(*Param, szParam[index]);

	sys_log(0, "GetParam %d", *Param);
	return true;
}
const char * CConfig::Get(const char* key)
{
	std::string * pstStr = Search(key);

	if (!pstStr)
	{
		static std::string stTemp = "";
		return stTemp.c_str();
	}

	return pstStr->c_str();
}


bool CConfig::GetValue(const char * key, int32_t* dest)
{
	if (!Search(key))
		return false;

	str_to_number(*dest, Get(key));
	return true;
}

bool CConfig::GetValue(const char * key, float *dest)
{ 
	if (!Search(key))
		return false;

	str_to_number(*dest, Get(key));
	return true;
}

bool CConfig::GetValue(const char * key, uint32_t *dest)
{ 
	if (!Search(key))
		return false;

	str_to_number(*dest, Get(key));
	return true;
}

bool CConfig::GetValue(const char * key, uint8_t *dest)
{ 
	if (!Search(key))
		return false;

	*dest = *(uint8_t *) Get(key);
	return true;
}

bool CConfig::GetValue(const char * key, char *dest, uint32_t destSize)
{ 
	if (!Search(key))
		return false;

	strlcpy(dest, Get(key), destSize);

	if (!*dest)
		return false;

	return true;
}

bool CConfig::GetTwoValue(const char* key, uint32_t * dest1, uint32_t *dest2)
{
	if (!GetParam(key, 0, dest1))
		return false;

	if (!GetParam(key, 1, dest2))
		return false;

	return true;
}

