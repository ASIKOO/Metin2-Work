#include "stdafx.h"
#include "MarkImage.h"

#include "crc32.h"
#include "lzo_manager.h"
#define CLZO LZOManager

CGuildMarkImage * NewMarkImage()
{
	return M2_NEW CGuildMarkImage;
}

void DeleteMarkImage(CGuildMarkImage * pkImage)
{
	M2_DELETE(pkImage);
}

CGuildMarkImage::CGuildMarkImage()
	: m_uImg(INVALID_HANDLE)
{
	memset( &m_apxImage, 0, sizeof(m_apxImage) );
}

CGuildMarkImage::~CGuildMarkImage()
{
	Destroy();
}

void CGuildMarkImage::Destroy()
{
	if (INVALID_HANDLE == m_uImg)
		return;

	ilDeleteImages(1, &m_uImg);
	m_uImg = INVALID_HANDLE;
}

void CGuildMarkImage::Create()
{
	if (INVALID_HANDLE != m_uImg)
		return;

	ilGenImages(1, &m_uImg);
}

bool CGuildMarkImage::Save(const char* c_szFileName) 
{
	ilEnable(IL_FILE_OVERWRITE);
	ilBindImage(m_uImg);

	if (!ilSave(IL_TGA, (const ILstring)c_szFileName))
		return false;

	return true;
}

bool CGuildMarkImage::Build(const char * c_szFileName)
{
	sys_log(0, "GuildMarkImage: creating new file %s", c_szFileName);

	Destroy();
	Create();

	ilBindImage(m_uImg);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	uint8_t * data = (uint8_t *) malloc(sizeof(Pixel) * WIDTH * HEIGHT);
	memset(data, 0, sizeof(Pixel) * WIDTH * HEIGHT);

	if (!ilTexImage(WIDTH, HEIGHT, 1, 4, IL_BGRA, IL_UNSIGNED_BYTE, data))
	{
		sys_err("GuildMarkImage: cannot initialize image");
		return false;
	}

	free(data);

	ilEnable(IL_FILE_OVERWRITE);

	if (!ilSave(IL_TGA, (const ILstring)c_szFileName))
		return false;

	return true;
}

bool CGuildMarkImage::Load(const char * c_szFileName) 
{
	Destroy();
	Create();	

	ilBindImage(m_uImg);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	if (!ilLoad(IL_TYPE_UNKNOWN, (const ILstring) c_szFileName))
	{
		sys_err("GuildMarkImage: %s cannot open file.", c_szFileName);
		return false;
	}

	if (ilGetInteger(IL_IMAGE_WIDTH) != WIDTH)	
	{
		sys_err("GuildMarkImage: %s width must be %u", c_szFileName, WIDTH);
		return false;
	}

	if (ilGetInteger(IL_IMAGE_HEIGHT) != HEIGHT)
	{
		sys_err("GuildMarkImage: %s height must be %u", c_szFileName, HEIGHT);
		return false;
	}

	ilConvertImage(IL_BGRA, IL_UNSIGNED_BYTE);

	BuildAllBlocks();
	return true;
}

void CGuildMarkImage::PutData(UINT x, UINT y, UINT width, UINT height, void * data)
{
	ilBindImage(m_uImg);
	ilSetPixels(x, y, 0, width, height, 1, IL_BGRA, IL_UNSIGNED_BYTE, data);
}

void CGuildMarkImage::GetData(UINT x, UINT y, UINT width, UINT height, void * data)
{
	ilBindImage(m_uImg);
	ilCopyPixels(x, y, 0, width, height, 1, IL_BGRA, IL_UNSIGNED_BYTE, data);	
}

// 이미지 = 512x512
//   블럭 = 마크 4 x 4
//   마크 = 16 x 12
// 한 이미지의 블럭 = 8 x 10

// SERVER
bool CGuildMarkImage::SaveMark(uint32_t posMark, uint8_t * pbImage)
{
	if (posMark >= MARK_TOTAL_COUNT)
	{
		sys_err("GuildMarkImage::CopyMarkFromData: Invalid mark position %u", posMark);
		return false;
	}

	// 마크를 전체 이미지에 그린다.
	uint32_t colMark = posMark % MARK_COL_COUNT;
	uint32_t rowMark = posMark / MARK_COL_COUNT;

	printf("PutMark pos %u %ux%u\n", posMark, colMark * SGuildMark::WIDTH, rowMark * SGuildMark::HEIGHT);
	PutData(colMark * SGuildMark::WIDTH, rowMark * SGuildMark::HEIGHT, SGuildMark::WIDTH, SGuildMark::HEIGHT, pbImage);

	// 그려진 곳의 블럭을 업데이트
	uint32_t rowBlock = rowMark / SGuildMarkBlock::MARK_PER_BLOCK_HEIGHT;
	uint32_t colBlock = colMark / SGuildMarkBlock::MARK_PER_BLOCK_WIDTH;

	Pixel apxBuf[SGuildMarkBlock::SIZE];
	GetData(colBlock * SGuildMarkBlock::WIDTH, rowBlock * SGuildMarkBlock::HEIGHT, SGuildMarkBlock::WIDTH, SGuildMarkBlock::HEIGHT, apxBuf);
	m_aakBlock[rowBlock][colBlock].Compress(apxBuf);
	return true;
}

bool CGuildMarkImage::DeleteMark(uint32_t posMark)
{
	Pixel image[SGuildMark::SIZE];
	memset(&image, 0, sizeof(image));
	return SaveMark(posMark, (uint8_t *) &image);
}

