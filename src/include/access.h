#ifndef _ACCESS_H_
#define _ACCESS_H_

#include "types.h"

#define FIELD 0x1
#define NOT_FIELD 0x2

typedef struct _flags {
    u1_t ispublic, isprivate, isprotected, isfinal;
    u1_t isinterface, isabstract, isenum, isannotation;
    u1_t isvolatile, istransient, issynthetic;
} flags;

flags get_flags(u2_t, u1_t);
#endif
