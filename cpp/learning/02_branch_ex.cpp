// 第 02 课：练习
// 练习 1：输入一个整数 x，输出它的绝对值（只能用 if，不许用 abs 函数）。
// 练习 2：输入三个整数 a、b、c，输出其中的最大值（只能用 if / else if）。
// 练习 3：输入 1~7 的整数，用 switch 输出 Mon Tue Wed Thu Fri Sat Sun；
//         输入其他数字输出 Invalid。

#include <iostream>
using namespace std;

int main() {
    // TODO: 在这里写你的答案
    // 输入获得绝对值
    int x;
    cout << "输入一个数返回绝对值：" << endl;
    cin >> x;
    if (x < 0){
        cout << -x << endl;
    }
    else{
        cout << x << endl;
    }

    // 输入3个数找最大值
    int a, b, c;
    cout << "input 3 numbers:" << endl;
    cin >> a >> b >> c;
    if (a >= b && a >= c){
        cout << a << endl;
    }
    else if (b >= c){
        cout << b << endl;
    }
    else{
        cout << c << endl;
    }

    //输入 1~7 的整数，用 switch 输出 Mon Tue Wed Thu Fri Sat Sun；
    // 输入其他数字输出 Invalid

    int day;
    cout << "1~7" << endl;
    cin >> day;
    switch(day){
        case 1:
            cout << "Mon" << endl;
            break;
        case 2:
            cout << "Tue" << endl;
            break;
        case 3:
            cout << "Wed" << endl;
            break;
        case 4:
            cout << "Thu" << endl;
            break;
        case 5:
            cout << "Fri" << endl;
            break;
        case 6:
            cout << "Sat" << endl;
            break;
        case 7:
            cout << "Sun" << endl;
            break;
        default:
            cout << "Invalid" << endl;
            break;
    } 
    return 0;
}
