#ifndef _CLASS_H_
#define _CLASS_H_

#include "methods.h"
#include "types.h"
#include "pool.h"
#include "access.h"
#include "fields.h"
#include <stdio.h>

typedef struct _class {
    u4_t magic;
    u2_t minor , major;
    u2_t cp_count;
    constant_pool* cp;
    cl_flags fg;
    u1_t* this_class;
    u1_t* super_class;
    u2_t inters_count;
    u2_t* inters;
    u2_t fields_count;
    fields* fds;
    u2_t meths_count;
    methods* mts;
    u2_t attrs_count;
    class_attrs* cl;
} Java_class;

Java_class* create_class(FILE* fptr);
Java_class* get_classref (u1_t* name);
#endif
