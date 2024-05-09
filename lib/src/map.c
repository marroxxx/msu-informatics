#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/map.h"

L2S *
map_find(Map *map, char *key) {
    if (map == NULL) {
    	exit(1);
    }
    unsigned short num = map->hash(key);
    L2S *list = &map->arr[num];
    return list;
}

void
map_init(Map *map) {
    for (int i = 0; i < (1 << 16); ++i) {
        map->arr[i].head = NULL;
        map->arr[i].tail = NULL;
        map->arr[i].size = 0;
    }
}

void 
map_insert(Map *map, char *item, char *key) {
    if (map == NULL) {
    	exit(1);
    }
    unsigned short num = map->hash(key);
    l2s_push_back(&map->arr[(int)num], item);
}

void 
map_erase(Map *map, char *key) {
    if (map == NULL) {
    	exit(1);
    }
    unsigned short num = map->hash(key);
    int pos = l2s_find(&map->arr[(int)num], key);
    if (pos != -1) {
        l2s_free(&map->arr[(int)num]);
    } else {
        printf("no elems in this key\n");
    }
}
