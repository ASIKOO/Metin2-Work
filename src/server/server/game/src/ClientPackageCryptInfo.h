#ifndef __INC_CLIENTPACKAGE_CRYPTINFO_H
#define __INC_CLIENTPACKAGE_CRYPTINFO_H

#include <boost/unordered_map.hpp>

#pragma pack(1)

typedef struct SSupplementaryDataBlockInfo
{
	uint32_t				dwPackageIdentifier;
	uint32_t				dwFileIdentifier;
	std::vector<uint8_t>	vecSDBStream;

	void Serialize( uint8_t* pStream )
	{
		memcpy(pStream,   &dwPackageIdentifier, sizeof(uint32_t));
		memcpy(pStream+4, &dwFileIdentifier,    sizeof(uint32_t));

		uint8_t bSize = vecSDBStream.size();
		memcpy(pStream+8, &bSize,  sizeof(uint8_t));
		memcpy(pStream+9, &vecSDBStream[0], bSize);
	}

	uint32_t GetSerializedSize() const
	{
		return sizeof(uint32_t)*2 + sizeof(uint8_t) + vecSDBStream.size();
	}

} TSupplementaryDataBlockInfo;

#pragma pack()

class CClientPackageCryptInfo
{
public:
	CClientPackageCryptInfo();
	~CClientPackageCryptInfo();

	bool LoadPackageCryptInfo( const char* pCryptInfoDir );
	void GetPackageCryptKeys( uint8_t** ppData, int32_t& iDataSize );

	bool GetRelatedMapSDBStreams(const char* pMapName, uint8_t** ppData, int32_t& iDataSize );

private:
	bool LoadPackageCryptFile( const char* pCryptFile );

private:
	int32_t				  m_nCryptKeyPackageCnt;
	std::vector<uint8_t> m_vecPackageCryptKeys;
	uint8_t*			  m_pSerializedCryptKeyStream;

	typedef struct SPerFileSDBInfo
	{
		SPerFileSDBInfo() : m_pSerializedStream(NULL) {}
		~SPerFileSDBInfo()
		{
			if(m_pSerializedStream)
			{
				delete[]m_pSerializedStream;
			}
		}

		uint32_t GetSize() const
		{
			uint32_t dwSize = 4; //initial vecSDBInfo count

			for(int32_t i = 0; i < (int32_t)vecSDBInfos.size(); ++i)
			{
				dwSize += vecSDBInfos[i].GetSerializedSize();
			}

			return dwSize;
		}

		uint8_t* GetSerializedStream()
		{
			//NOTE : SDB Data isn`t updated during runtime. ( in case of file reloading all data is cleared & recreated )
			//it`s not safe but due to performance benefit we don`t do re-serialize.
			if(m_pSerializedStream)
				return m_pSerializedStream;

			m_pSerializedStream = new uint8_t[GetSize()];

			int32_t iWrittenOffset = 0;
			int32_t iSDBInfoSize   = vecSDBInfos.size();

			//write size 
			memcpy( m_pSerializedStream, &iSDBInfoSize, sizeof(int32_t) );
			iWrittenOffset += sizeof(int32_t);
			for(int32_t i = 0; i < iSDBInfoSize; ++i)
			{
				vecSDBInfos[i].Serialize( m_pSerializedStream + iWrittenOffset );
				iWrittenOffset += vecSDBInfos[i].GetSerializedSize();
			}

			return m_pSerializedStream;
		}

		std::vector<TSupplementaryDataBlockInfo> vecSDBInfos;

	private:
		uint8_t* m_pSerializedStream;

	} TPerFileSDBInfo;

	typedef boost::unordered_map<std::string, TPerFileSDBInfo > TPackageSDBMap;	//key: related map name
	TPackageSDBMap	  m_mapPackageSDB;


};






#endif //__INC_CLIENTPACKAGE_CRYPTINFO_H