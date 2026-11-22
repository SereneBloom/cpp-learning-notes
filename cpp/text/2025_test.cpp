// 2025 真题测试文件：每个元素与其他元素乘积的最大值
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2025.exe 2025_test.cpp
//       然后运行 test2025.exe
#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

#include "2025.cpp"        // 引入被测函数 calMulMax()

int passCnt = 0, failCnt = 0;

// 独立的标准答案：最朴素的双层循环，j 跑遍所有下标（正确性最不依赖技巧）
vector<int> brute(const vector<int> &a) {
    int n = (int)a.size();
    vector<int> r(n, INT_MIN);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            long long v = (long long)a[i] * a[j];
            if (v > r[i]) r[i] = (int)v;
        }
    }
    return r;
}

void printVec(const vector<int> &v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << " ";
        cout << v[i];
    }
    cout << "]";
}

bool check(const string &name, const vector<int> &a) {
    int n = (int)a.size();
    int A[64], R[64];
    for (int i = 0; i < n; i++) { A[i] = a[i]; R[i] = 12345; }   // 故意填脏值
    calMulMax(A, R, n);
    vector<int> got(R, R + n);
    vector<int> exp = brute(a);
    if (got == exp) {
        passCnt++;
        if (passCnt <= 30) {           // 只用前 30 条打印明细，避免刷屏
            cout << "[通过] " << name << "  输入=";
            printVec(a);
            cout << " 输出=";
            printVec(got);
            cout << endl;
        }
        return true;
    }
    failCnt++;
    cout << "[失败] " << name << "  输入=";
    printVec(a);
    cout << "\n        返回=";
    printVec(got);
    cout << "\n        期望=";
    printVec(exp);
    cout << endl;
    return false;
}

int main() {
    cout << "===== 2025 真题：每元素与其他元素乘积最大值 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    {
        int t[] = {1, 2, 3};
        check("基本正数", vector<int>(t, t + 3));
    }
    {
        int t[] = {3, 1, 2};
        check("乱序正数", vector<int>(t, t + 3));
    }
    {
        int t[] = {-1, -5, 2};
        check("两负一正（负数乘负数得正）", vector<int>(t, t + 3));
    }
    {
        int t[] = {-10, -9, 1};
        check("负负得正的极端", vector<int>(t, t + 3));
    }
    {
        int t[] = {5, -2, 3, -7};
        check("正负混合", vector<int>(t, t + 4));
    }
    {
        int t[] = {-3, -2, -1};
        check("全负数", vector<int>(t, t + 3));
    }
    {
        int t[] = {7, 7, 7};
        check("全部相同", vector<int>(t, t + 3));
    }
    {
        int t[] = {0, 5};
        check("含 0（两个元素）", vector<int>(t, t + 2));
    }
    {
        int t[] = {0, 0, 3};
        check("多个 0", vector<int>(t, t + 3));
    }
    {
        int t[] = {-1, 0, 1};
        check("负零正", vector<int>(t, t + 3));
    }
    {
        int t[] = {1000, -1000, 999};
        check("较大值", vector<int>(t, t + 3));
    }
    {
        int t[] = {2, 5};
        check("只有两个元素", vector<int>(t, t + 2));
    }
    {
        int t[] = {-4, 0};
        check("负数加 0", vector<int>(t, t + 2));
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、随机用例 ----------
    srand(2025);
    int rndTotal = 0;
    for (int t = 0; t < 3000; t++) {
        int n = 2 + rand() % 11;               // 2 ~ 12
        vector<int> a;
        for (int i = 0; i < n; i++) a.push_back(rand() % 201 - 100);   // -100 ~ 100
        check("随机", a);
        rndTotal++;
    }
    cout << "随机用例：" << rndTotal << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
