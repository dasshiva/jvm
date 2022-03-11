#include "include/reader.h"
#include "include/pool.h"
#include "include/error.h"

#include <stdlib.h>

struct CONSTANT_Utf8_info {
	u2_t len_bytes;
	u1_t* bytes;
};
static void init_utf8(struct CONSTANT_Utf8_info* in, FILE* fptr);

struct CONSTANT_Integer_info {
    u4_t bytes;
};

struct CONSTANT_Float_info {
    u4_t bytes;
    float val;
};

struct CONSTANT_Class_info {
	u2_t n_index;
};
static void init_class(struct CONSTANT_Class_info* in, FILE* fptr);

struct CONSTANT_Methodref_info {
	u2_t cl_index;
	u2_t nt_index;
};
static void init_methodref(struct CONSTANT_Methodref_info* in, FILE* fptr);

struct pool_elem {
	u1_t tag;
	utf8_elem* utf;
	int_elem* num;
	flt_elem* flt;
	met_elem* met;
	cl_elem* cl;
};

static struct pool_elem *cp = NULL;
static int curr_index = 0, max_sz;
void init_cp (u2_t sz) {
	max_sz = sz;
	cp = (struct pool_elem*) malloc(sizeof(struct pool_elem) * sz);
}

void fill_cp (FILE* fptr) {
	u1_t tag;
	for (; curr_index < max_sz ; curr_index++) {
		tag = read_u1(fptr);
		switch (tag) {
			case CONSTANT_Utf8:
				cp[curr_index].tag = tag;
				init_utf8(cp[curr_index].utf,fptr);
				break;
			case CONSTANT_Methodref:
				cp[curr_index].tag = tag;
				init_methodref(cp[curr_index].met,fptr);
			case CONSTANT_Class:
				cp[curr_index].tag = tag;
				init_class(cp[curr_index].cl,fptr);
			case CONSTANT_String: break;
			case CONSTANT_Integer: break;
			case CONSTANT_Float: break;
			default: printf("VM error: Unsupported tag : %d",tag); err_exit();
		}
		curr_index++;
	}
}

static void init_utf8 (utf8_elem* in, FILE* fptr) {
	in = (struct CONSTANT_Utf8_info*) malloc (sizeof(struct CONSTANT_Utf8_info));
	in->len_bytes = read_u2(fptr);
	in->bytes = (u1_t*) malloc(sizeof(u1_t) * in->len_bytes);
	for (int i = 0; i < in->len_bytes; i++) {
		in->bytes[i] = read_u1(fptr);
	}
}

static void init_methodref (met_elem* in, FILE* fptr) {
	in = (met_elem*) malloc(sizeof(met_elem));
	in->cl_index = read_u2(fptr);
	in->nt_index = read_u2(fptr);
}

static void init_class (cl_elem* in, FILE* fptr) {
        in = (cl_elem*) malloc(sizeof(cl_elem));
        in->n_index = read_u2(fptr);
}
