#ifndef __INC_LZO_MANAGER_H
#define __INC_LZO_MANAGER_H

#include "minilzo.h"

class LZOManager : public singleton<LZOManager>
{
	public:
		LZOManager();
		virtual ~LZOManager();

		bool	Compress(const uint8_t* src, uint32_t srcsize, uint8_t* dest, lzo_uint * puiDestSize);
		bool	Decompress(const uint8_t* src, uint32_t srcsize, uint8_t* dest, lzo_uint * puiDestSize);
		uint32_t	GetMaxCompressedSize(uint32_t original);

		uint8_t *	GetWorkMemory() { return m_workmem; }

	private:
		uint8_t *	m_workmem;
};

#endif
