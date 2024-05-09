#ifndef MAP_H
#define MAP_H
#include "hash.h"

typedef struct HashTable {
    unsigned short (*hash)(char *str);
    L2S arr[1<<16];
} Map;

extern void map_insert(Map *map, char *item, char *key);
extern void map_erase(Map *map, char *item, char *key);
extern void map_init(Map *map);
extern L2S *map_find(Map *map, char *key);

#endif
