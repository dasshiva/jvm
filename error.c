#include "error.h"

#include <stdio.h>
#include <stdlib.h>

void err_fatal(const char* msg) {
	printf("Fatal VM error: %s", msg);
	exit(EXIT_FAILURE);
}

void err_exit() {
	exit(EXIT_FAILURE);
}
