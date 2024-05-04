#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"

char *
hs_find(HashTable *hash_table, char *str) {
    if (hash_table == NULL) {
    	exit(1);
    }
    unsigned short num = hash_table->hash(str);
    int pos = l2s_find(&hash_table->arr[(int)num], str);
    if (pos == -1) {
    	return NULL;
    }
    return l2s_get(&hash_table->arr[(int)num], pos);
}

void 
hs_insert(HashTable *hash_table, char *str) {
    if (hash_table == NULL) {
    	exit(1);
    }
    if (hs_find(hash_table, str) != NULL) {
    	return;
    }
    unsigned short num = hash_table->hash(str);
    l2s_push_back(&hash_table->arr[(int)num], str);
}

void 
hs_erase(HashTable *hash_table, char *str) {
    if (hash_table == NULL) {
    	exit(1);
    }
    unsigned short num = hash_table->hash(str);
    int pos = l2s_find(&hash_table->arr[(int)num], str);
    if (pos != -1) {
        l2s_erase(&hash_table->arr[(int)num], pos);
    }
}

