#ifndef _FRAME_H_
#define _FRAME_H_

#include "class.h"

/* The various values for the type field of a f_args structure */
#define INT 1
#define FLOAT 2

typedef struct _frame_args {
	u1_t type;
	int ival;
	float fval;
} f_args;

typedef struct __frame {
	u4_t pc;
	f_args* tab;
	struct f_stack {
		u4_t top;
		f_args* op;
	} *stack;
	code_attr* code;
	constant_pool* cp;
} frame;

frame* get_frame(const char* name, const char* desc, Java_class* jc);

#endif
