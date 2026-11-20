// 第 04 课：数组与字符串
// 目标：一维数组的遍历，char 数组与 string 的读取

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 1. 一维数组：一次开出一排连续的空间，下标从 0 开始
    int a[5] = {3, 1, 4, 1, 5};
    cout << a[0] << " " << a[4] << endl;

    // 2. 遍历：下标范围是 0 ~ n-1，不要写 <= n
    for (int i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    // 3. 边读边存
    int n;
    cout << "请输入元素个数 n：" << endl;
    cin >> n;
    int b[100];
    cout << "请输入 " << n << " 个整数：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    // 4. 求最大值与总和：最大值先用第一个元素打底
    int mx = b[0], sum = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] > mx)
            mx = b[i];
        sum += b[i];
    }
    cout << "max = " << mx << " sum = " << sum << endl;

    // 5. string：可以直接拼接，size() 拿长度
    string s1 = "abc";
    string s2 = "def";
    cout << s1 + s2 << endl;
    cout << s1.size() << endl;

    // 6. 遍历字符串：每个字符就是一个 char
    string word;
    cout << "请输入一个不含空格的单词（逐字符输出）：" << endl;
    cin >> word;
    for (int i = 0; i < (int)word.size(); i++) {
        cout << word[i] << "-";
    }
    cout << endl;

    return 0;
}
