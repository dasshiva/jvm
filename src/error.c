/* File : error.c
 * Descrption : contains methods for dealing with errors
 * Date : 11.3.22
 * Author : Shivashish Das
 */
#include "include/error.h"

#include <stdio.h>
#include <stdlib.h>

void err_fatal(const char* msg) {
	printf("Fatal VM error: %s", msg);
	exit(EXIT_FAILURE);
}

void err_exit() {
	exit(EXIT_FAILURE);
}
