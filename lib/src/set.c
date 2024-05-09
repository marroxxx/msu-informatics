#include "../headers/set.h"

L2S *
set_find(Set *set, char *key) {
    if (set == NULL) {
        fprintf(stderr, "set_find error: set is NULL\n");
        fflush(stderr);
        exit(1);
    }
    int num = set->hash(key);
    if (set->arr[num].size == 0) {
        return NULL;
    } else if (set->arr[num].size > 1) {
        printf("you're have collisions on key <%s>\n", key);
        return &set->arr[num];
    } else {
        return &set->arr[num];
    }
}

void
set_insert(Set *set, char *key) {
    if (set == NULL) {
        fprintf(stderr, "set_insert error: set is NULL\n");
        fflush(stderr);
        exit(1);
    }
    int num = set->hash(key);
    if (set_find(set, key) == NULL) {
        printf("you're have collisions on key <%s>\n", key);
    } 
    l2s_push_back(&set->arr[num], key);
}

void
set_erase(Set *set, char *key) {
    if (set == NULL) {
        fprintf(stderr, "set_erase error: set is NULL\n");
        fflush(stderr);
        exit(1);
    }
    int num = set->hash(key);
    l2s_erase(&set->arr[num], key);
}