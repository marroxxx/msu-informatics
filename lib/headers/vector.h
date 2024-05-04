#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    int *data;
    int size;
    int capacity;
} Vector;

extern void v_push_back(Vector *vector, int elem);
extern void v_insert(Vector *vector, int elem, int pos);
extern void v_erase(Vector *vector, int pos);
extern void v_update(Vector *vector, int elem, int pos);
extern int v_get(Vector *vector, int pos);

#endif
