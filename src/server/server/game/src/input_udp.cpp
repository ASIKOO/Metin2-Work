#include "stdafx.h"
#include "constants.h"
#include "config.h"
#include "input.h"
#include "desc.h"
#include "desc_manager.h"
#include "item_manager.h"
#include "char_manager.h"
#include "protocol.h"

extern socket_t udp_socket;

#define HEADER_CG_STATE_CHECKER	1

#pragma pack(1)

typedef uint32_t ServerStateChecker_Key;
typedef uint32_t ServerStateChecker_Index;
typedef uint8_t ServerStateChecker_State;

struct ServerStateChecker_RequestPacket
{
	uint8_t header;
	ServerStateChecker_Key key;	
	ServerStateChecker_Index index;
};

struct ServerStateChecker_ResponsePacket
{
	uint8_t header;
	ServerStateChecker_Key key;
	ServerStateChecker_Index index;
	ServerStateChecker_State state;
};

#pragma pack()

///---------------------------------------------------------

CPacketInfoUDP::CPacketInfoUDP()
{
	Set(1, sizeof(ServerStateChecker_RequestPacket), "ServerStateRequest", false);
}

CPacketInfoUDP::~CPacketInfoUDP()
{
	Log("udp_packet_info.txt");
}


CInputUDP::CInputUDP()
{
	memset( &m_SockAddr, 0, sizeof(m_SockAddr) );

	BindPacketInfo(&m_packetInfoUDP);
}   

void CInputUDP::Handshake(LPDESC pDesc, const char * c_pData)
{
	TPacketCGHandshake * pInfo = (TPacketCGHandshake *) c_pData;

	if (pDesc->GetHandshake() == pInfo->dwHandshake)
	{
		sys_log(0, "UDP: Grant %s:%d", inet_ntoa(m_SockAddr.sin_addr), m_SockAddr.sin_port);
		pDesc->UDPGrant(m_SockAddr);
		return;
	}
	else
		sys_log(0, "UDP: Handshake differs %s", pDesc->GetHostName());
}

void CInputUDP::StateChecker(const char * c_pData)
{
	// NOTE : TCP 연결로 바꾸면서 사용 X
	/*
	struct ServerStateChecker_RequestPacket * p = (struct ServerStateChecker_RequestPacket *) c_pData;
	ServerStateChecker_ResponsePacket rp;

	int32_t iTotal; 
	int32_t * paiEmpireUserCount;
	int32_t iLocal;

	DESC_MANAGER::instance().GetUserCount(iTotal, &paiEmpireUserCount, iLocal);

	rp.header	= 1; 
	rp.key	= p->key;
	rp.index	= p->index;

	if (g_bNoMoreClient)
		rp.state = 0;
	else
		rp.state = iTotal > g_iFullUserCount ? 3 : iTotal > g_iBusyUserCount ? 2 : 1;

	if (sendto(udp_socket, (const char*)&rp, sizeof(rp), 0, (const struct sockaddr *) &m_SockAddr, sizeof(m_SockAddr)) < 0)
	{
		sys_err("cannot sendto datagram socket : %s, %d", inet_ntoa(m_SockAddr.sin_addr), inet_ntoa(m_SockAddr.sin_addr));
		return;
	}
	*/
}

int32_t CInputUDP::Analyze(LPDESC pDesc, uint8_t bHeader, const char * c_pData)
{
	switch (bHeader)
	{
		/*
		case HEADER_CG_HANDSHAKE:
		   Handshake(pDesc, c_pData);
		   break;

		case HEADER_CG_STATE_CHECKER:
			StateChecker(c_pData);
			break;
		*/

		default:
			sys_err("unknown UDP header %u", bHeader);
			break;
	}

	return 0;
}

bool CInputUDP::Process(LPDESC pDesc, const void * c_pvOrig, int32_t iBytes, int32_t & r_iBytesProceed)
{
	/*
	const char * c_pData = static_cast<const char *> (c_pvOrig);

	uint8_t        bLastHeader = 0;
	int32_t         iLastPacketLen = 0;
	int32_t         iPacketLen;

	if (!m_pPacketInfo)
	{
		sys_err("No packet info has been binded to");
		return true;
	}

	for (m_iBufferLeft = iBytes; m_iBufferLeft > 0;)
	{
		if (m_iBufferLeft < 5)
			return true;

		uint8_t bHeader = (uint8_t) *(c_pData);
		const char * c_pszName;

		if (!m_pPacketInfo->Get(bHeader, &iPacketLen, &c_pszName))
		{
			sys_err("UNKNOWN HEADER: %d, LAST HEADER: %d(%d), REMAIN BYTES: %d",
					bHeader, bLastHeader, iLastPacketLen, m_iBufferLeft);
			//printdata((uint8_t *) c_pvOrig, iBytes);
			return true;
		}
		
		//uint32_t dwHandshake = *(uint32_t *) (c_pData + 1);
		//pDesc = DESC_MANAGER::instance().FindByHandshake(dwHandshake);

		//if (!pDesc)
		//{
		//sys_err("No desc by handshake %u", dwHandshake);
		//return true;
		//}

		//if (m_SockAddr.sin_addr.s_addr != pDesc->GetAddr().sin_addr.s_addr)
		//{
		//sys_err("Hostname Mismatch! %s != %s", inet_ntoa(m_SockAddr.sin_addr), pDesc->GetHostName());
		//return true;
		//}
		
		if (m_iBufferLeft < iPacketLen)
			return true;

		int32_t iExtraPacketSize = Analyze(pDesc, bHeader, c_pData);

		if (iExtraPacketSize < 0)
			return true;

		iPacketLen      += iExtraPacketSize;

		c_pData         += iPacketLen;
		m_iBufferLeft   -= iPacketLen;
		r_iBytesProceed += iPacketLen;

		iLastPacketLen  = iPacketLen;
		bLastHeader     = bHeader;

		//if (GetType() != pDesc->GetInputProcessor()->GetType())
		//return false;
	}

	*/
	return true;
}

