/* File : alloc.c 
 * Descrption : contains methods for managing memory
 * Date : 12.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/error.h"
#include "include/mem.h"

#include <stdlib.h>
#include <log.h>
void* mem_alloc (size_t st) {
	void* mem = malloc(st);
	if(!mem) {
		log_fatal("Failed to allocate memory of size %d", st);
		exit(1);
	}
	return mem;
}

void mem_free (void* mem) {
	free(mem);
}
