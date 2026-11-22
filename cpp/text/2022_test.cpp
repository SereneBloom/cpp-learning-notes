// 2022 真题测试文件：判断顺序存储的二叉树是否为二叉搜索树
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2022.exe 2022_test.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "2022.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

// 独立参考实现：上下界法（与中序法思路不同，可交叉验证）
bool refCheck(int a[], int n, int k, long long lo, long long hi){
    if (k >= n || a[k] == -1) return true;
    if (a[k] <= lo || a[k] >= hi) return false;
    return refCheck(a, n, 2 * k + 1, lo, a[k]) &&
           refCheck(a, n, 2 * k + 2, a[k], hi);
}
bool refAns(int a[], int n){
    return refCheck(a, n, 0, INT_MIN, INT_MAX);
}

void printArr(int a[], int n){
    cout << "[";
    for (int i = 0; i < n; i++){
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "]";
}

void check(const string &name, int a[], int n, bool show){
    SqBiTree T;
    for (int i = 0; i < n; i++) T.SqBiTNode[i] = a[i];
    T.ElemNum = n;

    int save[64];
    for (int i = 0; i < n; i++) save[i] = a[i];      // 备份，用于检测数据是否被改

    bool got = ans(&T);
    bool exp = refAns(a, n);

    bool dataOk = true;
    for (int i = 0; i < n; i++) if (T.SqBiTNode[i] != save[i]) dataOk = false;

    if (got == exp && dataOk){
        passCnt++;
        if (show){
            cout << "[通过] " << name << "  输入=";
            printArr(a, n);
            cout << " 结果=" << (got ? "是BST" : "非BST") << endl;
        }
    } else {
        failCnt++;
        cout << "[失败] " << name << "  输入=";
        printArr(a, n);
        cout << "\n        结果=" << (got ? "是BST" : "非BST")
             << "  期望=" << (exp ? "是BST" : "非BST");
        if (!dataOk) cout << "\n        注意：函数修改了原始数据！";
        cout << endl;
    }
}

int main(){
    cout << "===== 2022 真题：顺序存储二叉树判 BST 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    {
        int a[] = {10, 5, 15};
        check("合法 BST 10(5,15)", a, 3, true);
    }
    {
        int a[] = {10, 5, 15, -1, -1, 6};
        check("跨层违规 10(5,15(6))", a, 6, true);
    }
    {
        int a[] = {10, 5, 15, -1, -1, 12};
        check("合法 10(5,15(12))", a, 6, true);
    }
    {
        int a[] = {5, -1, 4, -1, -1, 3, 6};
        check("跨层违规 5(-,4(3,6))", a, 7, true);
    }
    {
        int a[] = {3};
        check("单结点", a, 1, true);
    }
    {
        int a[] = {-1};
        check("全空（只有空根）", a, 1, true);
    }
    {
        int a[] = {10, 5, -1, 3, 8};
        check("缺右孩子 10(5(3,8))", a, 5, true);
    }
    {
        int a[] = {10, 5, 15, -1, -1, 15};
        check("重复值（右孩子等于根）", a, 6, true);
    }
    {
        int a[] = {10, -1, 15, -1, -1, 12, 20};
        check("右斜链 10(-,15(12,20))", a, 7, true);
    }
    {
        int a[] = {20, 10, 30, 5, 15, 25, 35};
        check("满二叉树（合法）", a, 7, true);
    }
    {
        int a[] = {20, 10, 30, 5, 15, 25, 35, -1, -1, -1, -1, -1, -1, 36, -1};
        check("深层违规（右右子树 36 > 30 但挂在 35 下）", a, 15, true);
    }
    {
        int a[] = {1, 2, 3, 4, 5, 6, 7};
        check("层次递增但非 BST", a, 7, true);
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、随机用例 ----------
    srand(2022);
    int rnd = 0;
    for (int t = 0; t < 3000; t++){
        int n = 1 + rand() % 15;                  // 1 ~ 15
        int a[64];
        for (int i = 0; i < n; i++) a[i] = -1;
        a[0] = 1 + rand() % 50;
        for (int i = 1; i < n; i++){
            int par = (i - 1) / 2;
            if (a[par] == -1) a[i] = -1;          // 父空则子必空
            else a[i] = (rand() % 100 < 70) ? (1 + rand() % 50) : -1;
        }
        check("随机", a, n, false);
        rnd++;
    }
    cout << "随机用例：" << rnd << " 个" << endl;

    // ---------- 三、构造合法 BST ----------
    int bst = 0;
    for (int t = 0; t < 1000; t++){
        int n = 1 + rand() % 15;
        int a[64];
        for (int i = 0; i < n; i++) a[i] = -1;
        // 先随机决定哪些位置有结点（父空则子空）
        int has[64] = {0};
        has[0] = 1;
        for (int i = 1; i < n; i++){
            int par = (i - 1) / 2;
            if (has[par] && rand() % 100 < 70) has[i] = 1;
        }
        // 生成中序序列，按序列顺序填入严格递增的值 → 必然构成合法 BST
        vector<int> seq;
        {
            struct L {
                static void go(int a_has[], int n_, int k, vector<int> &out){
                    if (k >= n_ || !a_has[k]) return;
                    go(a_has, n_, 2 * k + 1, out);
                    out.push_back(k);
                    go(a_has, n_, 2 * k + 2, out);
                }
            };
            L::go(has, n, 0, seq);
        }
        int v = 1;
        for (size_t k = 0; k < seq.size(); k++){
            a[seq[k]] = v;
            v += 1 + rand() % 3;                  // 严格递增
        }
        check("构造 BST", a, n, false);
        bst++;
    }
    cout << "构造用例：" << bst << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
