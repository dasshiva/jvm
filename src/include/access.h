#ifndef _ACCESS_H_
#define _ACCESS_H_

#include "types.h"
typedef struct class_flags {
    int ispublic, isfinal, isinterface;
    int isabstract, isenum;
} flags;

flags get_flags(u2_t);
#endif