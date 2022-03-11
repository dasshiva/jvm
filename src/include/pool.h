#ifndef _POOL_H_
#define _POOL_H_

#include "types.h"
#include <stdio.h>

typedef struct CONSTANT_Utf8_info {
	u2_t len_bytes;
	u1_t* bytes;
} utf8_elem;

typedef struct CONSTANT_Integer_info {
    u4_t bytes;
	int val;
} int_elem;

typedef struct CONSTANT_Float_info {
    u4_t bytes;
    float val;
} flt_elem;

typedef struct CONSTANT_String_info {
    u2_t string_index;
} str_elem;

typedef struct CONSTANT_Class_info {
	u2_t n_index;
} cl_elem;

typedef struct CONSTANT_Methodref_info {
	u2_t cl_index;
	u2_t nt_index;
} met_elem;

typedef struct CONSTANT_NameAndType_info {
    u2_t n_index;
    u2_t desc_index;
} nt_elem;

struct pool_elem {
	u1_t tag;
	utf8_elem* utf;
	int_elem* num;
	flt_elem* flt;
	met_elem* met;
	cl_elem* cl;
	nt_elem* nt;
    str_elem* str;
};

typedef struct pool_elem* constant_pool;
void init_cp (constant_pool cp, u2_t sz, FILE* fptr);
#endif
