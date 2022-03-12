#ifndef _MEM_H_
#define _MEM_H_

#include <sys/types.h>

void* mem_alloc (size_t sz);
void free_mem (void* mem);

#endif
