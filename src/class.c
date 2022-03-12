/* File : class.c
 * Descrption : contains methods for creating the in-memory representation of a .class file
 * Date : 11.3.22
 * Author : Shivashish Das
 */

#include "include/class.h"
#include "include/error.h"
#include "include/reader.h"
#include "include/access.h"
#include "include/mem.h"

#define JAVA_MAGIC 0xCAFEBABE

u2_t convert_version (u2_t ver) {
    /* This is quick hack to get the class file version in human readable terms
	* Here, we basically do a left shift of 8 bytes and subtract it from 44
	* For example, if we were parsing a Java 8 class file then ver would be 0x3400
	* On left shifting this number by 8 bits we get 0x34 (i.e 52) and on subtracting 44
	* from that we get 8. 
	*/
	return (ver >> 8) - 44;
}

Java_class* create_class (FILE* fptr){
    Java_class* jc = (Java_class*) alloc(sizeof (struct _class));
    jc->magic = read_u4(fptr);
    if (jc->magic != JAVA_MAGIC)
       err_fatal("invalid magic number in class file ");
    jc->minor = read_u2(fptr);
    jc->major = convert_version(read_u2(fptr));
    jc->cp_count = read_u2(fptr);
    init_cp(jc->cp, jc->cp_count, fptr);
    jc->fg = get_flags(read_u2(fptr));
    jc->this_class = read_u2(fptr);
    jc->super_class = read_u2(fptr);
    return jc;
}
