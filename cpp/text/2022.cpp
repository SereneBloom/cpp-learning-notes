#include <iostream>
#include <climits>
using namespace std;

const int MAX_size = 1000;

typedef struct{
    int SqBiTNode[MAX_size];
    int ElemNum;
}SqBiTree;

// 2022 真题：判断顺序存储的二叉树是否为二叉搜索树
//
// 原写法（错误）：
//   ① if(T->SqBiTNode[i] = -1) —— 用了赋值而不是 ==，把每个结点都改成 -1，
//      条件恒为真，整个循环全部 continue，函数无条件返回 true
//   ② 只比较直接左右孩子，判不出跨层违规。反例 10(5, 15(6))：6 在根的右子树里
//      却小于根，父子关系却都合法
//   ③ 用祖父值 pass 当右孩子上界，不等于"最近祖先约束"，逻辑不成立
//   ④ 取孩子下标 2*i+2 前没判越界，i 接近 ElemNum 时会读到数组之外
//   ⑤ 空树 return false，应为 true

// 中序遍历：BST 的充要条件是中序序列严格递增
bool check(SqBiTree *T, int k, int &prev){
    if(k >= T->ElemNum || T->SqBiTNode[k] == -1){
        return true;                       // 空结点跳过
    }
    if(!check(T, 2 * k + 1, prev)) return false;      // 左子树
    if(T->SqBiTNode[k] <= prev) return false;         // 中：必须严格递增
    prev = T->SqBiTNode[k];                           // 记下前驱
    return check(T, 2 * k + 2, prev);                 // 右子树
}

bool ans(SqBiTree *T){
    if(T == NULL){
        return true;                       // 空树是 BST
    }
    int prev = INT_MIN;
    return check(T, 0, prev);
}
