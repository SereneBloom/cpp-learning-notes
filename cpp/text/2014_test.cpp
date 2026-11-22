// 2014 真题测试文件：二叉树的带权路径长度 WPL
// 定义：所有叶结点的 (权值 × 根到该叶结点的边数) 之和，根结点深度为 0
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2014.exe 2014_test.cpp
//       然后运行 test2014.exe
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#include "2014.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

// 建结点
TreeNode *node(int w, TreeNode *l = NULL, TreeNode *r = NULL) {
    TreeNode *t = new TreeNode;
    t->weight = w;
    t->left = l;
    t->right = r;
    return t;
}

void freeTree(TreeNode *T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    delete T;
}

// 暴力标准答案：先收集所有叶子的权值和深度，再逐个相乘求和
void collectLeaves(TreeNode *T, int deep, vector<int> &ws, vector<int> &ds) {
    if (T == NULL) return;
    if (T->left == NULL && T->right == NULL) {
        ws.push_back(T->weight);
        ds.push_back(deep);
        return;
    }
    collectLeaves(T->left, deep + 1, ws, ds);
    collectLeaves(T->right, deep + 1, ws, ds);
}

int bruteWpl(TreeNode *T) {
    vector<int> ws, ds;
    collectLeaves(T, 0, ws, ds);
    int s = 0;
    for (size_t i = 0; i < ws.size(); i++) s += ws[i] * ds[i];
    return s;
}

// 随机生成恰好 n 个结点的二叉树
TreeNode *buildRandom(int n) {
    if (n <= 0) return NULL;
    TreeNode *t = node(rand() % 10);
    if (n == 1) return t;
    int leftCnt = rand() % n;             // 0 ~ n-1
    int rightCnt = n - 1 - leftCnt;
    t->left = buildRandom(leftCnt);
    t->right = buildRandom(rightCnt);
    return t;
}

void check(const string &name, TreeNode *T, int exp) {
    int got = ans(T);
    if (got == exp) {
        passCnt++;
        cout << "[通过] " << name << "  WPL=" << got << endl;
    } else {
        failCnt++;
        cout << "[失败] " << name << "  返回=" << got
             << "  期望=" << exp << endl;
    }
    freeTree(T);
}

int main() {
    cout << "===== 2014 真题：二叉树 WPL 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    // 1. 单结点：根自己就是叶子，边数为 0
    check("单结点(权 7)", node(7), 0);

    // 2. 根 + 一个左孩子
    check("根(10) + 左叶(5)", node(10, node(5)), 5);

    // 3. 三结点满二叉树：两个叶子各在第 1 层
    check("三结点 1(2,3)", node(1, node(2), node(3)), 5);

    // 4. 题面示例树：10(5, 20(8,9))
    check("10(5, 20(8,9))", node(10, node(5), node(20, node(8), node(9))), 39);

    // 5. 左链 4 层：只有最深处一个叶子
    check("左链 1-2-3-4", node(1, node(2, node(3, node(4)))), 12);

    // 6. 右链 3 层
    check("右链 1-2-3", node(1, NULL, node(2, NULL, node(3))), 6);

    // 7. 七结点满二叉树：4 个叶子都在第 2 层
    check("七结点满二叉树",
          node(1, node(2, node(4), node(5)), node(3, node(6), node(7))),
          (4 + 5 + 6 + 7) * 2);

    // 8. 叶子权值为 0
    check("叶子权值为 0", node(9, node(0), node(3)), 3);

    // 9. 内部结点权值很大，但不应计入
    check("内部结点权值很大", node(1000, node(1), node(2)), 3);

    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、随机用例 ----------
    srand(2014);
    int rndTotal = 0;
    for (int t = 0; t < 3000; t++) {
        int n = 1 + rand() % 12;
        TreeNode *T = buildRandom(n);
        int got = ans(T);
        int exp = bruteWpl(T);
        if (got == exp) {
            passCnt++;
        } else {
            failCnt++;
            cout << "[失败] 随机树 n=" << n << "  返回=" << got
                 << "  期望=" << exp << endl;
        }
        freeTree(T);
        rndTotal++;
    }
    cout << "随机用例：" << rndTotal << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
