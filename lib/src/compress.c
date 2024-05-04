#include <stdio.h>
#include <stdlib.h>
#include "../headers/compress.h"

CompressedData
compress(CompressType mode, int n, void *data) {
    CompressedData new_data;
    new_data.data = data;
    new_data.size = n;
    switch (mode) {
        case RLE_COMPRESS:
            new_data = rle_compress(new_data);
            break;
        case FIB_COMPRESS:
            new_data = fib_compress(new_data);
            break;
        default:
            new_data = mock_compress(data, n);
            break;
    }
    return new_data;
}

CompressedData
mock_compress(void *data, int n) {
    CompressedData mock_data;
    mock_data.size = n;
    mock_data.data = data;
    return mock_data;
}

CompressedData
rle_compress(CompressedData inp_data) {
    CompressedData rle_data;
    char *input = (char *)inp_data.data;
    int size = 0;
    for (int i = 1; i < inp_data.size; ++i) {
        if (input[i] != input[i - 1]) {
            ++size;
        }
    }
    Pair *res = calloc(size, sizeof(*res));
    int j = 0, cnt = 0;
    Pair pair;
    for (int i = 1; i < inp_data.size; ++i) {
        ++cnt;
        if (input[i] != input[i - 1]) {
            pair.elem = input[i - 1];
            pair.cnt = cnt;
            cnt = 0;
            res[j] = pair;
            ++j;
        }
    }
    rle_data.data = res;
    rle_data.size = size;
    free(input);
    free(res);
    return rle_data;   
}

CompressedData
rle_decompress(CompressedData inp_data) {
    CompressedData rle_data;
    Pair *pairs = (Pair *)rle_data.data;
    int size1 = 0;
    for (int i = 0; i < inp_data.size; ++i) {
        size1 += pairs[i].elem;
    }
    int now = 0;
    char *input = calloc(size1, sizeof(*input));
    for (int i = 0; i < inp_data.size; ++i) {
        int count = pairs[i].cnt;
        for (int j = 0; j < count; ++j) {
            input[now] = pairs[i].elem;
            ++now;
        }
    }
    rle_data.data = input;
    rle_data.size = size1;
    return rle_data;
}

CompressedData
fib_compress(CompressedData data) {
    return data;
}
