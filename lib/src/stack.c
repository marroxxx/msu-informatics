#include <stdlib.h>
#include <stdio.h>
#include "../headers/stack.h"

int
s_empty(Stack *deq) {
    if (deq == NULL) {
        fprintf(stderr, "empty error\n");
        fflush(stderr);
        exit(1);
    }
    if (deq->list.size == 0) {
        return 1;
    }
    return 0;
}

void 
s_push(Stack *deq, int elem) {
    if (deq == NULL) {
        fprintf(stderr, "s_push_back error\n");
        fflush(stderr);
        exit(1);
    }   
    l2_push_back(&(deq->list), elem);
}

int 
s_pop(Stack *deq) {
    if (deq->list.size == 0) {
        fprintf(stderr, "s_pop_back deque is empty\n");
        fflush(stderr);
        exit(1);
    }   
    if (deq->list.size == 1) {
        int elem = deq->list.tail->data;
        deq->list.head = NULL;
        deq->list.tail = NULL;
        deq->list.size = 0;
        return elem;
    }
    int elem = deq->list.tail->data;
    l2_erase(&(deq->list), deq->list.size - 1);
    return elem;
}

void
s_free(Stack *deq) {
    if (deq->list.size == 0) {
        return;
    }
    l2_free(&deq->list);
}

int
s_pop(Stack *deq) {
    if (deq->list.size == 0) {
        printf("s_pop deq is empty\n");
    }
    return deq->list.head->data;
}