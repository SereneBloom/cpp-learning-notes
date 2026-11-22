// 2010 真题测试文件：穷举 n 与 p 的所有组合
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2010.exe 2010_test.cpp
//       然后运行 test2010.exe
#include <iostream>
using namespace std;

#include "2010.cpp"        // 引入被测函数 ans()

const int CAP = 32;        // 实际数组容量，远大于用到的 n
const int SENTINEL = -999; // 哨兵值，用来发现越界写入

int passCnt = 0, failCnt = 0;

void printArr(const char *tag, const int *a, int n) {
    cout << tag << "[";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "]";
}

// 对给定的 n、p 跑一次，并检查结果
void checkCase(int n, int p) {
    int R[CAP], exp[CAP];

    // 造数据：值取 10, 20, 30 ... 便于肉眼分辨
    for (int i = 0; i < CAP; i++) R[i] = SENTINEL;
    for (int i = 0; i < n; i++) R[i] = (i + 1) * 10;

    // 期望结果：循环左移 p 位
    for (int i = 0; i < n; i++) exp[i] = R[(i + p) % n];

    ans(R, p, n);

    // ① 比较结果
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (R[i] != exp[i]) { ok = false; break; }
    }
    // ② 检查 n 之后有没有被越界写坏
    bool overflow = false;
    for (int i = n; i < CAP; i++) {
        if (R[i] != SENTINEL) { overflow = true; break; }
    }

    if (ok && !overflow) {
        passCnt++;
    } else {
        failCnt++;
        cout << "[失败] n=" << n << " p=" << p << "  ";
        printArr("实际", R, n);
        cout << "  ";
        printArr("期望", exp, n);
        if (overflow) cout << "  << 发生越界写入 >>";
        cout << endl;
    }
}

int main() {
    cout << "===== 2010 真题：循环左移 p 位 测试 =====" << endl;

    // n 从 2 到 10，p 取 1 到 n-1，穷举全部合法输入
    for (int n = 2; n <= 10; n++) {
        for (int p = 1; p < n; p++) {
            checkCase(n, p);
        }
    }

    // 边界补充：n=2 p=1（最小合法输入）
    // 已在上面覆盖，这里再单独测一组特殊值：全相同、含负数
    {
        int R[CAP];
        for (int i = 0; i < CAP; i++) R[i] = SENTINEL;
        for (int i = 0; i < 5; i++) R[i] = 7;          // 全相同
        ans(R, 2, 5);
        bool ok = true;
        for (int i = 0; i < 5; i++) if (R[i] != 7) ok = false;
        cout << (ok ? "[通过] " : "[失败] ") << "n=5 p=2 全部元素相同" << endl;
        if (ok) passCnt++; else failCnt++;
    }
    {
        int R[CAP] = {SENTINEL};
        for (int i = 0; i < CAP; i++) R[i] = SENTINEL;
        int orig[5] = {-5, -3, -1, 2, 4};
        for (int i = 0; i < 5; i++) R[i] = orig[i];
        ans(R, 3, 5);
        bool ok = true;
        for (int i = 0; i < 5; i++) if (R[i] != orig[(i + 3) % 5]) ok = false;
        cout << (ok ? "[通过] " : "[失败] ") << "n=5 p=3 含负数" << endl;
        if (ok) passCnt++; else failCnt++;
    }

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
