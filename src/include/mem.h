#ifndef _MEM_H_
#define _MEM_H_

#include <sys/types.h>

void* mem_alloc (size_t sz);
void mem_realloc(void* mem, size_t sz);
void mem_free (void* mem);

#endif
