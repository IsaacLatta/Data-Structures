#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct {
	struct _node_t* top;
} stack_t;

stack_t* stack_create();
void stack_push(stack_t* stack, void* data);
void* stack_pop(stack_t* stack);
void stack_destroy(stack_t* stack);
void print_stack(stack_t* stack, void(*print)(void*));

#endif
