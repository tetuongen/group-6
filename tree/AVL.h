#pragma once
#include <iostream>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int key) {
        value = key;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getHeight (TreeNode* node);
int balanceFactor(TreeNode* node);
TreeNode* leftRotation (TreeNode* node);
TreeNode* rightRotation (TreeNode* node);
TreeNode* insert(TreeNode*& root, int key);
void preorder(TreeNode* root);