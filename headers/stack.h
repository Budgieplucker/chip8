#ifndef STACK_H
#define STACK_H

#include "types.h"

#define MAX_STACK_SIZE 16

typedef struct {
    int top;
    u16 arr[16];
} stack_t;

// init
void init_stack(stack_t* stack);

// insertion/deletion
void push(stack_t* stack, u16 value);
void pop(stack_t* stack);

// content checking
bool is_full(stack_t* stack);
bool is_empty(stack_t* stack);

#endif