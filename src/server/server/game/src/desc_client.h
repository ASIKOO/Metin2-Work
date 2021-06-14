#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "desc.h"

class CLIENT_DESC : public DESC
{
	public:
		CLIENT_DESC();
		virtual ~CLIENT_DESC();

		virtual uint8_t	GetType() { return DESC_TYPE_CONNECTOR; }
		virtual void	Destroy();
		virtual void	SetPhase(int32_t phase);

		bool 		Connect(int32_t iPhaseWhenSucceed = 0);
		void		Setup(LPFDWATCH _fdw, const char * _host, uint16_t _port);

		void		SetRetryWhenClosed(bool);

		void		DBPacketHeader(uint8_t bHeader, uint32_t dwHandle, uint32_t dwSize);
		void		DBPacket(uint8_t bHeader, uint32_t dwHandle, const void * c_pvData, uint32_t dwSize);
		void		Packet(const void * c_pvData, int32_t iSize);
		bool		IsRetryWhenClosed();

		void		Update(uint32_t t);
		void		UpdateChannelStatus(uint32_t t, bool fForce);

		// Non-destructive close for reuse
		void Reset();

	private:
		void InitializeBuffers();

	protected:
		int32_t			m_iPhaseWhenSucceed;
		bool		m_bRetryWhenClosed;
		int32_t		m_LastTryToConnectTime;
		int32_t		m_tLastChannelStatusUpdateTime;

		CInputDB 	m_inputDB;
		CInputP2P 	m_inputP2P;
		CInputTeen	m_inputTeen;
};


extern LPCLIENT_DESC db_clientdesc;
extern LPCLIENT_DESC g_pkAuthMasterDesc;
extern LPCLIENT_DESC g_NetmarbleDBDesc;
extern LPCLIENT_DESC g_TeenDesc;
extern LPCLIENT_DESC g_PasspodDesc;

#endif
