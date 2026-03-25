#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

// (a) Cap phat node moi
struct tnode* talloc(int data) {
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// (b) Them phan tu vao cay
struct tnode* addnode(struct tnode* root, int data) {
    if (root == NULL) {
        return talloc(data);
    }
    
    if (data < root->data) {
        root->left = addnode(root->left, data);
    } else if (data > root->data) {
        root->right = addnode(root->right, data);
    }
    
    return root;
}

// (c) Duyet Pre-order
void preorder(struct tnode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// (d) Duyet In-order
void inorder(struct tnode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// (e) Xoa cay va tra ve so node da xoa (Post-order)
int deltree(struct tnode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int leftDeleted = deltree(root->left);
    int rightDeleted = deltree(root->right);
    
    free(root);
    
    return leftDeleted + rightDeleted + 1;
}

// (f) Ham main kiem thu
int main() {
    struct tnode* root = NULL;
    
    int arr[] = {3, 1, 0, 2, 8, 6, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    for (int i = 0; i < n; i++) {
        root = addnode(root, arr[i]);
    }
    
    printf("Pre-order: ");
    preorder(root);
    printf("\n");
    
    printf("In-order : ");
    inorder(root);
    printf("\n");
    
    int deletedCount = deltree(root);
    root = NULL;
    
    printf("Da xoa toan bo cay. So node bi xoa: %d\n", deletedCount);
    
    return 0;
}