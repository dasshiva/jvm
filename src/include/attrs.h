#ifndef _ATTRS_H_
#define _ATTRS_H_

#include "types.h"
#include "pool.h"
#include <stdio.h>

typedef struct {
    u4_t attr_len;
    u2_t tab_len;
    struct __line_tab {   
        u2_t start_pc;
        u2_t ln_no;	
    } *line_num_table;
} line_num_table_attr;

typedef struct {
    u4_t len;                                                             
    u2_t max_stack;
    u2_t max_locals;
    u4_t code_len;
    u1_t* code;
    u2_t except_table_len;
    u2_t attrs_count;
    struct _at_info {
	    u1_t have_tab;
	    line_num_table_attr* lt;
    } *attr_info;
} code_attr;

typedef struct {
	u1_t have_code;
	code_attr* code;
} method_attrs; 

typedef struct {
    u2_t an_index;
    u4_t len;
    u1_t* info;
} field_attrs;

field_attrs* get_field_attr (FILE* fptr);
method_attrs* get_method_attr (FILE* fptr, constant_pool**, u2_t);

#endif
