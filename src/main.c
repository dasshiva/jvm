/* File : main.c
 * Descrption : The entry point for the JVM
 * Date : 11.3.22
 * Author : Shivashish Das
 */

#include "include/class.h"
#include "include/access.h"
#include "include/error.h"

#include <log.h>
void debug_print (flags fg) {
	if (fg.ispublic)
	   printf("public ");
	if (fg.isenum)
	   printf(" enum ");
	if (fg.isabstract) {
		if (fg.isinterface)
		    printf(" interface ");
		else 
		    printf((fg.isfinal)?" final abstract class" : " abstract class ");
	}
	else {
		if (fg.isfinal)
		    printf(" final ");
		printf (" class ");
	}
}

int main (int argc, char* argv[]) {
    FILE* fptr = NULL;
	if (argc<2)
		log_stderr(FATAL,"Expected a filename");
    if ((fptr = fopen(argv[1],"rb")) == NULL)
	    log_stderr(FATAL,"File not found");
	Java_class* jc = create_class(fptr);
	//debug_print(jc->fg);
	fclose(fptr);
}

