#include "include/resolve.h"

u1_t* resolve_utf8(constant_pool** cp, u2_t index) {
	constant_pool* c = *cp;
	if (c[index].tag == CONSTANT_Utf8) 
		return c[index].utf->bytes;
	else {
		switch (c[index].tag) {
			case CONSTANT_Class:
			return c[c[index].cl->n_index].utf->bytes;
			default: return NULL;
		}
	}
}

