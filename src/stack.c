#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void init_stack(stack_t* stack) {
    memset(stack->arr, 0, sizeof(stack->arr));
    stack->top = 0;
}

// insertion/deletion
void push(stack_t* stack, u16 value) {
    if(is_full(stack)) {
        fprintf(stderr, "Stack overflow...\n");
        exit(-1);
    }

    stack->arr[stack->top] = value; 
    stack->top += 1;
}

void pop(stack_t* stack) {
    if(is_empty(stack)) {
        fprintf(stderr, "Stack underflow...\n");
        exit(-1);
    }

    stack->arr[--stack->top] = 0;
}

// content checking
bool is_full(stack_t* stack) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        return true;
    }

    return false;
}

bool is_empty(stack_t* stack) {

    if(stack->top <= -1) {
        fprintf(stderr, "Stack underflow\n");
        return true;
    }   

    return false;
}