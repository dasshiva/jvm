/* File : pool.c
 * Description : contains methods for creating the constant pool and resolving constant pool indices 
 * Date : 11.3.22
 * Author : Shivashish Das
 */

#include "include/reader.h"
#include "include/pool.h"
#include "include/mem.h"
#include "include/cmdparser.h"

#include <log.h>
#define CONSTANT_Utf8 1
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_Class 7
#define CONSTANT_String 8
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_NameAndType 12
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

static void fill_cp (constant_pool** cp, u2_t sz, FILE* fptr);

void init_cp (constant_pool** cp , u2_t sz, FILE* fptr) {
	*cp = (struct pool_elem*) mem_alloc(sizeof(struct pool_elem) * sz); 
	log_stderr(TRACE, "allocated %d bytes for constant pool",sz * sizeof (struct pool_elem));
	fill_cp(cp,sz,fptr);
}

u1_t* resolve_utf8(constant_pool* cp, u2_t index,u2_t sz) {
	if (index < 1 || index >= sz) return NULL;
	if (cp[index].tag == CONSTANT_Class) {
		if (cp[(cp[index].cl->n_index)].tag == CONSTANT_Utf8) {
			return cp[(cp[index].cl->n_index)].utf->bytes;
		}
	}
	return NULL;
}

static void fill_cp (constant_pool** cp, u2_t sz, FILE* fptr) {
	u1_t tag;
	constant_pool* cp1 = *cp;
	for (u2_t curr_index = 1; curr_index < sz ; curr_index++) {
		tag = read_u1(fptr);
		switch (tag) {
			case CONSTANT_Utf8:
				cp1[curr_index].tag = tag;
				cp1[curr_index].utf = (utf8_elem*) mem_alloc (sizeof(utf8_elem));
				cp1[curr_index].utf->len_bytes = read_u2(fptr);
				cp1[curr_index].utf->bytes = (u1_t*) mem_alloc(sizeof(u1_t) * cp1[curr_index].utf->len_bytes);          
				for (int i = 0; i < cp1[curr_index].utf->len_bytes; i++) { 
					cp1[curr_index].utf->bytes[i] = read_u1(fptr);                                 
				}
				break;
			case CONSTANT_Methodref:
				cp1[curr_index].tag = tag;
				cp1[curr_index].met = (met_elem*) mem_alloc(sizeof (met_elem));
				cp1[curr_index].met->cl_index = read_u2(fptr); 
				cp1[curr_index].met->nt_index = read_u2(fptr);
				break;
			case CONSTANT_Class:
				cp1[curr_index].tag = tag;
				cp1[curr_index].cl = (cl_elem*) mem_alloc(sizeof (cl_elem));
				cp1[curr_index].cl->n_index = read_u2(fptr);
				break;
			case CONSTANT_NameAndType:
				cp1[curr_index].tag = tag;
				cp1[curr_index].nt = (nt_elem*) mem_alloc(sizeof (nt_elem));
				cp1[curr_index].nt->n_index = read_u2(fptr);
				cp1[curr_index].nt->desc_index = read_u2(fptr);
				break;
			case CONSTANT_String: 
				cp1[curr_index].tag = tag;
				cp1[curr_index].str = (str_elem*) mem_alloc(sizeof (str_elem));
				cp1[curr_index].str->string_index = read_u2(fptr);
				break;
			case CONSTANT_Fieldref:
				cp1[curr_index].tag = tag;          
				cp1[curr_index].fld = (fld_elem*) mem_alloc(sizeof (met_elem)); 
				cp1[curr_index].fld->cl_index = read_u2(fptr);
                                cp1[curr_index].fld->nt_index = read_u2(fptr);
                                break;
			/*
			case CONSTANT_Integer:
				cp[curr_index].tag = tag;
				init_int(cp[curr_index].num,fptr);
				break;
			case CONSTANT_Float: 
				cp[curr_index].tag = tag;
				init_float(cp[curr_index].flt,fptr);
				break;
				*/
			default: log_stderr(WARN,"Unsupported tag %d", tag);
		}
	}
}

static void init_float(flt_elem* in, FILE* fptr) {
	in = (flt_elem*) mem_alloc(sizeof (in));
	in->bytes = read_u4(fptr);
	int temp = (int) in->bytes;

	/* copied verbatim from the JVM spec */
	int s = ((temp >> 31) == 0) ? 1 : -1;
	int e = ((temp >> 23) & 0xff);
	int m = (e == 0) ? (temp & 0x7fffff) << 1 : (temp & 0x7fffff) | 0x800000;
	in->val = s * m * 2e-150;
}