// CLIENT
bool CGuildMarkImage::SaveBlockFromCompressedData(uint32_t posBlock, const uint8_t * pbComp, uint32_t dwCompSize)
{
	if (posBlock >= BLOCK_TOTAL_COUNT)
		return false;

	Pixel apxBuf[SGuildMarkBlock::SIZE];
	lzo_uint sizeBuf = sizeof(apxBuf);

	if (LZO_E_OK != lzo1x_decompress_safe(pbComp, dwCompSize, (uint8_t *) apxBuf, &sizeBuf, CLZO::Instance().GetWorkMemory()))
	{
		sys_err("GuildMarkImage::CopyBlockFromCompressedData: cannot decompress, compressed size = %u", dwCompSize);
		return false;
	}

	if (sizeBuf != sizeof(apxBuf))
	{
		sys_err("GuildMarkImage::CopyBlockFromCompressedData: image corrupted, decompressed size = %u", sizeBuf);
		return false;
	}

	uint32_t rowBlock = posBlock / BLOCK_COL_COUNT;
	uint32_t colBlock = posBlock % BLOCK_COL_COUNT;

	PutData(colBlock * SGuildMarkBlock::WIDTH, rowBlock * SGuildMarkBlock::HEIGHT, SGuildMarkBlock::WIDTH, SGuildMarkBlock::HEIGHT, apxBuf);

	m_aakBlock[rowBlock][colBlock].CopyFrom(pbComp, dwCompSize, GetCRC32((const char *) apxBuf, sizeof(Pixel) * SGuildMarkBlock::SIZE));
	return true;
}

void CGuildMarkImage::BuildAllBlocks() // 이미지 전체를 블럭화
{
	Pixel apxBuf[SGuildMarkBlock::SIZE];
	sys_log(0, "GuildMarkImage::BuildAllBlocks");

	for (UINT row = 0; row < BLOCK_ROW_COUNT; ++row)
		for (UINT col = 0; col < BLOCK_COL_COUNT; ++col)
		{
			GetData(col * SGuildMarkBlock::WIDTH, row * SGuildMarkBlock::HEIGHT, SGuildMarkBlock::WIDTH, SGuildMarkBlock::HEIGHT, apxBuf);
			m_aakBlock[row][col].Compress(apxBuf);
		}
}

uint32_t CGuildMarkImage::GetEmptyPosition()
{
	SGuildMark kMark;

	for (uint32_t row = 0; row < MARK_ROW_COUNT; ++row)
	{
		for (uint32_t col = 0; col < MARK_COL_COUNT; ++col)
		{
			GetData(col * SGuildMark::WIDTH, row * SGuildMark::HEIGHT, SGuildMark::WIDTH, SGuildMark::HEIGHT, kMark.m_apxBuf);

			if (kMark.IsEmpty())
				return (row * MARK_COL_COUNT + col);
		}
	}

	return INVALID_MARK_POSITION;
}

void CGuildMarkImage::GetDiffBlocks(const uint32_t * crcList, std::map<uint8_t, const SGuildMarkBlock *> & mapDiffBlocks)
{
	uint8_t posBlock = 0;

	for (uint32_t row = 0; row < BLOCK_ROW_COUNT; ++row)
		for (uint32_t col = 0; col < BLOCK_COL_COUNT; ++col)
		{
			if (m_aakBlock[row][col].m_crc != *crcList)
			{
				mapDiffBlocks.insert(std::map<uint8_t, const SGuildMarkBlock *>::value_type(posBlock, &m_aakBlock[row][col]));
			}
			++crcList;
			++posBlock;
		}
}

void CGuildMarkImage::GetBlockCRCList(uint32_t * crcList)
{
	for (uint32_t row = 0; row < BLOCK_ROW_COUNT; ++row)
		for (uint32_t col = 0; col < BLOCK_COL_COUNT; ++col)
			*(crcList++) = m_aakBlock[row][col].GetCRC();
}

////////////////////////////////////////////////////////////////////////////////
void SGuildMark::Clear()
{
	for (uint32_t iPixel = 0; iPixel < SIZE; ++iPixel)
		m_apxBuf[iPixel] = 0xff000000;	
}

bool SGuildMark::IsEmpty()
{
	for (uint32_t iPixel = 0; iPixel < SIZE; ++iPixel)
		if (m_apxBuf[iPixel] != 0x00000000)
			return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
uint32_t SGuildMarkBlock::GetCRC() const
{
	return m_crc;
}

void SGuildMarkBlock::CopyFrom(const uint8_t * pbCompBuf, uint32_t dwCompSize, uint32_t crc)
{
	if (dwCompSize > MAX_COMP_SIZE)
		return;

	m_sizeCompBuf = dwCompSize;
	thecore_memcpy(m_abCompBuf, pbCompBuf, dwCompSize);
	m_crc = crc;
	//printf("SGuildMarkBlock::CopyFrom: %u > %u crc %u\n", sizeof(Pixel) * SGuildMarkBlock::SIZE, m_sizeCompBuf, m_crc);
}

void SGuildMarkBlock::Compress(const Pixel * pxBuf)
{
	m_sizeCompBuf = MAX_COMP_SIZE;

	if (LZO_E_OK != lzo1x_1_compress((const uint8_t *) pxBuf, sizeof(Pixel) * SGuildMarkBlock::SIZE, m_abCompBuf, &m_sizeCompBuf, CLZO::Instance().GetWorkMemory()))
	{
		sys_err("SGuildMarkBlock::Compress: Error! %u > %u", sizeof(Pixel) * SGuildMarkBlock::SIZE, m_sizeCompBuf);
		return;
	}

	//sys_log(0, "SGuildMarkBlock::Compress %u > %u", sizeof(Pixel) * SGuildMarkBlock::SIZE, m_sizeCompBuf);
	m_crc = GetCRC32((const char *) pxBuf, sizeof(Pixel) * SGuildMarkBlock::SIZE);
}
