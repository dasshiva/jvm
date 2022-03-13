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

#include <stdio.h>
#include <log.h>

#define JAVA_MAGIC 0xCAFEBABE

extern int is_verbose();
u2_t convert_version (u2_t ver) {
    /* This is quick hack to get the class file version in 
     * human readable terms. Here, we basically do a left shift of 
     * 8 bytes. For example, if we were running  a Java 8 class file 
     * then ver would be 0x3400. 
     * On left shifting this number by 8 bits we get 0x34 (i.e 52)
     */
	return (ver >> 8);
}


void debug_print (flags* fg) {     
	printf("Access flags are interpreted as : ");
	if (fg->ispublic)                 
		printf("public ");         
	if (fg->isenum)                                         
		printf(" enum ");                                   
	if (fg->isabstract) {                  
		if (fg->isinterface)                       
			printf(" interface ");  
		else                                                
			printf((fg->isfinal)?" final abstract class" : " abstract class ");                                             
	}                                                       
	else {                                                   
		if (fg->isfinal)                                   
			printf(" final ");                        
		printf (" class ");               
	}
	printf("\n");
}

u2_t read_2(FILE* fptr) {
	u2_t rd = 0;
	while (rd == 0) {
		rd = read_u1(fptr);
	}
	return rd;
}

Java_class* create_class (FILE* fptr){
    Java_class* jc = (Java_class*) mem_alloc(sizeof (struct _class));
    jc->magic = read_u4(fptr);
    if (jc->magic != JAVA_MAGIC)
       log_stderr(FATAL,"invalid magic number in class file ");
    jc->minor = read_u2(fptr);
    jc->major = convert_version(read_u2(fptr));
    log_stderr(TRACE,"Running class file version %d.%d",jc->major,jc->minor);
    jc->cp_count = read_2(fptr);
    log_stderr(TRACE,"Constant pool size : %d",jc->cp_count);
    init_cp(jc->cp, jc->cp_count, fptr);
    jc->fg = get_flags(read_2(fptr));
    //if (is_verbose())
//	    debug_print(&jc->fg);
    jc->this_class = read_u2(fptr);
    jc->super_class = read_u2(fptr);
    jc->inters_count = read_u2(fptr);
    jc->inters = (u2_t*) mem_alloc(sizeof (u2_t) * jc->inters_count);
    for (u2_t i = 0; i < jc->inters_count; i++) {
	    jc->inters[i] = read_u2(fptr);
    }

    return jc;
}
