#ifndef TREE_H
#define TREE_H

#include "vector.h"

typedef struct AVLNode {
    int data;
    int height;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

typedef struct AVLTree {
    TreeNode *root;
} Tree;

extern void avl_insert(AVLTree *tree, int elem);

#endif
