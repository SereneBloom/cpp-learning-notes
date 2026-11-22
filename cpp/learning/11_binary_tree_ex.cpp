// 第 11 课练习：二叉树的递归遍历与基本统计
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

// 按先序输入建树，-1 表示空（已给出）
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

void freeTree(TreeNode *t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

// 练习 1：三种递归遍历（只输出结点值，用空格分隔）
void preOrder(TreeNode *t) {
    if (t == NULL) return;          // 原写法缺出口，空指针会崩
    cout << t->data << " " ;
    preOrder(t->left);
    preOrder(t->right);
}

void inOrder(TreeNode *t) {
    if (t == NULL) return;          // 原写法缺出口
    inOrder(t->left);
    cout << t->data << " " ;
    inOrder(t->right);
}

void postOrder(TreeNode *t) {
    if (t == NULL) return;          // 原写法缺出口
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << " " ;
}

// 练习 2：统计结点总数
int countNodes(TreeNode *t) {
    // 原写法：if(t->left == NULL) 才递归，条件反了；右子树结果还赋给了 l
    if (t == NULL) return 0;
    return 1 + countNodes(t->left) + countNodes(t->right);
}

// 练习 2：统计叶子结点数（左右孩子都为空的结点）
int countLeaves(TreeNode *t) {
    // 原写法：缺空树判断，且 if(t->left == NULL) 才递归，条件反了
    if (t == NULL) return 0;
    if (t->left == NULL && t->right == NULL) return 1;   // 叶子自己算 1
    return countLeaves(t->left) + countLeaves(t->right);
}

// 练习 3：求树的高度（空树为 0，只有根为 1）
int treeDepth(TreeNode *t) {
    // TODO
    if(t == NULL){
        return 0;
    }
    int m = max(treeDepth(t->left), treeDepth(t->right));
    return m + 1;
}

// 练习 4：交换每个结点的左右子树
void swapChildren(TreeNode *t) {
    // TODO：空树直接返回；否则交换 t->left、t->right，再递归两棵子树
    if(t == NULL){
        return ;
    }
    TreeNode *l = t->left;
    TreeNode *r = t->right;
    t->left = r;
    t->right = l;
    swapChildren(t->left);
    swapChildren(t->right);
    return ;
}

int main() {
    cout << "请按先序输入结点值，-1 表示空：" << endl;
    cout << "例如 1 2 -1 -1 3 4 -1 -1 5 -1 -1" << endl;
    TreeNode *root = createTree();

    cout << "前序：";
    preOrder(root);
    cout << endl;
    cout << "中序：";
    inOrder(root);
    cout << endl;
    cout << "后序：";
    postOrder(root);
    cout << endl;

    cout << "结点数：" << countNodes(root) << endl;
    cout << "叶子数：" << countLeaves(root) << endl;
    cout << "深度：" << treeDepth(root) << endl;

    // 练习 4：交换左右子树后，前序应与原中序的镜像关系，先看中序变化
    swapChildren(root);
    cout << "交换左右子树后中序：";
    inOrder(root);
    cout << endl;

    freeTree(root);
    root = NULL;
    return 0;
}
