#ifndef STACK_H
#define STACK_H

#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    L2 list;
} Stack;

extern int s_empty(Stack *stack);
extern void s_push(Stack *stack);
extern int s_pop(Stack *stack);
extern void s_top(Stack *stack);
extern void s_free(Stack *stack);

#endif