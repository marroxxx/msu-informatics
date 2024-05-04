#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

typedef struct L2SNode {
    char *data;
    struct L2SNode *prev;
    struct L2SNode *next;
} L2SNode;

typedef struct L2S {
    L2SNode *head;
    L2SNode *tail;
    size_t size;
} L2S;

extern void l2s_push_back(L2S *List_str, char * elem);
extern void l2s_push_front(L2S *List_str, char * elem);
extern void l2s_erase(L2S *List_str, int pos);
extern void l2s_insert(L2S *List_str, int pos, char * elem);
extern void l2s_update(L2S *List_str, int pos, char * elem);
extern L2SNode *l2s_find(L2S *List_str, char * elem);
extern void l2s_free(L2S *List_str);
extern char * l2s_get(L2S *List_str, int pos);
extern void l2s_prchar *f(L2S *List_str);

#endif
