#ifndef __INC_DB_MATRIXCARD_H__
#define __INC_DB_MATRIXCARD_H__

extern bool MatrixCardCheck(const char * src, const char * answer, uint32_t rows, uint32_t cols);
extern void MatrixCardRndCoordinate(uint32_t & rows, uint32_t & cols);

#define MATRIX_CARD_ROW(rows, i) ((rows >> ((4 - i - 1) * 8)) & 0x000000FF)
#define MATRIX_CARD_COL(cols, i) ((cols >> ((4 - i - 1) * 8)) & 0x000000FF)

#endif
