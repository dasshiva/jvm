/* File : methods.c
 * Description : contains methods for creating and managing methods
 * Date : 15.3.22
 * Author : Shivashish Das
 */

#include "include/methods.h"
#include "include/mem.h"
#include "include/reader.h"

static void fill_methods(methods**, u2_t, FILE*);

void init_methods(methods** mt, u2_t sz, FILE* fptr) {
	*mt = (methods*) mem_alloc(sizeof (methods) * sz);
	fill_methods(mt,sz,fptr);
}

static void fill_methods(methods** mt, u2_t sz, FILE* fptr) {
	methods* m = *mt;
	for (int i = 0; i < sz; i++) {
		m[i].acc = get_method_flags(read_u2(fptr));
		m[i].n_index = read_u2(fptr);
		m[i].desc_index = read_u2(fptr);
		m[i].attr = create_attr(fptr);
	}
}


