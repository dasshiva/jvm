/* File : class.c
 * Descrption : contains methods for creating the in-memory representation of a .class file
 * Date : 11.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/class.h"
#include "include/resolve.h"
#include "include/error.h"
#include "include/reader.h"
#include "include/access.h"
#include "include/mem.h"

#include <log.h>

#define JAVA_MAGIC 0xCAFEBABE

extern int strcmp (const char*, const char*);
extern int is_verbose();

static u1_t load_limit = 5, index = 0;

/* loaded_classes contains the names of all classes that have been
 * loaded till now while loaded_class_refs contains the in-memory 
 * representations of the corresponding loaded classes (Java_class*).
 * The classes and their corresponding represenatation lie at the
 * same index of these structures. For example, if a class 'Hello' is
 * loaded first then its index in loaded_classes will be 0 while the
 * Java_class* representing it will be at loaded_class_refs[0] 
 */

static u1_t** loaded_classes = NULL;
static Java_class** loaded_class_refs = NULL;

static inline void add_class (char* class_name) {
	if (!loaded_classes) {
		loaded_classes = mem_alloc (sizeof (u1_t) * load_limit);
		loaded_class_refs = mem_alloc(sizeof (Java_class*) * load_limit);
	}
	loaded_classes[index] = class_name;
}

static void add_class_ref(Java_class* jc) {
	if (index == load_limit) {                                                    load_limit+=5;                                      
		mem_realloc(loaded_class_refs, load_limit);
		mem_realloc(loaded_classes, load_limit);
        } 
	loaded_class_refs[index] = jc; 

	/* add_class_ref should increment index because it will 
	 * always be called after add_class and the index at which the
	 * class name has been added into load_class must always match
	 * the index at  which jc will be added into loaded_class_refs
	 * to exhibit the behaviour explained above */
        index++; 
}

Java_class* get_classref (u1_t* class_name) {
	for (int i = 0; i <= index; i++) {
		/* This totally relies on the behaviour described
		 * in line 25 */
		if (strcmp(loaded_classes[i], class_name) == 0) 
			return loaded_class_refs[i];
	}
}
static void debug_print (cl_flags* fg) {     
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
       log_fatal("invalid magic number %x in class file ", jc->magic);
    jc->minor = read_u2(fptr);
    jc->major = read_u2(fptr);
    log_trace("Running class file version %d.%d (Java %d)",jc->major,jc->minor, jc->major - 44);
    jc->cp_count = read_u2(fptr);
    log_trace("Constant pool size : %d",jc->cp_count);
    init_cp(&jc->cp, jc->cp_count, fptr);
    jc->fg = get_class_flags(read_u2(fptr));
    //if (is_verbose())
    //   debug_print(&jc->fg);
    jc->this_class = resolve_utf8(&jc->cp, read_u2(fptr));
    add_class(jc->this_class);
    log_trace("This class : %s", jc->this_class);
    jc->super_class = resolve_utf8(&jc->cp, read_u2(fptr));
    log_trace("Super class : %s ", jc->super_class);
    jc->inters_count = read_u2(fptr);
    jc->inters = (u2_t*) mem_alloc(sizeof (u2_t) * jc->inters_count);
    for (u2_t i = 0; i < jc->inters_count; i++) {
	    jc->inters[i] = read_u2(fptr);
    }
    jc->fields_count = read_u2(fptr);
    init_fields(&jc->fds, jc->fields_count, fptr);
    jc->meths_count = read_u2(fptr);
    log_trace("Initializing methods ");
    init_methods(&jc->mts, jc->meths_count, fptr, &jc->cp);
    jc->attrs_count = read_u2(fptr);
    jc->cl = get_class_attr(fptr,&jc->cp,jc->attrs_count);
    log_trace("Source file for this class : %s", resolve_utf8(&jc->cp,jc->cl->cp_index));
    add_class_ref(jc);
    return jc;
}
