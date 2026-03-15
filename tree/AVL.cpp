#include "AVL.h"
int getHeight (TreeNode* node) {
    if (!node) return 0;
    return node->height;
}

int balanceFactor(TreeNode* node) {
    if (!node) return 0;
    int heightDifference = getHeight(node->left) - getHeight(node->right);
    return heightDifference;
}

TreeNode* leftRotation (TreeNode* node) {
    TreeNode* leftr1 = node->right;
    TreeNode* leftr2 = leftr1->left;
    leftr1->left = node;
    node->right = leftr2;

    leftr1->height = 1 + max(getHeight(leftr1->left), getHeight(leftr1->right));
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return leftr1;
}

TreeNode* rightRotation (TreeNode* node) {
    TreeNode* rightr1 = node->left;
    TreeNode* rightr2 = rightr1->right;
    rightr1->right = node;
    node->left = rightr2;

    rightr1->height = 1 + max(getHeight(rightr1->left), getHeight(rightr1->right));
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return rightr1;
}

TreeNode* insert(TreeNode*& root, int key) {
    if (!root) return new TreeNode(key);

    if (key == root->value) return root;
    else if (key < root->value) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = balanceFactor(root);
    //LEFT-LEFT
    if (balance > 1 && key < root->left->value) return rightRotation(root);
    //RIGHT-RIGHT
    if (balance < -1 && key > root->right->value) return leftRotation(root);
    //RIGHT-LEFT
    if (balance < -1 && key < root->right->value) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    //LEFT-RIGHT
    if (balance > 1 && key > root->left->value) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    return root;
}

