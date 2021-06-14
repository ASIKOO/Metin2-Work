/*********************************************************************
 * date        : 2007.06.07
 * file        : input_teen.cpp
 * author      : mhh
 * description : 
 */

#define _input_teen_cpp_

#include "stdafx.h" 
#include "constants.h"
#include "../../common/teen_packet.h"
#include "input.h"
#include "desc.h"
#include "desc_manager.h"
#include "db.h"
#include "protocol.h"
#include "char.h"
#include "dev_log.h"

#define HANDSHAKE_XOR                  0x6AB3D224

void CInputTeen::SetStep(int32_t step)
{
	m_step = step;
}

bool CInputTeen::Process(LPDESC lpDesc, const void * c_pvOrig, int32_t iBytes, int32_t & r_iBytesProceed)
{
	switch (m_step)
	{
		case 0:
			return this->ProcessHandshake(lpDesc, c_pvOrig, iBytes, r_iBytesProceed);
			break;
		case 1:
			return this->ProcessMain(lpDesc, c_pvOrig, iBytes, r_iBytesProceed);
			break;
	}
	return false;
} /* end of CInputTeen::Process() */

bool CInputTeen::ProcessHandshake(LPDESC lpDesc, const void * c_pvOrig, uint32_t uiBytes, int32_t & r_iBytesProceed)
{
	const char	*c_pData = (const char*) c_pvOrig;
	uint32_t packet_len = sizeof(uint32_t);

	if (uiBytes < packet_len)
		return false;

	uint32_t	handshake	= decode_4bytes(c_pData);

	c_pData			+= packet_len;
	m_iBufferLeft	-= packet_len;
	r_iBytesProceed	+= packet_len;

	this->SetStep(1);

	char buf[256];
	*((uint32_t *) buf) = handshake ^ HANDSHAKE_XOR;
	lpDesc->Packet(buf, sizeof(uint32_t));

	return true;
}


static int32_t __packet_len(uint8_t header)
{
	const int32_t	header_size = sizeof(uint8_t) + sizeof(uint16_t);

	switch (header)
	{
		case HEADER_TG_TEEN_NOTICE:	return (header_size + LOGIN_MAX_LEN + 4);
		case HEADER_TG_FORCE_LOGOUT:	return (header_size + LOGIN_MAX_LEN);
		case HEADER_TG_LOGIN_NOTICE:	return (header_size + LOGIN_MAX_LEN + 4 + 4);
	}
	return 0;
}


static void __proc_teen_notice(char *login, int32_t hour)
{
	LPDESC desc = DESC_MANAGER::instance().FindByLoginName(login);
	if (NULL==desc) return;

	LPCHARACTER		ch = desc->GetCharacter();
	if (NULL==ch)	return;

	switch (hour)
	{
		case 0:
			{
				SET_OVER_TIME(ch, OT_NONE);
				return;
			}
			break;
		case 1:
		case 2:
			{
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 누적 온라인 시간이 이미 %d시간이 지났습니다."), hour);
				SET_OVER_TIME(ch, OT_NONE);
			}
			break;
		case 3:
			{
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 누적 온라인 시간이 이미 %d시간이 되었습니다,"), hour);
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("조속히 접속을 종료하신 후 건강을 위해 휴식을 취해주시기바랍니다."));
				SET_OVER_TIME(ch, OT_3HOUR);
			}
			break;
		case 4:
			{
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신은 이미 게임 피로 상태에 들어섰으며,"));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("게임 내의 수익이 정상치의 50%로 하향됩니다."));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 건강을 위해 조속히 접속을 종료하시고"));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("휴식 및 학업에 열중해주십시오."));
				SET_OVER_TIME(ch, OT_3HOUR);
			}
			break;
		default:
			{
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신은 이미 온전하지 못한 게임 시간에 들어섰습니다."));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("건강을 위해 조속히 접속을 종료하신 후 휴식을 취해주십시오,"));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("그렇지 않으면 건강 상에 피해를 입을 수 있으며 게임 내의 수치는 0이 됩니다."));
				ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("누적 오프라인 시간이 5시간이 되면 정상으로 돌아옵니다."));
				SET_OVER_TIME(ch, OT_5HOUR);
			}
			break;
	}
}

