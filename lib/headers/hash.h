#ifndef HASH_H
#define HASH_H

#include "lists.h"

typedef struct HashTable {
    unsigned short (*hash)(char *str);
    L2S arr[1<<16];
} HashTable;

extern void hs_insert(HashTable *hash_table, char *str);
extern void hs_erase(HashTable *hash_table, char *str);
extern char *hs_find(HashTable *hash_table, char *str);

#endif
