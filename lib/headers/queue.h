#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct Queue {
    L2 list;
} Queue;

extern int q_empty(Queue *deq);
extern void q_push(Queue *deq, int elem);
extern int q_pop(Queue *deq);
extern int d_front(Queue *deq);
extern void q_free(Queue *deq);

#endif
