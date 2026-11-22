// 2013 真题测试文件：找主元素（出现次数 > n/2）
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2013.exe 2013_test.cpp
//       然后运行 test2013.exe
#include <iostream>
#include <cstdlib>
using namespace std;

#include "2013.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

// 暴力标准答案：逐个数字数出现次数
int brute(int *A, int n) {
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) {
            if (A[j] == A[i]) c++;
        }
        if (c > n / 2) return A[i];
    }
    return -1;
}

void printArr(const int *a, int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "]";
}

void check(const string &name, int *A, int n, int exp) {
    int got = ans(A, n);
    if (got == exp) {
        passCnt++;
    } else {
        failCnt++;
        cout << "[失败] " << name << "  n=" << n << "  ";
        printArr(A, n);
        cout << "  返回=" << got << "  期望=" << exp << endl;
    }
}

// 手写用例：名称、数组、长度、期望值（均由 brute 反推，避免手算失误）

int main() {
    cout << "===== 2013 真题：主元素 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    {
        int A[] = {0};
        check("n=1 单元素", A, 1, 0);                    // 1 > 0，是主元素
    }
    {
        int A[] = {1, 1};
        check("n=2 两个相同", A, 2, 1);                  // 2 > 1
    }
    {
        int A[] = {1, 2};
        check("n=2 两个不同", A, 2, -1);                 // 1 不大于 1
    }
    {
        int A[] = {1, 1, 2, 2};
        check("n=4 恰好各占一半", A, 4, -1);             // 2 > 2 不成立，边界
    }
    {
        int A[] = {1, 1, 2, 1};
        check("n=4 三个相同", A, 4, 1);                  // 3 > 2
    }
    {
        int A[] = {3, 3, 3, 1, 2};
        check("n=5 奇数长度", A, 5, 3);                  // 3 > 2
    }
    {
        int A[] = {1, 2, 3, 4, 5};
        check("n=5 全不相同", A, 5, -1);
    }
    {
        int A[] = {2, 2, 2, 2, 3, 4};
        check("n=6 四个相同", A, 6, 2);                  // 4 > 3
    }
    {
        int A[] = {1, 2, 3, 9, 9, 9, 9};
        check("n=7 主元素在末尾", A, 7, 9);              // 4 > 3
    }
    {
        int A[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
        check("n=10 全部相同", A, 10, 4);
    }
    {
        int A[] = {0, 1, 0, 2, 3, 0, 4, 0, 5, 0, 0};
        check("n=11 主元素是 0（下标边界）", A, 11, 0);   // 6 > 5
    }
    {
        int A[] = {6, 6, 1, 2, 3, 6, 6};
        check("n=7 主元素是 n-1（下标上界）", A, 7, 6);   // 4 > 3
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、随机用例 ----------
    // 题面限定 0 <= ai < n，随机值也按此范围生成
    srand(2013);
    int rndTotal = 0;
    for (int t = 0; t < 5000; t++) {
        int n = 1 + rand() % 20;
        int A[20];
        for (int i = 0; i < n; i++) A[i] = rand() % n;
        check("随机", A, n, brute(A, n));
        rndTotal++;
    }
    cout << "随机用例：" << rndTotal << " 个" << endl;

    // ---------- 三、构造"有主元素"的随机用例 ----------
    // 保证某个值出现超过 n/2 次，验证一定能找到
    int mainTotal = 0;
    for (int t = 0; t < 2000; t++) {
        int n = 1 + rand() % 20;
        int A[20];
        for (int i = 0; i < n; i++) A[i] = rand() % n;
        int target = rand() % n;
        // 用 target 覆盖超过一半的位置
        int need = n / 2 + 1;
        for (int i = 0; i < need && i < n; i++) {
            int pos = rand() % n;
            A[pos] = target;
        }
        check("构造有主元素", A, n, brute(A, n));
        mainTotal++;
    }
    cout << "构造用例：" << mainTotal << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
