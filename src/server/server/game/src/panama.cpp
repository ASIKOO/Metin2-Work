#include "stdafx.h"
#include "desc.h"
#include "packet.h"

typedef std::vector<std::pair<std::string, uint8_t* > > PanamaVectorType;
static PanamaVectorType s_panamaVector;

uint32_t PanamaLoad()
{
	FILE* fp;

	fp = fopen("panama/panama.lst", "r");

	if (!fp)
		return 0;

	char buf[256];

	while (fgets(buf, 256, fp))
	{
		char szPackName[256];
		char szIVFileName[256];
		char szIVFileNameConfig[256];

		sscanf(buf, " %s %s ", szPackName, szIVFileNameConfig);
		snprintf(szIVFileName, sizeof(szIVFileName), "panama/%s", szIVFileNameConfig);

		FILE * fpIV = fopen(szIVFileName, "rb");

		if (!fpIV)
		{
			sys_err("cannot open iv file %s", szIVFileName);
			continue;
		}

		uint8_t abIV[32];

		if (32 != fread(abIV, sizeof(uint8_t), 32, fpIV))
			sys_err("IV file format error! %s", szIVFileName);
		else
		{
			char szHex[64 + 1];

			for (int32_t i = 0; i < 32; ++i)
				snprintf(szHex + i * 2, sizeof(szHex) - i * 2, "%02x", abIV[i]);

			sys_log(0, "PANAMA: %s %s", szPackName, szHex);

			s_panamaVector.push_back(std::make_pair(szPackName, M2_NEW uint8_t[32]));
			memcpy(s_panamaVector[s_panamaVector.size() - 1].second, abIV, 32);
		}

		fclose(fpIV);
	}

	fclose(fp);
	return s_panamaVector.size();
}

void PanamaDestroy()
{
	PanamaVectorType::iterator it = s_panamaVector.begin();

	while (it != s_panamaVector.end()) {
		M2_DELETE_ARRAY(it->second);
		++it;
	}
}

void SendPanamaList(LPDESC d)
{
	TPacketGCPanamaPack pack;

	pack.bHeader = HEADER_GC_PANAMA_PACK;

	PanamaVectorType::iterator it = s_panamaVector.begin();

	while (it != s_panamaVector.end())
	{
		strlcpy(pack.szPackName, it->first.c_str(), sizeof(pack.szPackName));
		memcpy(pack.abIV, it->second, sizeof(pack.abIV));


		uint32_t* ivs = (uint32_t*)pack.abIV;
		for (int32_t i = 0; i != 32 / sizeof(uint32_t); i++)
		{
			ivs[i] ^= d->GetPanamaKey() + i * 16777619;	// 더블워드단위로 변형된 파나마 키를 XOR 해준다
		}
		++it;

		d->Packet(&pack, sizeof(pack));
	}
}
