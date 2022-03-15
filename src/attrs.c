/* File : attrs.c
 * Descrption : contains a method for creating attributes
 * Date : 14.3.22
 * Author : Shivashish Das
 */

#include "include/attrs.h"
#include "include/resolve.h"
#include "include/reader.h"
#include "include/mem.h"

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
	for (int i = 0; i < total_attrs; i++) {
		
	}
	return met;
}
