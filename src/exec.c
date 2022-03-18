/* File : exec.c
 * Descrption : contains methods that actually implement opcodes and execute frames
 * Date : 18.3.22
 * Author : dasshiva
 * License : MIT License (Look at the LICENSE file for more details)   */
#include "include/exec.h"
#include "include/frame.h"

#include <log.h>

int exec_frame(frame** f) {
	frame* deref = *f;
	for (; deref->pc < deref->code->code_len; deref->pc++) {
		switch(deref->code->code[deref->pc]) {
			case 16: // bipush
				deref->stack->op[deref->stack->top].type = INT;
				deref->stack->op[deref->stack->top].ival= (int) deref->code->code[++deref->pc];
				deref->stack->top++;
				break;
			default:
				log_fatal("Instruction %d is not supported yet", deref->code->code[deref->pc]);
		}
	}
	return 0;
}

