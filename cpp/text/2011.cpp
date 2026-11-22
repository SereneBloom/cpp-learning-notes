#include <iostream>
using namespace std;

// 2011 年 408 真题：求两个等长升序序列 A、B 的中位数
// A、B 各 n 个元素，共 2n 个，中位数 = 第 n 小的元素
// 要求：时间和空间都尽可能高效

// ---------- 解法一：暴力归并（把合并结果存下来，最直观） ----------
int ans(int *A, int *B, int n){
    int C[200];                     // 固定容量，n <= 100 时够用
    int i = 0, j = 0, k = 0;

    // 原错误写法 ①：int C[n+1];  变长数组，ISO C++ 不支持（-Wvla 警告）
    // 原错误写法 ②：while(k < n+1){ if(A[i] < B[j])... }  没判 i<n / j<n，
    //               A 取完后会读 A[n]，越界（未定义行为）
    // 原错误写法 ③：return C[n];  取的是第 n+1 小，所有用例都差一位

    while(i < n && j < n){          // 两条序列都没取完，谁小取谁
        if(A[i] <= B[j]) C[k++] = A[i++];
        else             C[k++] = B[j++];
    }
    while(i < n) C[k++] = A[i++];   // A 有剩余，一次搬完
    while(j < n) C[k++] = B[j++];   // B 有剩余，一次搬完

    return C[n-1];                  // 2n 个元素里的第 n 小，下标是 n-1
}

// ---------- 解法二：推荐写法（不存合并结果，空间 O(1)） ----------
// 思路：既然只要第 n 小，就不必把 2n 个数都存下来。
//       两个指针同步推进，第 n 个"出堆"的元素就是答案。
int ans2(int *A, int *B, int n){
    int i = 0, j = 0;
    int cur = 0;                    // 当前出堆的值
    for(int k = 0; k < n; k++){
        // i < n ：A 不能被读穿
        // j >= n：B 已取完，剩下全从 A 取
        if(i < n && (j >= n || A[i] < B[j])){
            cur = A[i++];
        }else{
            cur = B[j++];
        }
    }
    return cur;                     // 循环正好 n 步，cur 就是第 n 小
}
