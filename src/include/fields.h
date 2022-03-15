#ifndef _FIELDS_H_
#define _FIELDS_H_

#include "types.h"
#include "attrs.h"
#include "access.h"
#include <stdio.h>

typedef struct _field {
	fl_flags acc;
	u2_t n_index;
	u2_t desc_index;
	field_attrs* attr;
} fields;

void init_fields(fields** fd, u2_t sz, FILE* fptr);
#endif
