#include "../headers/avl.h"
#include <stdio.h>
#include <stdlib.h>

void
avl_insert(AVLTree *tree, int elem) {
    return;
}

int
max(int a, int b) {
    return a > b ? a : b;
}
    
AVLNode *
rotate_left(AVLNode *root) {
    res = root->right;
    if (res == NULL || res->left == NULL || res->right == NULL) {
        return NULL;
    }
    AVLNode *right_left_son = root->right->left;
    if (right_left_son == NULL) {
        return NULL;
    }   
    res->left = root;
    res->left->right = right_left_son;
    res->left = max(h(res->left->left), h(res->left->right)) + 1;
    res->height = max(h(res->left), h(res->right)) + 1;
    return res;
}

int
h(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
