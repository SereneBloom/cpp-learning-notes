// 第 08 课：顺序表练习
// 练习 1：删除表中最小值元素，用 e 带回被删的值；空表返回 false
// 练习 2：就地逆置，要求空间 O(1)
// 练习 3：删除所有值为 x 的元素，要求时间 O(n)、空间 O(1)
// 练习 4：把两个非递减有序表 A、B 合并成新的非递减表 C

#include <iostream>
using namespace std;

#define MAXSIZE 50

struct SeqList {
    int data[MAXSIZE];
    int length;
};

void initList(SeqList &L) {
    L.length = 0;
}

bool insertList(SeqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) return false;
    if (L.length >= MAXSIZE) return false;
    for (int j = L.length; j >= i; j--) L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return true;
}

void printList(SeqList &L) {
    cout << "length = " << L.length << " : ";
    for (int i = 0; i < L.length; i++) cout << L.data[i] << " ";
    cout << endl;
}

// 练习 1
bool deleteMin(SeqList &L, int &e) {
    // TODO:
    //   1) 空表直接 return false
    //   2) 用 min 记最小值的下标（从 0 开始），遍历整个表更新它
    //   3) e = L.data[min]
    //   4) 用后面元素依次前移把 L.data[min] 覆盖掉，length--
    //   5) return true
    if(L.length == 0){
        return false;
    }
    int min = 0;
    for(int i = 0; i < L.length; i ++){
        if(L.data[i] < L.data[min]){
            min = i;
        }
    }
    e = L.data[min];
    for(int i = min; i < L.length - 1; i ++){
        L.data[i] = L.data[i + 1];
    }
    L.length --;
    return true;
}

// 练习 2
void reverseList(SeqList &L) {
    // TODO:
    //   1) 用双指针 i = 0、j = L.length - 1
    //   2) 当 i < j 时交换 L.data[i] 与 L.data[j]，然后 i++、j--
    //   注意交换要用临时变量，别直接赋值把值冲掉
    int i = 0;
    int j = L.length - 1;
    while(i < j){
        swap(L.data[i], L.data[j]);
        i ++;
        j --;
    }
}

// 练习 3
void deleteAllX(SeqList &L, int x) {
    // TODO（提示：不要每删一个就整体前移，那样是 O(n^2)）
    //   1) 用 k 记录"保留下来的元素个数"，初始 0
    //   2) 遍历原表，遇到不等于 x 的元素就 L.data[k++] = 当前元素
    //   3) 循环结束 L.length = k
    int k = 0;
    for(int i = 0; i < L.length; i ++){
        if(L.data[i] != x){
            L.data[k] = L.data[i];
            k ++;
        }
    }
    L.length = k;
}

// 练习 4
void mergeList(SeqList &A, SeqList &B, SeqList &C) {
    // TODO:
    //   1) initList(C)
    //   2) i、j 分别指向 A、B 的当前元素，都为 0
    //   3) 两边都有元素时，把较小的那个放进 C，对应下标前进
    //   4) 哪个表还剩元素，就整段搬进 C
    //   5) 注意 C 的 length 不能超过 MAXSIZE
    initList(C);
    int i = 0;
    int j = 0;
    int k = 0;
    while(i < A.length && j < B.length){
        if(A.data[i] <= B.data[j]){
            C.data[k] = A.data[i];
            k ++;
            i ++;
        }else{
            C.data[k] = B.data[j];
            k ++;
            j ++;
        }
    }
    if(i < A.length){
        while(i < A.length){
            C.data[k] = A.data[i];
                i ++;
                k ++;
        }
        
    }else{
        while(j < B.length){
            C.data[k] = B.data[j];
                j ++;
                k ++;
        }
        
    }
    C.length = k;
}

int main() {
    // 练习 1 测试
    SeqList L1;
    initList(L1);
    int a1[] = {5, 3, 9, 1, 7};
    for (int i = 0; i < 5; i++) insertList(L1, i + 1, a1[i]);
    cout << "练习 1 原表：" << endl;
    printList(L1);
    int e1 = 0;
    if (deleteMin(L1, e1)) cout << "删除最小值：" << e1 << endl;
    printList(L1);

    // 练习 2 测试
    SeqList L2;
    initList(L2);
    int a2[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) insertList(L2, i + 1, a2[i]);
    cout << "练习 2 原表：" << endl;
    printList(L2);
    reverseList(L2);
    cout << "逆置后：" << endl;
    printList(L2);

    // 练习 3 测试
    SeqList L3;
    initList(L3);
    int a3[] = {2, 1, 2, 3, 2, 4};
    for (int i = 0; i < 6; i++) insertList(L3, i + 1, a3[i]);
    cout << "练习 3 原表：" << endl;
    printList(L3);
    deleteAllX(L3, 2);
    cout << "删除所有 2 后：" << endl;
    printList(L3);

    // 练习 4 测试
    SeqList A, B, C;
    initList(A);
    initList(B);
    int a4[] = {1, 3, 5, 7};
    int b4[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 4; i++) insertList(A, i + 1, a4[i]);
    for (int i = 0; i < 5; i++) insertList(B, i + 1, b4[i]);
    cout << "练习 4 A：" << endl;
    printList(A);
    cout << "练习 4 B：" << endl;
    printList(B);
    mergeList(A, B, C);
    cout << "合并结果 C：" << endl;
    printList(C);

    return 0;
}
