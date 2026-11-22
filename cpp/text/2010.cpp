#include <iostream>
using namespace std;

// 2010 年 408 真题
// 设将 n（n > 1）个整数存放到一维数组 R 中。试设计一个在时间和空间两方面都
// 尽可能高效的算法，将 R 中保存的序列循环左移 p（0 < p < n）个位置，
// 即将 R 中的数据由 <x0, x1, ..., x(n-1)> 变换为
// <xp, x(p+1), ..., x(n-1), x0, x1, ..., x(p-1)>。
void mySwap(int &a, int &b){
    // 交换2个元素
    int k = a;
    a = b;
    b = k;
}

void S(int *R, int l, int r){
    // 倒置数据闭区间 [l, r]
    // 原错误写法：for(int i = l; i < (r - l + 1) / 2; i ++){ mySwap(R[i], R[r-i]); }
    //   错误 1：i 的起点是绝对下标 l，判断条件 (r-l+1)/2 却是"长度的一半"，
    //           两者基准不同。l=1,r=3 时变成 i<1，一次都不执行
    //   错误 2：配对写成 R[r-i]，只在 l=0 时碰巧成立；l>0 时应配 R[l+r-i]
    // 正确写法：i 只负责数"第几对"，下标用 l+i 和 r-i 现算
    for(int i = 0; i < (r - l + 1) / 2; i ++){
        mySwap(R[l + i], R[r - i]);
    }
}

void ans(int *R, int p, int n){
    S(R, 0, p-1);
    S(R, p, n-1);
    S(R, 0, n-1);
}