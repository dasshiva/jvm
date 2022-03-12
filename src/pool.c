/* File : pool.c
 * Description : contains methods for creating the constant pool
 * Date : 11.3.22
 * Author : Shivashish Das
 */

#include "include/reader.h"
#include "include/pool.h"
#include "include/error.h"
#include "include/mem.h"

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

static void init_utf8(struct CONSTANT_Utf8_info* in, FILE* fptr);
static void init_str(struct CONSTANT_String_info* in, FILE* fptr);
static void init_float(struct CONSTANT_Float_info* in, FILE* fptr);
static void init_int(struct CONSTANT_Integer_info* in, FILE* fptr);
static void init_class(struct CONSTANT_Class_info* in, FILE* fptr);
static void init_methodref(struct CONSTANT_Methodref_info* in, FILE* fptr);
static void init_nameandtype(struct CONSTANT_NameAndType_info* in, FILE* fptr);
static void fill_cp (constant_pool cp, u2_t sz, FILE* fptr);

void init_cp (constant_pool cp , u2_t sz, FILE* fptr) {
	cp = (struct pool_elem*) mem_alloc(sizeof(struct pool_elem) * sz);
	fill_cp(cp,sz,fptr);
}

static void fill_cp (constant_pool cp, u2_t sz, FILE* fptr) {
	u1_t tag;
	for (u2_t curr_index = 0; curr_index < sz ; curr_index++) {
		tag = read_u1(fptr);
		switch (tag) {
			case CONSTANT_Utf8:
				cp[curr_index].tag = tag;
				init_utf8(cp[curr_index].utf,fptr);
				break;
			case CONSTANT_Methodref:
				cp[curr_index].tag = tag;
				init_methodref(cp[curr_index].met,fptr);
				break;
			case CONSTANT_Class:
				cp[curr_index].tag = tag;
				init_class(cp[curr_index].cl,fptr);
				break;
			case CONSTANT_NameAndType:
			    cp[curr_index].tag = tag;
				init_nameandtype(cp[curr_index].nt,fptr);
				break;
			case CONSTANT_String: 
			    cp[curr_index].tag = tag;
				init_str(cp[curr_index].str,fptr);
				break;
			case CONSTANT_Integer: 
			    cp[curr_index].tag = tag;
				init_int(cp[curr_index].num,fptr);
				break;
			case CONSTANT_Float: 
			    cp[curr_index].tag = tag;
				init_float(cp[curr_index].flt,fptr);
				break;
			default: printf("VM error: Unsupported tag : %d",tag); err_exit();
		}
	}
}

static void init_utf8 (utf8_elem* in, FILE* fptr) {
	in = (struct CONSTANT_Utf8_info*) mem_alloc (sizeof(struct CONSTANT_Utf8_info));
	in->len_bytes = read_u2(fptr);
	in->bytes = (u1_t*) mem_alloc(sizeof(u1_t) * in->len_bytes);
	for (int i = 0; i < in->len_bytes; i++) {
		in->bytes[i] = read_u1(fptr);
	}
}

static void init_str(str_elem* in, FILE* fptr) {
	in = (str_elem*) mem_alloc(sizeof (in));
	in->string_index = read_u2(fptr);
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

static void init_int(int_elem* in, FILE* fptr) {
	in = (int_elem*) mem_alloc(sizeof (in));
	in->bytes =  read_u4(fptr);
	in->val = (int) in->bytes;
}

static void init_methodref (met_elem* in, FILE* fptr) {
	in = (met_elem*) mem_alloc(sizeof(met_elem));
	in->cl_index = read_u2(fptr);
	in->nt_index = read_u2(fptr);
}

static void init_class (cl_elem* in, FILE* fptr) {
    in = (cl_elem*) mem_alloc(sizeof(cl_elem));
    in->n_index = read_u2(fptr);
}

static void init_nameandtype(nt_elem* in, FILE* fptr){
	in = (nt_elem*) mem_alloc(sizeof(nt_elem));
	in->n_index = read_u2(fptr);
	in->desc_index = read_u2(fptr);
}
