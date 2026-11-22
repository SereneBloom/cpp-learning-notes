// 第 02 课：条件分支
// 目标：会用 if / else if / else、逻辑运算 && || !、switch

#include <iostream>
using namespace std;

int main() {
    // 1. 最简单的一分为二：判断奇偶
    int n;
    cout << "请输入一个整数 n（判断奇偶）：" << endl;
    cin >> n;
    if (n % 2 == 0)
        cout << "even" << endl;
    else
        cout << "odd" << endl;

    // 2. 多个区间：成绩等级，从上往下判断，命中一个就走人
    int score;
    cout << "请输入成绩 score（0~100）：" << endl;
    cin >> score;
    if (score >= 90)
        cout << "A" << endl;
    else if (score >= 80)
        cout << "B" << endl;
    else if (score >= 60)
        cout << "C" << endl;
    else
        cout << "D" << endl;

    // 3. 组合条件：闰年 = 能被 4 整除且不能被 100 整除，或者能被 400 整除
    int y;
    cout << "请输入年份 y（判断闰年）：" << endl;
    cin >> y;
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
        cout << "leap" << endl;
    else
        cout << "not leap" << endl;

    // 4. switch：按值跳转，适合固定几个选项
    char op;
    cout << "请输入一个运算符（+ 或 -）：" << endl;
    cin >> op;
    switch (op) {
        case '+':
            cout << "add" << endl;
            break;
        case '-':
            cout << "sub" << endl;
            break;
        default:
            cout << "other" << endl;
            break;
    }

    return 0;
}
