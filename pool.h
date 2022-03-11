#ifndef _POOL_H_
#define _POOL_H_

#include "types.h"

/* we don't include stdio.h here just for the FILE struct 
 * because the compiler doesn't need to see the struct
 * definition when we declare it as a function paramter
 * in fill_cp(). Instead we include it in pool.c (indirectly from reader.h)
 * where other functions from stdio.h are actually needed.
 */

#define CONSTANT_Utf8 1
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_CLASS 7
#define CONSTANT_String 8
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_NameAndType 12
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

typedef struct CONSTANT_Utf8_info utf8_elem;
typedef struct CONSTANT_Integer_info int_elem;
typedef struct CONSTANT_Float_info flt_elem;
typedef struct CONSTANT_Methodref_info met_elem;
void init_cp (u2_t sz);
void fill_cp (FILE* fptr);
#endif
