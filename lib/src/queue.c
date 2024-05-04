#include <stdlib.h>
#include <stdio.h>
#include "../headers/queue.h"

int
q_empty(Queue *deq) {
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
q_push_back(Queue *deq, int elem) {
    if (deq == NULL) {
        fprintf(stderr, "d_push_back error\n");
        fflush(stderr);
        exit(1);
    }   
    l2_push_back(&(deq->list), elem);
}

int
q_pop(Queue *deq) {
    if (deq->list.size == 0) {
        fprintf(stderr, "d_pop_front deque is empty\n");
        fflush(stderr);
        exit(1);
    }
    if (deq->list.size == 1) {
        int elem = deq->list.head->data;
        deq->list.head = NULL;
        deq->list.tail = NULL;
        deq->list.size = 0;
        return elem;
    }
    int elem = deq->list.head->data;
    l2_erase(&(deq->list), 0);
    return elem;
}   

void
q_free(Queue *deq) {
    if (deq->list.size == 0) {
        return;
    }
    l2_free(&deq->list);
}
    
int
q_front(Queue *deq) {
    if (deq->list.size == 0) {
        printf("d_front deq is empty\n");
    }
    return deq->list.tail->data;
}
