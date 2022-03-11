#ifndef _READER_H_
#define _READER_H_

#include <stdio.h>
#include "types.h"

u8_t read_u8(FILE *src);
u4_t read_u4(FILE *src);
u2_t read_u2(FILE *src);
u1_t read_u1(FILE *src);
void skip(FILE* src, int n);
#endif
