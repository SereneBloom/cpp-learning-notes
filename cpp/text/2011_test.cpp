// 2011 真题测试文件：穷举 + 随机，同时验证 ans（归并）与 ans2（双指针计数）
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2011.exe 2011_test.cpp
//       然后运行 test2011.exe
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "2011.cpp"        // 引入被测函数 ans()、ans2()

int passCnt = 0, failCnt = 0;

void printArr(const char *tag, const int *a, int n) {
    cout << tag << "[";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "]";
}

// 一个用例：两个升序数组、长度、期望的中位数
void check(const string &name, int *A, int *B, int n, int exp) {
    int r1 = ans(A, B, n);
    int r2 = ans2(A, B, n);
    bool ok = (r1 == exp) && (r2 == exp);
    if (ok) {
        passCnt++;
    } else {
        failCnt++;
        cout << "[失败] " << name << "  n=" << n
             << "  ans=" << r1 << "  ans2=" << r2 << "  期望=" << exp << "  ";
        printArr("A=", A, n);
        cout << "  ";
        printArr("B=", B, n);
        cout << endl;
    }
}

int main() {
    cout << "===== 2011 真题：两升序序列的中位数 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    {
        int A[] = {1, 2, 3}, B[] = {4, 5, 6};
        check("A 全部小于 B", A, B, 3, 3);            // 合并 1..6，第 3 小 = 3
    }
    {
        int A[] = {4, 5, 6}, B[] = {1, 2, 3};
        check("B 全部小于 A", A, B, 3, 3);
    }
    {
        int A[] = {1, 3, 5, 7}, B[] = {2, 4, 6, 8};
        check("完全交错", A, B, 4, 4);                 // 合并 1..8，第 4 小 = 4
    }
    {
        int A[] = {11, 13, 15, 17, 19}, B[] = {2, 4, 6, 8, 20};
        check("含极端值", A, B, 5, 11);
    }
    {
        int A[] = {1}, B[] = {2};
        check("n = 1", A, B, 1, 1);
    }
    {
        int A[] = {5, 5, 5}, B[] = {5, 5, 5};
        check("全部相同", A, B, 3, 5);
    }
    {
        int A[] = {-5, -1, 3}, B[] = {-10, 0, 9};
        check("含负数", A, B, 3, -1);                  // 合并 -10 -5 -1 0 3 9，第 3 小 = -1
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、穷举所有交错方式 ----------
    // n 个元素的两条升序序列，恰好把 {0..2n-1} 分成两半，共有 C(2n, n) 种分法
    // 合并后必然是 0..2n-1，第 n 小恒为 n-1
    int exTotal = 0;
    for (int n = 1; n <= 6; n++) {
        int m = 2 * n;
        for (int mask = 0; mask < (1 << m); mask++) {
            if (__builtin_popcount(mask) != n) continue;
            int A[8], B[8], ia = 0, ib = 0;
            for (int v = 0; v < m; v++) {
                if ((mask >> v) & 1) A[ia++] = v;
                else                 B[ib++] = v;
            }
            check("穷举交错", A, B, n, n - 1);
            exTotal++;
        }
    }
    cout << "穷举交错：" << exTotal << " 个用例，累计通过 " << passCnt
         << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 三、随机用例（含重复值、负数） ----------
    srand(2011);                       // 固定种子，结果可复现
    int rndTotal = 0;
    for (int t = 0; t < 5000; t++) {
        int n = 1 + rand() % 8;
        int A[8], B[8], C[16];
        for (int i = 0; i < n; i++) {
            A[i] = rand() % 21 - 10;   // -10 ~ 10，必然出现重复值
            C[i] = A[i];
        }
        for (int i = 0; i < n; i++) {
            B[i] = rand() % 21 - 10;
            C[n + i] = B[i];
        }
        sort(A, A + n);
        sort(B, B + n);
        sort(C, C + 2 * n);            // 标准答案：合并排序后取第 n 小
        check("随机", A, B, n, C[n - 1]);
        rndTotal++;
    }
    cout << "随机用例：" << rndTotal << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
