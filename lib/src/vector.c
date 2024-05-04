#include "../headers/vector.h"
#include <stdlib.h>
#include <stdio.h>

enum {
    SIZE = 1,
    CAPACITY = 10000
};

Vector
init(void) {
    Vector vector;
    vector.size = SIZE;
    vector.capacity = CAPACITY;
    int *res = calloc(SIZE, sizeof(*res));
    vector.data = res;
    return vector;
}

void
v_push_back(Vector *vector, int elem) {
    if (vector->size + 1 <= vector->capacity) {
        vector->size++;
        vector->data[vector->size - 1] = elem;
    } else {
        int *new_data;
        vector->data = realloc(vector->data, 2 * vector->capacity);   //
        if (new_data == NULL) {
             exit(1);
        }
        vector->data = new_data;
        vector->size++;
        vector->capacity *= 2;
        vector->data[vector->size - 1] = elem;
    }
}

void
v_insert(Vector *vector, int elem, int pos) {
    if (pos > vector->size || pos < 0) {
        return;
    }
    v_push_back(vector, 0);
    for (int i = vector->size - 1; i > pos; --i) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[pos] = elem;
}

void
v_erase(Vector *vector, int pos) {
    int prev = vector->data[pos];
    if (pos >= vector->size || pos < 0) {
        return;
    }
    for (int i = pos; i < vector->size - 1; ++i) {
        vector->data[i] = vector->data[i + 1];
    }
    vector->size--;
}

void
v_update(Vector *vector, int elem, int pos) {
    if (pos < 0 || pos >= vector->size) {
        return;
    }
    vector->data[pos] = elem;
}

int
v_get(Vector *vector, int pos) {
    if (pos < 0 || pos >= vector->size) {
        return 0;
    }
    return vector->data[pos];
}
