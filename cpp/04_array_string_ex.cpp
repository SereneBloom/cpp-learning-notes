// 第 04 课：练习
// 练习 1：先输入 n，再输入 n 个整数，输出最大值、最小值、平均值（平均值保留小数）。
// 练习 2：输入一个由小写字母组成的单词（不含空格），倒序输出它，不许用 reverse 之类的函数。
// 练习 3：先输入 n，再输入 n 个整数，统计其中正数、负数、零各有多少个。

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 练习 1：先输入 n，再输入 n 个整数，输出最大值、最小值、平均值（平均值保留小数）。
    int n;
    cout << "input n:" << endl;
    cin >> n;
    int A[100]; // 原写法：int A[n]; 变长数组是 GCC 扩展，不符合标准 C++
    for(int i = 0; i < n; i++){
        cin >> A[i];
    }
    int ma = A[0];
    int mi = A[0];
    int sum = 0;
    for(int i = 0; i < n; i++){
        if(A[i] > ma){
            ma = A[i];
        }
        if(A[i] < mi){
            mi = A[i];
        }
        sum += A[i];
    }
    // 原写法：sum / n，int / int 会丢掉小数，42 / 4 得 10
    cout << ma << " " << mi << " " << (double)sum / n << endl;

    // 练习 2：输入一个由小写字母组成的单词（不含空格），倒序输出它，不许用 reverse 之类的函数。
    string s1;
    cout << "input s:" << endl;
    cin >> s1;
    // 原写法：int i = s1.size() - 1，size() 是无符号数，空串时 0 - 1 会绕成极大值
    for(int i = (int)s1.size() - 1; i >= 0; i--){
        cout << s1[i]; // 原写法：cout << s1[i] << " "，多打了空格
    }
    cout << endl;

    // 练习 3：先输入 n，再输入 n 个整数，统计其中正数、负数、零各有多少个。
    int x;
    cout << "input x:" << endl;
    cin >> x;
    int B[100]; // 原写法：int B[x]; 同样是变长数组
    int B_1 = 0, B_2 = 0, zero = 0;
    for(int i = 0; i < x; i++){
        cin >> B[i];
        if(B[i] > 0){
            B_1 += 1;
        }else if(B[i] < 0){
            B_2 += 1;
        }else{
            zero += 1;
        }
    }
    cout << B_1 << " " << B_2 << " " << zero << endl;
    return 0;

}
