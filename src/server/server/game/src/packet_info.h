#ifndef __INC_METIN_II_GAME_PACKET_HEADER_INFO_H__
#define __INC_METIN_II_GAME_PACKET_HEADER_INFO_H__

#include "packet.h"

typedef struct SPacketElement
{
	int32_t		iSize;
	std::string	stName;
	int32_t		iCalled;
	uint32_t	dwLoad;
	bool	bSequencePacket;
} TPacketElement;

class CPacketInfo
{
	public:
		CPacketInfo();
		virtual ~CPacketInfo();

		void Set(int32_t header, int32_t size, const char * c_pszName, bool bSeq=false);
		bool Get(int32_t header, int32_t * size, const char ** c_ppszName);

		void Start();
		void End();

		void Log(const char * c_pszFileName);

		bool IsSequence(int32_t header);
		void SetSequence(int32_t header, bool bSeq);

	private:
		TPacketElement * GetElement(int32_t header);

	protected:
		std::map<int32_t, TPacketElement *> m_pPacketMap;
		TPacketElement * m_pCurrentPacket;
		uint32_t m_dwStartTime;
};

class CPacketInfoCG : public CPacketInfo
{
	public:
		CPacketInfoCG();
		virtual ~CPacketInfoCG();
};

// PacketInfo P2P 
class CPacketInfoGG : public CPacketInfo
{
	public:
		CPacketInfoGG();
		virtual ~CPacketInfoGG();
};

/// Implemented in input_udp.cpp
class CPacketInfoUDP : public CPacketInfo
{
	public:
		CPacketInfoUDP();
		virtual ~CPacketInfoUDP();
};

#endif
