// 第 03 课：循环
// 目标：会用 for / while / do-while、break / continue、嵌套循环

#include <iostream>
using namespace std;

int main() {
    // 1. for：次数已知，1 加到 n
    int n;
    cout << "请输入 n（求 1 到 n 的和）：" << endl;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    cout << "sum = " << sum << endl;

    // 2. while：次数未知，靠条件决定什么时候停
    int x;
    cout << "请输入一个正整数 x（数它有多少位）：" << endl;
    cin >> x;
    int cnt = 0;
    while (x > 0) {
        cnt++;
        x = x / 10;
    }
    cout << "digits = " << cnt << endl;

    // 3. do-while：先做一次，再判断要不要继续
    int m;
    cout << "请输入 m（do-while 打印 m 次）：" << endl;
    cin >> m;
    do {
        cout << "run once" << endl;
        m--;
    } while (m > 0);

    // 4. break 直接跳出，continue 跳过本次
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0)
            continue;
        if (i > 7)
            break;
        cout << i << " ";
    }
    cout << endl;

    // 5. 嵌套循环：外层管行，内层管列
    int h, w;
    cout << "请输入行数 h 和列数 w（打印矩形）：" << endl;
    cin >> h >> w;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
