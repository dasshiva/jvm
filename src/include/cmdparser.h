#ifndef  _CMDPARSER_H_
#define  _CMDPARSER_H_

typedef struct _flags {
	int verbose;
	char *file;
} cmdflags;

void parse_args(int argc, char* *argv);
int is_verbose();
char* get_file();

#endif
