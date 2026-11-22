// 2018 真题测试文件：数组中未出现的最小正整数
// g++ -std=c++11 -Wall -pedantic -fexec-charset=GBK -o test2018.exe 2018_test.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "2018.cpp"

int passCnt = 0, failCnt = 0;

// 独立标准答案：标记数组
int refAns(int A[], int n){
    bool *B = new bool[n + 2]();
    for (int i = 0; i < n; i++)
        if (A[i] >= 1 && A[i] <= n) B[A[i]] = true;
    int r = 1;
    while (r <= n && B[r]) r++;
    delete[] B;
    return r;
}

void printArr(int A[], int n){
    cout << "[";
    for (int i = 0; i < n; i++){ if (i) cout << " "; cout << A[i]; }
    cout << "]";
}

void run(const char *name, int src[], int n, bool show){
    int A[256];
    memcpy(A, src, sizeof(int) * n);
    int want = refAns(src, n);
    int got = ans(A, n);
    if (got == want){
        passCnt++;
        if (show){
            cout << "[通过] " << name << "  输入=";
            printArr(src, n);
            cout << " 结果=" << got << endl;
        }
    } else {
        failCnt++;
        cout << "[失败] " << name << "  输入=";
        printArr(src, n);
        cout << " 结果=" << got << " 期望=" << want << endl;
    }
}

int main(){
    cout << "===== 2018 真题：未出现的最小正整数 测试 =====" << endl;

    { int a[] = {1, 2, 3};                   run("A {1,2,3}", a, 3, true); }
    { int a[] = {-1, 2, 3};                  run("B {-1,2,3}", a, 3, true); }
    { int a[] = {0};                         run("C {0}", a, 1, true); }
    { int a[] = {5, 6, 7};                   run("D {5,6,7}", a, 3, true); }
    { int a[] = {1, 1, 1};                   run("E {1,1,1}（原版崩溃点）", a, 3, true); }
    { int a[] = {3, 4, -1, 1};               run("F {3,4,-1,1}", a, 4, true); }
    { int a[] = {2, 3, 4};                   run("G {2,3,4}", a, 3, true); }
    { int a[] = {1, 2, 3, 4};                run("H {1,2,3,4}", a, 4, true); }
    { int a[] = {2, 2, 2};                   run("I {2,2,2}", a, 3, true); }
    { int a[] = {7, 8, 9, 11, 12};           run("J 官方样例 {7,8,9,11,12}", a, 5, true); }
    { int a[] = {-5, -3, 0, 1};              run("K 负数为主", a, 4, true); }
    { int a[] = {1};                         run("L {1}", a, 1, true); }
    { int a[] = {-1};                        run("M {-1}", a, 1, true); }
    { int a[] = {1, 2, 3, 5, 6};             run("N 缺 4", a, 5, true); }
    { int a[] = {2, 1, 4, 3, 6, 5};          run("O 乱序 1..6 缺 7", a, 6, true); }
    { int a[] = {100, 1, 2};                 run("P 大值 + 1,2", a, 3, true); }

    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // 随机对照
    srand(2018);
    int rPass = 0, rFail = 0;
    for (int t = 0; t < 3000; t++){
        int n = 1 + rand() % 20;
        int a[256];
        for (int i = 0; i < n; i++) a[i] = rand() % 31 - 10;   // -10 ~ 20
        int want = refAns(a, n);
        int got = ans(a, n);
        if (got == want) rPass++;
        else {
            rFail++;
            if (rFail <= 3){
                cout << "[随机失败] n=" << n << " got=" << got << " want=" << want << endl;
            }
        }
    }
    cout << "随机用例：通过 " << rPass << " 个，失败 " << rFail << " 个" << endl;
    cout << "===== 通过 " << (passCnt + rPass) << " 个，失败 " << (failCnt + rFail) << " 个 =====" << endl;
    return (failCnt + rFail) == 0 ? 0 : 1;
}
