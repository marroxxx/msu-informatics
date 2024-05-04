#include "../headers/tree.h"
#include <stdlib.h>
#include <stdio.h>

void
swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void
heap_insert(Heap *heap, int value) {
    TreeNode *newNode = calloc(1, sizeof(TreeNode));
    newNode->data = value;
    newNode->left = newNode->right = newNode->parent = NULL;

    if (heap->root == NULL) {
        heap->root = newNode;
        return;
    }

    TreeNode *temp = heap->root;
    while (temp->left != NULL && temp->right != NULL) {
        if (temp->left != NULL && temp->right != NULL) {
            if (temp->left->data < temp->right->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        } else {
            if (temp->left != NULL) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
    }

    if (temp->left == NULL) {
        temp->left = newNode;
    } else {
        temp->right = newNode;
    }

    newNode->parent = temp;

    while (newNode->parent != NULL && newNode->parent->data < newNode->data) {
        swap(&newNode->data, &newNode->parent->data);
        newNode = newNode->parent;
    }
}

int 
heap_erase_root(Heap *heap) {
    if (heap->root == NULL) {
        fflush(stderr);
        fprintf(stderr, "Heap is empty\n");
        exit(1);
    }

    int rootValue = heap->root->data;

    if (heap->root->left == NULL && heap->root->right == NULL) {
        free(heap->root);
        heap->root = NULL;
        return rootValue;
    }

    TreeNode *lastNode = heap->root;
    while (lastNode->left != NULL || lastNode->right != NULL) {
        if (lastNode->right != NULL)
            lastNode = lastNode->right;
        else
            lastNode = lastNode->left;
    }

    if (lastNode->parent->left == lastNode)
        lastNode->parent->left = NULL;
    else
        lastNode->parent->right = NULL;

    heap->root->data = lastNode->data;
    free(lastNode);

    TreeNode *current = heap->root;
    while (current->left != NULL || current->right != NULL) {
        TreeNode *leftChild = current->left;
        TreeNode *rightChild = current->right;

        TreeNode *maxChild = current;
        if (leftChild != NULL && leftChild->data > maxChild->data) {
            maxChild = leftChild;
        }
        if (rightChild != NULL && rightChild->data > maxChild->data) {
            maxChild = rightChild;
        }

        if (maxChild == current) {
            break;
        }
        int temp = current->data;
        current->data = maxChild->data;
        maxChild->data = temp;

        current = maxChild;
    }

    return rootValue;
}


void
bst_insert(BSTree *tree, int elem) {
    TreeNode *new_node = calloc(1, sizeof(*new_node));
    new_node->data = elem;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    if (tree->root == NULL) {
        tree->root = new_node;
        return; 
    }
    TreeNode *cur = tree->root;
    TreeNode *parent = NULL;
    while (cur != NULL) {
        parent = cur;
        if (elem < cur->data) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    new_node->parent = parent;
    if (elem < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

int 
bst_find(BSTree *tree, int elem) {
    TreeNode *current = tree->root;

    while (current != NULL) {
        if (current->data == elem) {
            return 1;
        } else if (current->data < elem) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return 0;
}

void bst_erase(BSTree *tree, int elem) {
    TreeNode *current = tree->root;
    int flag = 0;
    while (current != NULL) {
        if (current->data == elem) {
            flag = 1;
            break;
        } else if (current->data < elem) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (flag == 0) {
        fprintf(stderr, "bst_erase tree is empty\n");
        fflush(stderr);
        exit(1);
    }
    TreeNode *new_node;
    if (current->left == NULL) {
        new_node = current->right;
    } else if (current->right == NULL) {
        new_node = current->left;
    } else {
        new_node = current->right;
        while (new_node->left != NULL) {
            new_node = new_node->left;
        }
        if (new_node->parent != current) {
            new_node->parent->left = new_node->right;
            if (new_node->right != NULL) {
                new_node->right->parent = new_node->parent;
            }
            new_node->right = current->right;
            new_node->right->parent = new_node;
        }
        new_node->left = current->left;
        new_node->left->parent = new_node;
    }
    if (current->parent == NULL) {
        tree->root = new_node;
    } else if (current == current->parent->left) {
        current->parent->left = new_node;
    } else {
        current->parent->right = new_node;
    }
    if (new_node != NULL) {
        new_node->parent = current->parent;
    }
    free(current);
}

Vector bst_to_vector(BSTree *tree) {
    Vector vector;
    vector.size = 0;
    vector.capacity = 10000;
    vector.data = calloc(1, sizeof(vector.data));

    Vector node_vector;
    node_vector.size = 0;
    node_vector.capacity = 10000;
    node_vector.data = 0;

    TreeNode *current = tree->root;

    while (current != NULL || node_vector.size > 0) {
        while (current != NULL) {
            v_push_back(&node_vector, current);
            current = current->left;
        }
        current = v_pop_back(&node_vector);
        v_push_back(&vector, current->data);
        current = current->right;
    }

    free(node_vector.data);
    return vector;
}
