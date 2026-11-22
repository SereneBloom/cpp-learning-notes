// 第 08 课：顺序表
// 位序从 1 开始（408 教材写法），数组下标从 0 开始，两者差 1

#include <iostream>
using namespace std;

#define MAXSIZE 50

struct SeqList {
    int data[MAXSIZE];
    int length;
};

// 初始化：长度归零即可
void initList(SeqList &L) {
    L.length = 0;
}

// 在第 i 个位置插入 e（i 从 1 开始，取值 1 ~ length+1）
bool insertList(SeqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) return false;   // 位置非法
    if (L.length >= MAXSIZE) return false;         // 表满
    for (int j = L.length; j >= i; j--) {          // 从后往前挪，腾出位置
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

// 删除第 i 个元素，被删的值通过 e 带回去
bool deleteList(SeqList &L, int i, int &e) {
    if (i < 1 || i > L.length) return false;
    e = L.data[i - 1];
    for (int j = i; j < L.length; j++) {           // 从前往后挪，填上空洞
        L.data[j - 1] = L.data[j];
    }
    L.length--;
    return true;
}

// 按值查找：返回位序，找不到返回 0
int locate(SeqList &L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e) return i + 1;
    }
    return 0;
}

void printList(SeqList &L) {
    cout << "length = " << L.length << " : ";
    for (int i = 0; i < L.length; i++) {
        cout << L.data[i] << " ";
    }
    cout << endl;
}

int main() {
    SeqList L;
    initList(L);

    insertList(L, 1, 10);
    insertList(L, 2, 20);
    insertList(L, 3, 30);
    cout << "插入 10 20 30：" << endl;
    printList(L);

    insertList(L, 2, 15);
    cout << "在第 2 位插入 15：" << endl;
    printList(L);

    int e = 0;
    if (deleteList(L, 3, e)) {
        cout << "删除第 3 位，删掉的是 " << e << "：" << endl;
    }
    printList(L);

    cout << "查找 30 的位序：" << locate(L, 30) << endl;
    cout << "查找 99 的位序：" << locate(L, 99) << endl;

    cout << "在非法位置 9 插入：" << (insertList(L, 9, 1) ? "成功" : "失败") << endl;

    return 0;
}
