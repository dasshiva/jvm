#ifndef _METHODS_H_
#define _METHODS_H_

#include "types.h"
#include "attrs.h"
#include "access.h"
#include "pool.h"
#include <stdio.h>

typedef struct _method {
	mt_flags acc;
	u2_t n_index;
	u2_t desc_index;
	method_attrs* attr;
} methods;

void init_methods(methods** fd, u2_t sz, FILE* fptr, constant_pool** cp);
#endif
