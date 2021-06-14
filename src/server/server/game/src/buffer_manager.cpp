#include "stdafx.h"
#include "buffer_manager.h"

TEMP_BUFFER::TEMP_BUFFER(int32_t Size, bool bForceDelete)
{
	forceDelete = bForceDelete;

	if (forceDelete)
		Size = MAX(Size, 1024 * 128);

	buf = buffer_new(Size);
}

TEMP_BUFFER::~TEMP_BUFFER()
{
	buffer_delete(buf);
}

const void * TEMP_BUFFER::read_peek()
{
	return (buffer_read_peek(buf));
}

void TEMP_BUFFER::write(const void * data, int32_t size)
{
	buffer_write(buf, data, size);
}

int32_t TEMP_BUFFER::size()
{
	return buffer_size(buf);
}

void TEMP_BUFFER::reset()
{
	buffer_reset(buf);
}

