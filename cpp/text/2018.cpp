#include <iostream>
#include <utility>
using namespace std;

// 2018 真题：求数组中未出现的最小正整数
//
// 原写法（错误）：
//   ① Qsort 内层 while(A[j] >= pivot) j--; 没有 i < j 保护，
//      全相同或已排序的数组会让 j 一路减出左边界（i 同理向右），越界崩溃
//   ② ans 里 if(i > A[j]) return i; 判的是"有没有比 i 小的数"，
//      与"i 是否出现过"无关，几乎总是立刻返回
//   ③ i 从 0 开始，最小正整数应从 1 起，数组含非正数时直接返回 0
//   ④ 内层 j < n+1 读到 A[n]，数组只有 n 个元素
//   ⑤ 结尾 return n; 当 1..n 全部出现时答案应为 n+1

void Qsort(int A[], int L, int R){
    if(L >= R) return ;
    int i = L, j = R;
    int pivot = A[L];
    while(i < j){
        while(i < j && A[j] >= pivot) j--;     // 原写法缺 i < j
        while(i < j && A[i] <= pivot) i++;     // 原写法缺 i < j
        if(i < j){
            swap(A[i], A[j]);
        }
    }
    swap(A[L], A[i]);
    Qsort(A, L, i-1);
    Qsort(A, i+1, R);
}

// 排序后从小到大扫：维护"下一个应该出现的正整数" expect
int ans(int A[], int n){
    Qsort(A, 0, n-1);

    int start = 0;
    while(start < n && A[start] <= 0){         // 跳过非正数
        start++;
    }

    int expect = 1;                            // 原写法：i 从 0 开始
    for(int i = start; i < n; i++){            // 原写法：i < n+1 越界
        if(A[i] == expect){
            expect++;                          // 出现了，期望下一个
        }else if(A[i] > expect){
            return expect;                     // 断档，就是答案
        }
        // A[i] < expect 说明是重复值，跳过
    }
    return expect;                             // 原写法：return n; 应返回 n+1
}
