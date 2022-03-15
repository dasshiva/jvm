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

Java_class* create_class (FILE* fptr){
    Java_class* jc = (Java_class*) mem_alloc(sizeof (struct _class));
    jc->magic = read_u4(fptr);
    if (jc->magic != JAVA_MAGIC)
       log_stderr(FATAL,"invalid magic number in class file ");
    jc->minor = read_u2(fptr);
    jc->major = read_u2(fptr);
    log_stderr(TRACE,"Running class file version %d.%d (Java %d)",jc->major,jc->minor, jc->major - 44);
    jc->cp_count = read_u2(fptr);
    log_stderr(TRACE,"Constant pool size : %d",jc->cp_count);
    init_cp(&jc->cp, jc->cp_count, fptr);
    jc->fg = get_flags(read_u2(fptr), NOT_FIELD);
    //if (is_verbose())
    //   debug_print(&jc->fg);
    jc->this_class = read_u2(fptr);
    log_stderr(TRACE,"This class : %s", resolve_utf8(jc->cp, jc->this_class, jc->cp_count));
    jc->super_class = read_u2(fptr);
    log_stderr(TRACE,"Super class : %s ",resolve_utf8(jc->cp, jc->super_class, jc->cp_count));
    jc->inters_count = read_u2(fptr);
    jc->inters = (u2_t*) mem_alloc(sizeof (u2_t) * jc->inters_count);
    for (u2_t i = 0; i < jc->inters_count; i++) {
	    jc->inters[i] = read_u2(fptr);
    }
    jc->fields_count = read_u2(fptr);
    init_fields(&jc->fds, jc->fields_count, fptr);
    return jc;
}
