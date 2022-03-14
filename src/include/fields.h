#ifndef _FIELDS_H_
#define _FIELDS_H_

#include "types.h"
#include "attrs.h"

typedef struct _field {
	u2_t acc;
	u2_t n_index;
	u2_t desc_index;
	attrs* attr;
} fileds;
