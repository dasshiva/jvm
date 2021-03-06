/* File : cmdflags.c
 * Descrption : contains methods for parsing command-line arguments and for checking the results 
 * Date : 13.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/cmdparser.h"
#include <log.h>

static cmdflags flgs = {0};
void parse_args(int argc, char* *argv) {
	int expect = 0;
	char prev = ' ';
	for (int i = 1; i < argc; i++) {
		if (expect) {
			switch (prev) {
				case 'f' : flgs.file = *(argv + i); break;
			}
			expect = 0;
			prev = ' ';
			continue;

		}

		if (argv[i][0] == '-') {
			char c;
			switch ((c = argv[i][1])) {
				case 'v': flgs.verbose = 1; break;
				case 'l': flgs.log_file = 1; break;
				case 'f': prev = c; expect = 1; break;
				default: log_fatal("Unknown command line option -%c", c);
			}
		}
	}
	if (expect) 
		log_fatal("Expected argument for option -%c",prev);
}

int is_verbose() {
	return flgs.verbose;
}

char* get_file () {
	if (!flgs.file) 
		log_fatal("Expected a file argument");
	return flgs.file;
}

int is_log_file () {
	return flgs.log_file;
}
