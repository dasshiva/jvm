#ifndef  _CMDPARSER_H_
#define  _CMDPARSER_H_

typedef struct _cmdln_flags {
	int verbose, log_file;
	char *file;
} cmdflags;

void parse_args(int argc, char* *argv);
int is_verbose();
char* get_file();
int is_log_file();

#endif
