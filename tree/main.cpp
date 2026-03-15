#include "AVL.h"
#include <raylib.h>
int main() {
    TreeNode* root = nullptr;
    int x;
    while (cin >> x) {
        if (x == -1) break;
        root = insert(root, x);
        preorder(root);
        cout << endl;
    }
    return 0;
}
