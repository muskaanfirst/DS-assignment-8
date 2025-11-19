#include <stdio.h>
#include <stdlib.h>

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

Node* insert(Node *root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

Node* find_min(Node *root) {
    if (root == NULL) return NULL;
    while (root->left) root = root->left;
    return root;
}

Node* deleteNode(Node *root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node *tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {
            Node *tmp = root->left;
            free(root);
            return tmp;
        } else {
            Node *succ = find_min(root->right);
            root->key = succ->key;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

int maxDepth(Node *root) {
    if (root == NULL) return 0;
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return (l > r ? l : r) + 1;
}

int minDepth(Node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    if (root->left == NULL) return minDepth(root->right) + 1;
    if (root->right == NULL) return minDepth(root->left) + 1;
    int l = minDepth(root->left);
    int r = minDepth(root->right);
    return (l < r ? l : r) + 1;
}

void inorder_print(Node *root) {
    if (!root) return;
    inorder_print(root->left);
    printf("%d ", root->key);
    inorder_print(root->right);
}

int main(void) {
    Node *root = NULL;
    int keys[] = {20, 10, 5, 15, 30, 25, 35, 12, 18};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; ++i) root = insert(root, keys[i]);

    printf("In-order traversal: ");
    inorder_print(root);
    printf("\n");

    printf("Max depth: %d\n", maxDepth(root));
    printf("Min depth: %d\n", minDepth(root));

    root = deleteNode(root, 10);
    printf("After deleting 10, in-order: ");
    inorder_print(root);
    printf("\n");
    printf("Max depth: %d\n", maxDepth(root));
    printf("Min depth: %d\n", minDepth(root));

    root = deleteNode(root, 20);
    printf("After deleting 20, in-order: ");
    inorder_print(root);
    printf("\n");
    printf("Max depth: %d\n", maxDepth(root));
    printf("Min depth: %d\n", minDepth(root));

    return 0;
}
