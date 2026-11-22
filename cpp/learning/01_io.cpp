// 第 01 课：第一个程序与输入输出
// 目标：能编译运行，会用 cout / cin，认识 int double char string

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 1. 输出：cout 用 << 把内容送出去，endl 表示换行并刷新
    cout << "Hello, 408!" << endl;

    // 2. 变量：先给类型，再给名字，可以同时赋值
    int age = 21;
    double score = 89.5;
    char grade = 'A';
    string name = "Tom";

    // 3. 输出变量：可以连着写多个 <<
    cout << name << " " << age << " " << score << " " << grade << endl;

    // 4. 输入：cin 用 >> 把数据读进变量，多个变量可以一次读完
    int a, b;
    cout << "请输入两个整数 a b：" << endl;
    cin >> a >> b;
    cout << a + b << endl;

    // 5. 输入字符串：遇到空格或换行就停
    string s;
    cout << "请输入一个不含空格的单词：" << endl;
    cin >> s;
    cout << "s = " << s << endl;

    return 0;
}
