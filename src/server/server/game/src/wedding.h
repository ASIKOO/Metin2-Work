#ifndef __WEDDING_H
#define __WEDDING_H

#include "marriage.h"

namespace marriage
{
	const uint32_t WEDDING_MAP_INDEX = 81;
	typedef CHARACTER_SET charset_t;

	class WeddingMap
	{
		public:
			WeddingMap(uint32_t dwMapIndex, uint32_t dwPID1, uint32_t dwPID2);
			~WeddingMap();

			uint32_t GetMapIndex() { return m_dwMapIndex; }

			void WarpAll();
			void DestroyAll();
			void Notice(const char* psz);
			void SetEnded();

			void IncMember(LPCHARACTER ch);
			void DecMember(LPCHARACTER ch);
			bool IsMember(LPCHARACTER ch );

			void SetDark(bool bSet);
			void SetSnow(bool bSet);
			void SetMusic(bool bSet, const char* szMusicFileName);

			bool IsPlayingMusic();

			void SendLocalEvent(LPCHARACTER ch);

			void ShoutInMap(uint8_t type, const char* szMsg);
		private:

			const char* __BuildCommandPlayMusic(char* szCommand, uint32_t nCmdLen, uint8_t bSet, const char* c_szMusicFileName); 

		private:
			uint32_t m_dwMapIndex;
			LPEVENT m_pEndEvent;
			charset_t m_set_pkChr;

			bool m_isDark;
			bool m_isSnow;
			bool m_isMusic;

			uint32_t dwPID1;
			uint32_t dwPID2;

			std::string m_stMusicFileName;
	};

	class WeddingManager : public singleton<WeddingManager>
	{
		public:
			WeddingManager();
			virtual ~WeddingManager();

			bool IsWeddingMap(uint32_t dwMapIndex);

			void Request(uint32_t dwPID1, uint32_t dwPID2);
			bool End(uint32_t dwMapIndex);

			void DestroyWeddingMap(WeddingMap* pMap);

			WeddingMap* Find(uint32_t dwMapIndex);

		private:
			uint32_t __CreateWeddingMap(uint32_t dwPID1, uint32_t dwPID2);

		private:

			std::map<uint32_t, WeddingMap*> m_mapWedding;
	};
}
#endif
