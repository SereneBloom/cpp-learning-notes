// 第 07 课：综合复习
// 目标：getline 读整行、多组输入 while (cin >> x)、把前面知识串起来

#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int score;
};

int main() {
    // 1. getline：一次读一整行，空格也算内容
    string line;
    cout << "请输入一行文字（可以带空格）：" << endl;
    getline(cin, line);
    cout << "读到：" << line << "，长度 " << line.size() << endl;

    // 2. cin >>：只读一个词，遇到空格或换行就停
    string word;
    cout << "请输入一个单词：" << endl;
    cin >> word;
    cout << "读到：" << word << endl;

    // 3. 多组输入：while (cin >> x) 读到没有数据为止
    //    交互式运行时，按 Ctrl + Z 再回车表示结束
    int x;
    int sum = 0;
    int cnt = 0;
    cout << "请输入若干整数，用空格或换行分隔，最后按 Ctrl+Z 回车：" << endl;
    while (cin >> x) {
        sum += x;
        cnt++;
    }
    cout << "共 " << cnt << " 个数，sum = " << sum << endl;

    return 0;
}
