/* File : alloc.c 
 * Descrption : contains methods for managing memory
 * Date : 12.3.22
 * Author : Shivashish Das
 */

#include "include/error.h"
#include "include/mem.h"

#include <stdlib.h>
#include <log.h>
void* alloc (size_t st) {
	void* mem = malloc(st);
	if(!mem) {
		log_stderr(FATAL,"Fatal VM error : Failed to allocate memory of size %d", st);
		exit(1);
	}
	return mem;
}

void free_mem (void* mem) {
	free(mem);
}
