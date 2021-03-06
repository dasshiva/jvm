/* File : reader.c
 * Description : contains methods for reading from a .class file
 * Date : 11.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/reader.h"

static u4_t u4_swap_endian (u4_t num) {
	unsigned int rmbyte,rbyte,lbyte,lmbyte;
	rmbyte = num & 0x000000ff;
	rbyte = (num & 0x0000ff00) >> 8;
	lbyte = (num & 0x00ff0000) >> 16;
	lmbyte = (num & 0xff000000) >> 24;
	return lmbyte | (lbyte << 8) | (rbyte << 16) | (rmbyte << 24);
}

static inline u2_t u2_swap_endian (u2_t num) {
	return (num>>8) | (num << 8);
}

u4_t read_u4 (FILE* src) {
	u4_t data;
        fread(&data, sizeof(u4_t), 1, src);
	return u4_swap_endian(data);
}

u2_t read_u2 (FILE* src) {
	u2_t data = 0;
	fread(&data, sizeof(u2_t), 1, src);
	return u2_swap_endian(data);
}

u1_t read_u1 (FILE* src) {
	u1_t data = 0;
	fread(&data, sizeof(u1_t), 1, src);
	return data;
}
