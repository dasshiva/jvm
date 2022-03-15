#ifndef _ACCESS_H_
#define _ACCESS_H_

#include "types.h"

typedef struct _class_flags { // TODO: Add support for ACC_SUPER
	u1_t ispublic, isfinal;
	u1_t isinterface, isabstract, isenum, isannotation;
	u1_t issynthetic;
} cl_flags;

typedef struct _field_flags {
	u1_t ispublic, isprivate, isprotected, isenum;
	u1_t isvolatile, istransient, isfinal, issynthetic, isstatic;
} fl_flags;

typedef struct _method_flags { // TODO: Add support for ACC_VARARGS
	u1_t ispublic, isprivate, isprotected;
	u1_t isstatic, isfinal, issync, isbridge, isnative, isabstract;
	u1_t issynthetic, isstrict;
} mt_flags;

cl_flags get_class_flags(u2_t);
fl_flags get_field_flags(u2_t);
mt_flags get_method_flags(u2_t);
#endif
