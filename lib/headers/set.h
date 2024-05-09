#ifndef SET_H
#define SET_H

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashTable {
    unsigned short (*hash)(char *str);
    L2S arr[1<<16];
} Set;

extern void set_insert(Set *set, char *key);
extern void set_erase(Set *set, char *key);
extern L2S *set_find(Set *set, char *key); //finded or not 

#endif
