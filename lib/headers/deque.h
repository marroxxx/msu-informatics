#ifndef DEQUE_H
#define DEQUE_H

#include "list.h"

typedef struct Deque {
    L2 list;
} Deque;

extern int d_empty(Deque *deq);
extern void d_push_back(Deque *deq, int elem);
extern void d_push_front(Deque *deq, int elem);
extern int d_pop_back(Deque *deq);
extern int d_pop_front(Deque *deq);
extern int d_back(Deque *deq);
extern int d_front(Deque *deq);
extern void d_free(Deque *deq);

#endif
