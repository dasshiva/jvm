#include "include/reader.h"

unsigned int swap_endian (u4_t num) {
	unsigned int rmbyte,rbyte,lbyte,lmbyte;
	rmbyte = num & 0x000000ff;
	rbyte = (num & 0x0000ff00) >> 8;
	lbyte = (num & 0x00ff0000) >> 16;
	lmbyte = (num & 0xff000000) >> 24;
	return lmbyte | (lbyte << 8) | (rbyte << 16) | (rmbyte << 24);
}

u8_t read_u8 (FILE* src) {
	u8_t data;
	fread(&data, sizeof(u8_t), 1, src);
	return data;
}

u4_t read_u4 (FILE* src) {
	u4_t data;
        fread(&data, sizeof(u4_t), 1, src);
	data = swap_endian(data);
	return data;
}

u2_t read_u2 (FILE* src) {
	u2_t data;
        fread(&data, sizeof(u2_t), 1, src);
	return data;
}

u1_t read_u1 (FILE* src) {
	u1_t data;
        fread(&data, sizeof(u1_t), 1, src);
	return data;
}

void skip (FILE* src, int n) {
	fseek(src, n, SEEK_CUR);
}
