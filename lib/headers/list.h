#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} List;

typedef struct L2Node {
    int data;
    struct L2Node *prev;
    struct L2Node *next;
} L2Node;

typedef struct L2 {
    L2Node *head;
    L2Node *tail;
    size_t size;
} L2;

extern List *l_init(List *list, int elem);
extern List *l_push_back(List *list, int elem);
extern List *l_insert(List *list, int elem, int pos);
extern List *l_erase(List *list, int pos);
extern List *l_update(List *list, int elem, int pos);
extern int l_get(List *list, int pos);
extern List *l_find(List *list, int elem);
extern void l_printf(List *list);
extern void l_free(List *list);

extern void l2_push_back(L2 *list, int elem);
extern void l2_push_front(L2 *list, int elem);
extern void l2_erase(L2 *list, int pos);
extern void l2_insert(L2 *list, int pos, int elem);
extern void l2_update(L2 *list, int pos, int elem);
extern L2Node *l2_find(L2 *list, int elem);
extern void l2_free(L2 *list);
extern int l2_get(L2 *list, int pos);
extern void l2_printf(L2 *list);

#endif
