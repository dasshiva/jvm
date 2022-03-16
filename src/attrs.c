/* File : attrs.c
 * Descrption : contains  method for creating attributes
 * Date : 14.3.22
 * Author : Shivashish Das
 */

#include "include/attrs.h"
#include "include/resolve.h"
#include "include/reader.h"
#include "include/mem.h"
#include <string.h>
#include <log.h>

field_attrs* get_field_attr (FILE* fptr) {
	field_attrs* ret = (field_attrs*) mem_alloc(sizeof (field_attrs)); 
	ret->an_index = read_u2(fptr);
	ret->len = read_u4(fptr);
	ret->info = (u1_t*) mem_alloc(sizeof (u1_t) * ret->len);
	for (u4_t i = 0; i < ret->len; i++) {
		ret->info[i] = read_u1(fptr);
	}
	return ret;
}

method_attrs* get_method_attr(FILE* fptr, constant_pool** cp, u2_t total_attrs) {
	method_attrs* met = (method_attrs*) mem_alloc(sizeof (method_attrs) * total_attrs);
	u1_t* attr_name = NULL;
	for (int i = 0; i < total_attrs; i++){
		attr_name = resolve_utf8(cp,read_u2(fptr));
		if (strcmp("Code",attr_name) == 0) {
			met->have_code = 1;
			met->code = (code_attr*) mem_alloc(sizeof (code_attr));
			met->code->len = read_u4(fptr);
			met->code->max_stack = read_u2(fptr);
			met->code->max_locals = read_u2(fptr);
			met->code->code_len = read_u4(fptr);
			met->code->code = (u1_t*) mem_alloc (sizeof (u1_t) * met->code->code_len);
			for (u4_t i = 0; i < met->code->code_len; i++){
				met->code->code[i] = read_u1(fptr);
			}
			met->code->except_table_len = read_u2(fptr);
			if (met->code->except_table_len != 0)
				log_stderr(FATAL, "Exceptions are not supported for now");
			met->code->attrs_count = read_u2(fptr);
			met->code->attr_info = (struct _at_info*) mem_alloc(sizeof (struct _at_info));
			for (int i = 0; i < met->code->attrs_count; i++) {
				attr_name = resolve_utf8(cp,read_u2(fptr));
				if (strcmp("LineNumberTable", attr_name) == 0) {
					met->code->attr_info->have_tab = 1;
					met->code->attr_info->lt = (line_num_table_attr*) mem_alloc(sizeof (line_num_table_attr));
					met->code->attr_info->lt->attr_len = read_u4(fptr);
					met->code->attr_info->lt->tab_len = read_u2(fptr);
					met->code->attr_info->lt->line_num_table = (struct __line_tab*) mem_alloc (sizeof (struct __line_tab) * met->code->attr_info->lt->tab_len);
					for (int i = 0; i < met->code->attr_info->lt->tab_len; i++) {
						met->code->attr_info->lt->line_num_table[i].start_pc = read_u2(fptr);
						met->code->attr_info->lt->line_num_table[i].ln_no = read_u2(fptr);
					}

				}
				/* TODO: It is against the JVM spec for any JVM implementation to complain 
				 * when it does not recognize an attribute so we have to support 
				 * ignoring unknown (or unsupported) attributes as soon as possible */
				else
					log_stderr(FATAL, "Code attribute %s not supported yet", attr_name);
			}
		}
		else log_stderr (FATAL, "Attribute %s is not supported yet", attr_name);
	}
	return met;
}
