#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *data;
    int size;
} CompressedData;

typedef struct {
    char elem;
    int cnt;
} Pair;

typedef enum CompressType {
    MOCK_COMPRESS,
    RLE_COMPRESS,
    FIB_COMPRESS
} CompressType;

extern CompressedData compress(CompressType mode, int n, void *data);
extern CompressedData mock_compress(void *data, int n);
extern CompressedData rle_compress(CompressedData data);
extern CompressedData rle_decompress(CompressedData data);
extern CompressedData fib_compress(CompressedData data);


#endif
