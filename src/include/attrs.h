#ifndef _ATTRS_H_
#define _ATTRS_H_

#include "types.h"
#include "pool.h"
#include <stdio.h>

typedef struct {
    u2_t attribute_name_index;
    u4_t attribute_length;
    u2_t max_stack;
    u2_t max_locals;
    u4_t code_length;
    u1_t* code;
    u2_t exception_table_length;
    u2_t attributes_count;
} code_attr;

typedef struct {
    u2_t attribute_name_index;
    u4_t attribute_length;
    u2_t line_number_table_length;
    struct __line_tab {   
        u2_t start_pc;
        u2_t line_number;	
    } *line_num_table;
} line_num_table_attr;

typedef struct {
    code_attr* code;
    line_num_table_attr* lt;
} method_attrs; 

typedef struct {
    u2_t an_index;
    u4_t len;
    u1_t* info;
} field_attrs;

field_attrs* get_field_attr (FILE* fptr);
method_attrs* get_method_attr (FILE* fptr, constant_pool**, u2_t);

#endif
