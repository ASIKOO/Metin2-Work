
#ifndef HACK_SHIELD_IMPL_H_
#define HACK_SHIELD_IMPL_H_

#include <boost/unordered_map.hpp>

#ifdef __FreeBSD__
// Live build only
#define UNIX
#include <AntiCpXSvr.h>
#undef UNIX
#endif

#pragma pack(1)

typedef struct SPacketGCHSCheck
{
	uint8_t	bHeader;
#ifdef __FreeBSD__
	AHNHS_TRANS_BUFFER Req;
#endif
} TPacketGCHSCheck;

#pragma pack()

class CHackShieldImpl
{
	public:
		bool Initialize ();
		void Release ();

		bool CreateClientHandle (uint32_t dwPlayerID);
		void DeleteClientHandle (uint32_t dwPlayerID);

		bool SendCheckPacket (LPCHARACTER ch);
		bool VerifyAck (LPCHARACTER ch, TPacketGCHSCheck* buf);

	private:
#ifdef __FreeBSD__
		AHNHS_SERVER_HANDLE handle_;

		typedef boost::unordered_map<uint32_t, AHNHS_CLIENT_HANDLE> ClientHandleContainer;
		ClientHandleContainer CliehtHandleMap_;

		typedef boost::unordered_map<uint32_t, bool> ClientCheckContainer;
		ClientCheckContainer ClientCheckMap_;
#endif
};

#endif /* HACK_SHIELD_IMPL_H_ */