static inline void __sec_to_timestring(int32_t sec, char *buf, uint32_t buflen)
{
	int32_t	hour	= (sec/60)/60;
	int32_t min		= (sec/60);

	if (hour>0)
		snprintf(buf, buflen, LC_TEXT("%d시간"), hour);
	else
		snprintf(buf, buflen, LC_TEXT("%d분"), min);
}

static void __proc_login_notice(char *login, int32_t on_time, int32_t off_time)
{
	//{ check player's name
	LPDESC desc = DESC_MANAGER::instance().FindByLoginName(login);
	if (NULL==desc) return;

	LPCHARACTER		ch = desc->GetCharacter();
	if (NULL==ch)	return;
	//} check player's name

	char	on_time_string[64];
	char	off_time_string[64];

	__sec_to_timestring(on_time, on_time_string, sizeof(on_time_string));
	__sec_to_timestring(off_time, off_time_string, sizeof(off_time_string));

	if (0==on_time)
	{
		ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 누적 오프라인 시간은 %s입니다."), off_time_string);
		ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 누적 온라인 시간은 0이 되었습니다. 100% 효과를 얻으실 수 있습니다."));
		return;
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("당신의 누적 오프라인 시간은 %s이며, 누적 온라인 시간은 %s입니다."),
				off_time_string, on_time_string);
	}
}


static void __input_teen(uint8_t header, uint16_t desc_num, char *body)
{
	switch (header)
	{
		case HEADER_TG_FORCE_LOGOUT:
			{
				char	*data = body;
				char	login[LOGIN_MAX_LEN+1] = {0};
				memcpy(login, data, LOGIN_MAX_LEN);
				data += LOGIN_MAX_LEN;
				LPDESC d = DESC_MANAGER::instance().FindByLoginName(login);

				if (NULL==d)
					return;

				d->SetPhase(PHASE_CLOSE);
			}
			break;
		case HEADER_TG_TEEN_NOTICE:
			{
				char	*data = body;
				char	login[LOGIN_MAX_LEN+1] = {0};
				memcpy(login, data, LOGIN_MAX_LEN);
				data += LOGIN_MAX_LEN;
				int32_t	hour = decode_4bytes(data);
				data += 4;

				__proc_teen_notice(login, hour);
			}
			break;
		case HEADER_TG_LOGIN_NOTICE:
			{
				char	*data = body;
				char	login[LOGIN_MAX_LEN+1] = {0};
				memcpy(login, data, LOGIN_MAX_LEN);
				data += LOGIN_MAX_LEN;
				int32_t		on_time = decode_4bytes(data);
				data += 4;
				int32_t		off_time = decode_4bytes(data);
				data += 4;

				__proc_login_notice(login, on_time, off_time);
			}
			break;
	}
}


bool CInputTeen::ProcessMain(LPDESC lpDesc, const void * c_pvOrig, uint32_t uiBytes, int32_t & r_iBytesProceed)
{
	const char	*c_pData = (const char*) c_pvOrig;
	const uint32_t header_size = sizeof(uint8_t) + sizeof(uint16_t);

	if (uiBytes < header_size)
		return false;

	for (m_iBufferLeft = uiBytes; m_iBufferLeft > 0;)
	{
		uint8_t header		= decode_byte(c_pData);
		uint16_t desc_num	= decode_2bytes(c_pData+sizeof(uint8_t));
		char *body		= (char*) c_pData + header_size;

		int32_t packet_len	= __packet_len(header);

		if (m_iBufferLeft < packet_len)
			return true;

		c_pData			+= packet_len;
		m_iBufferLeft	-= packet_len;
		r_iBytesProceed	+= packet_len;

		__input_teen(header, desc_num, body);
	}	

	return true;
}

