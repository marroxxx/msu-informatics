#include <stdlib.h>
#include <stdio.h>
#include "../headers/deque.h"

int
d_empty(Deque *deq) {
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
d_push_back(Deque *deq, int elem) {
    if (deq == NULL) {
        fprintf(stderr, "d_push_back error\n");
        fflush(stderr);
        exit(1);
    }   
    l2_push_back(&(deq->list), elem);
}

void
d_push_front(Deque *deq, int elem) {
    if (deq == NULL) {
        fprintf(stderr, "d_push_front error\n");
        fflush(stderr);
        exit(1);
    }
    l2_push_front(&(deq->list), elem);
}

int 
d_pop_back(Deque *deq) {
    if (deq->list.size == 0) {
        fprintf(stderr, "d_pop_back deque is empty\n");
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

int
d_pop_front(Deque *deq) {
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
d_free(Deque *deq) {
    if (deq->list.size == 0) {
        return;
    }
    l2_free(&deq->list);
}

int
d_back(Deque *deq) {
    if (deq->list.size == 0) {
        printf("d_pop deq is empty\n");
    }
    return deq->list.head->data;
}
    
int
d_front(Deque *deq) {
    if (deq->list.size == 0) {
        printf("d_front deq is empty\n");
    }
    return deq->list.tail->data;
}
