#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

int isBSTUtil(Node *node, long long min, long long max) {
    if (node == NULL) return 1;
    if (node->key <= min || node->key >= max) return 0;
    return isBSTUtil(node->left, min, node->key) && isBSTUtil(node->right, node->key, max);
}

int isBST(Node *root) {
    return isBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *bst = newNode(20);
    bst->left = newNode(10);
    bst->right = newNode(30);
    bst->left->left = newNode(5);
    bst->left->right = newNode(15);
    bst->right->left = newNode(25);
    printf("Tree 1 is %sBST\n", isBST(bst) ? "" : "not ");

    Node *nonbst = newNode(20);
    nonbst->left = newNode(30);     
    nonbst->right = newNode(10);
    printf("Tree 2 is %sBST\n", isBST(nonbst) ? "" : "not ");

    freeTree(bst);
    freeTree(nonbst);
    return 0;
}
