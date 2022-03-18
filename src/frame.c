/* File : frame.c
 * Descrption : contains methods for creating and destroying frames
 * Date : 18.3.22
 * Author : dasshiva
 * License : MIT License (Look at the LICENSE file for more details) 
 */

#include "include/frame.h"
#include "include/mem.h"
#include "include/resolve.h"

static frame* new_frame(constant_pool** cp, code_attr* cd) {
	frame* ret = (frame*) mem_alloc(sizeof (frame));
	ret->pc = 0;
	ret->tab = mem_alloc (sizeof (f_args) * cd->max_locals);
	ret->stack = mem_alloc (sizeof (struct f_stack));
	ret->stack->top = 0;
	ret->stack->op = mem_alloc(sizeof (f_args) * cd->max_stack);
	ret->cp = *cp;
	ret->code = cd;
	return ret;
}

frame* get_frame(const char* name, const char* desc, Java_class* jc){
	for (u2_t i = 1; i <= jc->meths_count; i++) {
		if (strcmp(name, resolve_utf8(&jc->cp, jc->mts[i].n_index)) == 0) {
			if (strcmp(desc, resolve_utf8(&jc->cp,jc->mts[i].desc_index)) == 0) 
				return new_frame(&jc->cp, jc->mts[i].attr->code);
		}
	}
        return NULL;           
}

void destroy_frame (frame** f) {
	mem_free((*f)->stack->op);
	mem_free((*f)->stack);
	mem_free((*f)->tab);
	mem_free(*f);
	*f = NULL;
}
