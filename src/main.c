/* File : main.c
 * Descrption : The entry point for the JVM
 * Date : 11.3.22
 * Author : dasshiva
 * License : MIT License (Look at the LICENSE file for more details)
 */

#include "include/class.h"
#include "include/cmdparser.h"
#include "include/exec.h"
#include <log.h>

int main (int argc, char* argv[]) {
    parse_args(argc,argv);
    FILE *fptr = fopen(get_file(),"rb");
    if(is_log_file())
	    set_file_target(fopen("log.txt","w"));
    log_trace("Starting JVM");
    Java_class* jc = create_class(fptr);
    frame* main = get_frame("main","([Ljava/lang/String;)V",jc);
    if (main == NULL)
	    log_fatal("Main method not found");
    log_trace("Starting main method execution");
    exec_frame(&main);
    log_trace("Finished main method execution");
    fclose(fptr);
}

