// 第 01 课：练习
// 练习 1：读入两个整数 a、b，分三行输出 a + b、a - b、a * b。
// 练习 2：读入一个小数 r，输出半径 r 的圆周长 2 * 3.14159 * r。

#include <iostream>
using namespace std;

int main() {
    // TODO: 在这里写你的答案
    int a, b;
    cout << "练习 1：请输入两个整数 a b：" << endl;
    cin >> a >> b;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    double r;
    cout << "练习 2：请输入半径 r：" << endl;
    cin >> r;
    cout << 2 * 3.14159 * r << endl;
    return 0;
}
