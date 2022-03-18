/* File : methods.c
 * Description : contains methods for creating and managing methods
 * Date : 15.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/methods.h"
#include "include/mem.h"
#include "include/reader.h"
#include "include/resolve.h"
#include <log.h>

static void fill_methods(methods**, u2_t, FILE*);

void init_methods(methods** mt, u2_t sz, FILE* fptr, constant_pool** cp) {
	*mt = (methods*) mem_alloc(sizeof (methods) * sz);
	methods* m = *mt;
	for (int i = 1; i <= sz; i++) {
		m[i].acc = get_method_flags(read_u2(fptr));
		m[i].n_index = read_u2(fptr);
		m[i].desc_index = read_u2(fptr);
		m[i].attr = get_method_attr(fptr,cp, read_u2(fptr));
		log_trace("Registered function %s", resolve_utf8(cp,m[i].n_index));
	}
}
