// 第 11 课：二叉树定义与三种递归遍历
#include <iostream>
using namespace std;

// 二叉链表结点：数据 + 左孩子 + 右孩子
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

// 按「先序」输入建立二叉树，-1 表示该位置为空
// 例：1 2 -1 -1 3 4 -1 -1 5 -1 -1
// 结构：1 的左孩子是 2，右孩子是 3；3 的左孩子是 4，右孩子是 5
TreeNode *createTree() {
    int x;
    cin >> x;
    if (x == -1) return NULL;
    TreeNode *t = new TreeNode;
    t->data = x;
    t->left = createTree();
    t->right = createTree();
    return t;
}

// 先序：根 -> 左 -> 右
void preOrder(TreeNode *t) {
    if (t == NULL) return;
    cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

// 中序：左 -> 根 -> 右
void inOrder(TreeNode *t) {
    if (t == NULL) return;
    inOrder(t->left);
    cout << t->data << " ";
    inOrder(t->right);
}

// 后序：左 -> 右 -> 根
void postOrder(TreeNode *t) {
    if (t == NULL) return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << " ";
}

// 后序释放：先释放左右子树，再释放自己
void freeTree(TreeNode *t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

int main() {
    cout << "请按先序输入结点值，-1 表示空：" << endl;
    cout << "例如 1 2 -1 -1 3 4 -1 -1 5 -1 -1" << endl;
    TreeNode *root = createTree();

    cout << "前序遍历：";
    preOrder(root);
    cout << endl;

    cout << "中序遍历：";
    inOrder(root);
    cout << endl;

    cout << "后序遍历：";
    postOrder(root);
    cout << endl;

    freeTree(root);
    root = NULL;
    return 0;
}
