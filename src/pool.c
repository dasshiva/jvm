/* File : pool.c
 * Description : contains methods for creating the constant pool and resolving constant pool indices 
 * Date : 11.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/reader.h"
#include "include/pool.h"
#include "include/mem.h"
#include "include/cmdparser.h"

#include <log.h>

static void fill_cp (constant_pool** cp, u2_t sz, FILE* fptr);
static float init_float(u4_t flt);

void init_cp (constant_pool** cp , u2_t sz, FILE* fptr) {
	*cp = (struct pool_elem*) mem_alloc(sizeof(struct pool_elem) * sz); 
	log_trace( "allocated %d bytes for constant pool",sz * sizeof (struct pool_elem));
	fill_cp(cp,sz,fptr);
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
			case CONSTANT_Integer:
				cp1[curr_index].tag = tag;
				cp1[curr_index].num = (int_elem*) mem_alloc(sizeof (int_elem));
				cp1[curr_index].num->val = (int) read_u4(fptr);
				break;
			case CONSTANT_Float: 
				cp1[curr_index].tag = tag;
				cp1[curr_index].flt = (flt_elem*) mem_alloc(sizeof (flt_elem));
				cp1[curr_index].flt->val = init_float(read_u4(fptr));
				break;
			default: log_warn("Unsupported tag %d", tag);
		}
	}
}

static float init_float(u4_t flt){
	int temp = (int) flt;

	/* copied verbatim from the JVM spec */
	int s = ((temp >> 31) == 0) ? 1 : -1;
	int e = ((temp >> 23) & 0xff);
	int m = (e == 0) ? (temp & 0x7fffff) << 1 : (temp & 0x7fffff) | 0x800000;
	return s * m * 2e-150;
}


