/* File : methods.c
 * Description : contains methods for creating and managing methods
 * Date : 15.3.22
 * Author : Shivashish Das
 */

#include "include/methods.h"
#include "include/mem.h"
#include "include/reader.h"
#include "include/resolve.h"
#include <log.h>

static void fill_methods(methods**, u2_t, FILE*);

void init_methods(methods** mt, u2_t sz, FILE* fptr, constant_pool** cp) {
	methods* m = *mt;
	m = (methods*) mem_alloc(sizeof (methods) * sz);
	for (int i = 1; i <= sz; i++) {
		m[i].acc = get_method_flags(read_u2(fptr));
		m[i].n_index = read_u2(fptr);
		log_stderr(TRACE,"Registered function %s", resolve_utf8(cp,m[i].n_index));
		m[i].desc_index = read_u2(fptr);
		m[i].attr = get_method_attr(fptr,cp, read_u2(fptr));
	}
}


