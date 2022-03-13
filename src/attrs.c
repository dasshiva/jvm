#include "include/attrs.h"
#include "include/reader.h"
#include "include/mem.h"

attrs* create_attr (FILE* fptr) {
	attrs* ret = (attrs*) mem_alloc(sizeof (attrs)); 
	ret->an_index = read_u2(fptr);
	ret->len = read_u4(fptr);
	ret->info = (u1_t*) mem_alloc(sizeof (u1_t) * ret->len);
	for (u4_t i = 0; i < ret->len; i++) {
		ret->info[i] = read_u1(fptr);
	}
	return ret;
}


