#include <iostream>
#include <climits>
using namespace std;

// 2025 真题：对每个 i，求 A[i] 与「另一个元素」乘积的最大值，存入 res[i]
void calMulMax(int A[], int res[], int n){
    if (n < 2) return;                 // 没有「另一个元素」时无定义

    // 原写法问题：
    //   ① 内层 j 从 i+1 开始只算右侧伙伴，左侧伙伴全部漏掉，
    //      导致最后一个元素 res[n-1] 永远没被写入
    //   ② res[i] = max(res[i], ...) 时 res[i] 是未初始化的垃圾值
    //   ③ int maxMul = A[i] * A[i]; 用「自己乘自己」作初值，违反 j ≠ i
    //      （{1,2,3} 的 res[2] 会得到 3*3=9，正确答案是 3*2=6）

    for(int i = 0; i < n; i++){
        res[i] = INT_MIN;              // ② 先压到最小，再逐个取大
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j ++){
            long long v = (long long)A[i] * A[j];   // 防溢出
            if(v > res[i]) res[i] = (int)v;
            if(v > res[j]) res[j] = (int)v;         // ① 一对 (i,j) 同时更新两端
        }
    }
}
