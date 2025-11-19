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

Node* search_recursive(Node *root, int key) {
    if (root == NULL) return NULL;
    if (root->key == key) return root;
    if (key < root->key) return search_recursive(root->left, key);
    else return search_recursive(root->right, key);
}

Node* search_iterative(Node *root, int key) {
    Node *cur = root;
    while (cur != NULL) {
        if (key == cur->key) return cur;
        else if (key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return NULL;
}

Node* find_min(Node *root) {
    if (root == NULL) return NULL;
    Node *cur = root;
    while (cur->left != NULL) cur = cur->left;
    return cur;
}

Node* find_max(Node *root) {
    if (root == NULL) return NULL;
    Node *cur = root;
    while (cur->right != NULL) cur = cur->right;
    return cur;
}

Node* inorder_successor(Node *root, Node *x) {
    if (x == NULL) return NULL;
    if (x->right != NULL)
        return find_min(x->right);

    Node *succ = NULL;
    Node *cur = root;
    while (cur != NULL) {
        if (x->key < cur->key) {
            succ = cur;
            cur = cur->left;
        } else if (x->key > cur->key) {
            cur = cur->right;
        } else break;
    }
    return succ;
}

Node* inorder_predecessor(Node *root, Node *x) {
    if (x == NULL) return NULL;
    if (x->left != NULL)
        return find_max(x->left);

    Node *pred = NULL;
    Node *cur = root;
    while (cur != NULL) {
        if (x->key > cur->key) {
            pred = cur;
            cur = cur->right;
        } else if (x->key < cur->key) {
            cur = cur->left;
        } else break;
    }
    return pred;
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

    int q = 15;
    Node *r1 = search_recursive(root, q);
    Node *r2 = search_iterative(root, q);
    printf("search_recursive(%d): %s\n", q, r1 ? "found" : "not found");
    printf("search_iterative(%d): %s\n", q, r2 ? "found" : "not found");

    Node *mn = find_min(root);
    Node *mx = find_max(root);
    if (mn) printf("Minimum: %d\n", mn->key);
    if (mx) printf("Maximum: %d\n", mx->key);

    Node *node = search_iterative(root, 15);
    if (node) {
        Node *succ = inorder_successor(root, node);
        Node *pred = inorder_predecessor(root, node);
        printf("Node: %d\n", node->key);
        printf("  Successor: %s\n", succ ? "exists" : "NULL");
        if (succ) printf("  Successor: %d\n", succ->key);
        printf("\n");
        printf("  Predecessor: %s\n", pred ? "exists" : "NULL");
        if (pred) printf("  Predecessor: %d\n", pred->key);
        printf("\n");
    }

    Node *maxnode = find_max(root);
    Node *s_of_max = inorder_successor(root, maxnode);
    printf("Successor of max (%d): %s\n", maxnode->key, s_of_max ? "exists" : "NULL");

    Node *minnode = find_min(root);
    Node *p_of_min = inorder_predecessor(root, minnode);
    printf("Predecessor of min (%d): %s\n", minnode->key, p_of_min ? "exists" : "NULL");

    return 0;
}
