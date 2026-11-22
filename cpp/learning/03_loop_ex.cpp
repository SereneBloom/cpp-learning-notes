// 第 03 课：练习
// 练习 1：输入 n（n <= 10），输出 n!（1 * 2 * ... * n），用 for。
// 练习 2：输入一个大于 1 的整数 n，判断它是否为素数，是输出 yes，否则输出 no。
// 练习 3：不断读入整数，读到 0 为止（0 不参与计算），输出这些数的和与个数。

#include <iostream>
using namespace std;

int main() {
    // TODO: 在这里写你的答案
    int n1 = 0;
    cout << "input: n1 = " << endl;
    cin >> n1 ;
    int sum = 1;
    for (int i = 1; i <= n1; i++){
        sum *= i;
    }
    cout << sum << endl;

    int n2 = 0;
    cout << "input: n2 = " << endl;
    cin >> n2;
    int k = 2;
    bool x = true;
    while (k < n2){
        if(n2 % k == 0){
            x = false;
            break;
        }
        k++;
    }
    if (x){
        cout << "yes" << endl;
    }else{
        cout << "no" << endl;
    }
    
    int ans = 0;
    int a = 0;
    int n3 = 0;
    do{
        ans += a;
        cout << "input a = " << endl;
        cin >> a;
        if(a != 0){
            n3 += 1;
        }
    }while(a != 0);
    cout << ans << endl;
    cout << n3 << endl;
    return 0;
}
