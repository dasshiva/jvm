/* File : exec.c
 * Descrption : contains methods that actually implement opcodes and execute frames
 * Date : 18.3.22
 * Author : dasshiva
 * License : MIT License (Look at the LICENSE file for more details)   */
#include "include/exec.h"
#include "include/frame.h"
#include "include/resolve.h"
#include <log.h>

static void push(frame** f, f_args* arg);
static f_args* pop (frame** f);
static void iadd(frame** f);
static void stack_dump (frame** f);
static void invokestatic (frame** f);
static u2_t parse_desc (u1_t* desc);

f_args* exec_frame(frame** f) {
	frame* deref = *f;
	u2_t index = 1;
	u1_t *name = NULL , *desc = NULL;
	frame* fr = NULL;
	for (; deref->pc < deref->code->code_len; deref->pc++) {
		switch(deref->code->code[deref->pc]) {
			case 16: // bipush
				deref->stack->op[deref->stack->top].type = INT;
				deref->stack->op[deref->stack->top++].ival = (int) deref->code->code[++deref->pc];
				break;
			case 26: // iload_0 
				 deref->stack->op[deref->stack->top++]= deref->tab[0];
				 break;
			case 27: // iload_1
				 deref->stack->op[deref->stack->top++]= deref->tab[1];
				 break;
			case 87: // pop
				 pop(f);
				 break;
			case 96: // iadd
				 iadd(f);
				 break;
			case 172: // ireturn
				 return pop(f);
			case 177: // return
				 return NULL;
			case 184: // invokestatic
				invokestatic(f);
				break; 
			default:
				log_fatal("Instruction %d is not supported yet", deref->code->code[deref->pc]);
		}
		stack_dump(f);
	}
}

static void push(frame** f, f_args* arg) {                           
	(*f)->stack->op[(*f)->stack->top++] = *arg;
}

static f_args* pop (frame** f) {
	frame* deref = *f;
	deref->stack->top--;
	//printf(" Popped off :%d", deref->stack->op[deref->stack->top + 1].ival);
	return &deref->stack->op[deref->stack->top];
}

static void iadd(frame** f) {
	frame* deref = *f;
	int op1 = pop(f)->ival;
	int op2 = pop(f)->ival;
	deref->stack->op[deref->stack->top].type = INT;
	deref->stack->op[deref->stack->top++].ival = op1 + op2;
}

static void invokestatic (frame** f) {
       /* The unsigned indexbyte1 and indexbyte2 are used to construct
	 * an index into the run-time constant pool of the current
	 * class (§2.6), where the value of the index is
	 * (indexbyte1 << 8) | indexbyte2. */

	u1_t *cl_name = NULL, *name = NULL, *desc = NULL;
	frame* deref = *f, *new = NULL;
	u1_t index = deref->code->code[++deref->pc] << 8 | deref->code->code[++deref->pc];   
	cl_name = resolve_utf8(&deref->cp,deref->cp[deref->cp[index].met->cl_index].cl->n_index);
	name = resolve_utf8(&deref->cp,deref->cp[deref->cp[index].met->nt_index].nt->n_index);
	desc = resolve_utf8(&deref->cp,deref->cp[deref->cp[index].met->nt_index].nt->desc_index);
	u2_t to_pop = parse_desc(desc);
	new = get_frame(name, desc, get_classref(cl_name));
	for (u2_t a = 0; a < to_pop; a++) {
		new->tab[a] = *pop(f);
	}
	push(f,exec_frame(&new));
	destroy_frame(&new);
	//printf("%d",deref->stack->op[deref->stack->top].ival);
}

/* This works only for parsing methods which take primitive types
 * as parameters . For example (I)V. */
static u2_t parse_desc (u1_t* desc) {
	u2_t to_pop = 1;
	for (; desc[to_pop] != ')'; to_pop++);
	return to_pop - 1 ;
}

static void stack_dump (frame** f) {
	frame* deref = *f;
	printf("Stack dump\n");
	for (int i = 0; i < deref->stack->top; i++) {
		if (deref->stack->op[i].type == INT) 
			printf("%d\n",deref->stack->op[i].ival);
		else
			printf("%f\n", deref->stack->op[i].fval);
	}
}
