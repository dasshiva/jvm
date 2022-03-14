#ifndef _ATTRS_H_
#define _ATTRS_H_

#include "types.h"
#include <stdio.h>
typedef struct __attr {
    u2_t an_index;
    u4_t len;
    u1_t* info;
} attrs; 

attrs* create_attr (FILE* fptr);
#endif
