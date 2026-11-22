#include <iostream>
using namespace std;

struct TreeNode{
    int weight;
    TreeNode *left;
    TreeNode *right;
};

// 辅助函数：deep 表示根到当前结点经过的边数，根结点为 0
int wpl(TreeNode *T, int deep){
    if(T == NULL){
        return 0;
    }
    // 只有叶子结点参与计算：权值 × 路径长度
    if(T->left == NULL && T->right == NULL){
        return T->weight * deep;
    }
    return wpl(T->left, deep + 1) + wpl(T->right, deep + 1);
}

int ans(TreeNode * T){
    // 原错误写法：把所有结点的权值直接相加
    //   int l = ans(T->left);
    //   int r = ans(T->right);
    //   return(T->weight + l + r);
    // 错误 1：只该累加叶结点，内部结点不计入
    // 错误 2：叶结点的权值还要乘以路径长度（边数）
    // 错误 3：函数没有深度参数，无法知道当前在第几层
    return wpl(T, 0);          // 根结点深度为 0（按边数定义）
}
