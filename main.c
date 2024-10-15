#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right, *parent;
} Node;

typedef struct SplayTree {
    Node *root;
} SplayTree;


Node* createNode(int data);
void right_rotation(SplayTree *T, Node *x);
void left_rotation(SplayTree *T, Node *x);
void splay(SplayTree *T, Node *n);
void insert(SplayTree *T, int data);
void printTree(Node *root, int space);

//  create  new node
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Right rotation
void right_rotation(SplayTree *T, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        T->root = y; // y is new root
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// Left rotation
void left_rotation(SplayTree *T, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        T->root = y; 
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

//Splay Tree
void splay(SplayTree *T, Node *n) {
    while (n->parent != NULL) {
        if (n->parent == T->root) {
            if (n == n->parent->left) {
                right_rotation(T, n->parent);
            } else {
                left_rotation(T, n->parent);
            }
        } else {
            Node *p = n->parent;
            Node *g = p->parent;
            if (n == p->left && p == g->left) {
                right_rotation(T, g);
                right_rotation(T, p);
            } else if (n == p->right && p == g->right) {
                left_rotation(T, g);
                left_rotation(T, p);
            } else if (n == p->left && p == g->right) {
                right_rotation(T, p);
                left_rotation(T, g);
            } else {
                left_rotation(T, p);
                right_rotation(T, g);
            }
        }
    }
}

// Insert data
void insert(SplayTree *T, int data) {
    Node *temp = T->root;
    Node *y = NULL;
    Node *n = createNode(data);
    while (temp != NULL) {
        y = temp;
        if (n->data < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    n->parent = y;
    if (y == NULL) {
        T->root = n; 
    } else if (n->data < y->data) {
        y->left = n;
    } else {
        y->right = n;
    }
    splay(T, n);
}

// Print Tree
void printTree(Node *root, int space) {
    if (root == NULL) return;
    space += 10; 
    printTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    printTree(root->left, space);
}


int main() {
    SplayTree *T = (SplayTree*)malloc(sizeof(SplayTree));
    T->root = NULL;
    int data;
    char choice;
    do {
        printf("Enter a number to insert into the splay tree: ");
        scanf("%d", &data);
        insert(T, data);
        
        printf("Splay Tree:\n");
        printTree(T->root, 0);

        printf("Do you want to insert another number? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    return 0;
}
