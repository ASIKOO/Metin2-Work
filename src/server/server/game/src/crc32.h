#ifndef __INC_CRC32_H__
#define __INC_CRC32_H__

typedef uint32_t crc_t;

crc_t	GetCRC32(const char * buffer, uint32_t count);
crc_t	GetCaseCRC32(const char * buffer, uint32_t count);
crc_t	GetFastHash(const char * key, uint32_t len);

/*#define CRC32(buf) GetCRC32(buf, strlen(buf))
#define CRC32CASE(buf) GetCaseCRC32(buf, strlen(buf))*/

#endif
