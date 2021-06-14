#ifndef __INC_METIN_II_GUILDLIB_MARK_MANAGER_H__
#define __INC_METIN_II_GUILDLIB_MARK_MANAGER_H__

#include "MarkImage.h"

class CGuildMarkManager : public singleton<CGuildMarkManager>
{
	public:
		enum
		{
			MAX_IMAGE_COUNT = 5,
			INVALID_MARK_ID = 0xffffffff,
		};

		// Symbol
		struct TGuildSymbol
		{
			uint32_t crc;
			std::vector<uint8_t> raw;
		};

		CGuildMarkManager();
		virtual ~CGuildMarkManager();

		const TGuildSymbol * GetGuildSymbol(uint32_t GID);
		bool LoadSymbol(const char* filename);
		void SaveSymbol(const char* filename);
		void UploadSymbol(uint32_t guildID, int32_t iSize, const uint8_t* pbyData);

		//
		// Mark
		//
		void SetMarkPathPrefix(const char * prefix);

		bool LoadMarkIndex(); // 마크 인덱스 불러오기 (서버에서만 사용)
		bool SaveMarkIndex(); // 마크 인덱스 저장하기

		void LoadMarkImages(); // 모든 마크 이미지를 불러오기
		void SaveMarkImage(uint32_t imgIdx); // 마크 이미지 저장

		bool GetMarkImageFilename(uint32_t imgIdx, std::string & path) const;
		bool AddMarkIDByGuildID(uint32_t guildID, uint32_t markID);
		uint32_t GetMarkImageCount() const;
		uint32_t GetMarkCount() const;
		uint32_t GetMarkID(uint32_t guildID);

		// SERVER
		void CopyMarkIdx(char * pcBuf) const;
		uint32_t SaveMark(uint32_t guildID, uint8_t * pbMarkImage);
		void DeleteMark(uint32_t guildID);
		void GetDiffBlocks(uint32_t imgIdx, const uint32_t * crcList, std::map<uint8_t, const SGuildMarkBlock *> & mapDiffBlocks);

		// CLIENT
		bool SaveBlockFromCompressedData(uint32_t imgIdx, uint32_t idBlock, const uint8_t * pbBlock, uint32_t dwSize);
		bool GetBlockCRCList(uint32_t imgIdx, uint32_t * crcList);

	private:
		// 
		// Mark
		//
		CGuildMarkImage * __NewImage();
		void __DeleteImage(CGuildMarkImage * pkImgDel);

		uint32_t __AllocMarkID(uint32_t guildID);

		CGuildMarkImage * __GetImage(uint32_t imgIdx);
		CGuildMarkImage * __GetImagePtr(uint32_t idMark);

		std::map<uint32_t, CGuildMarkImage *> m_mapIdx_Image; // index = image index
		std::map<uint32_t, uint32_t> m_mapGID_MarkID; // index = guild id

		std::set<uint32_t> m_setFreeMarkID;
		std::string		m_pathPrefix;

	private:
		//
		// Symbol
		//
		std::map<uint32_t, TGuildSymbol> m_mapSymbol;
};

#endif
