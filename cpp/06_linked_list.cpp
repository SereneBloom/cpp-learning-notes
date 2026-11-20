// 第 06 课：单链表（带头结点风格）
// 目标：哨兵结点、头插 / 尾插、遍历、查找、删除、释放

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

// 初始化：造一个哨兵结点，head 永远指向它，head->next 才是第一个数据结点
Node *initList() {
    Node *head = new Node;
    head->next = NULL;
    return head;
}

// 遍历：从 head->next 开始，跳过哨兵
void printList(Node *head) {
    for (Node *p = head->next; p != NULL; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

int length(Node *head) {
    int cnt = 0;
    for (Node *p = head->next; p != NULL; p = p->next) {
        cnt++;
    }
    return cnt;
}

Node *find(Node *head, int x) {
    Node *p = head->next;
    while (p != NULL && p->data != x) {
        p = p->next;
    }
    return p;
}

// 头插：插在哨兵之后，永远是第一个
void insertHead(Node *head, int x) {
    Node *p = new Node;
    p->data = x;
    p->next = head->next;
    head->next = p;
}

// 尾插：从哨兵开始找尾巴，空表时 tail 就是 head，不需要特判
void insertTail(Node *head, int x) {
    Node *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    tail->next = p;
}

// 删除第一个值为 x 的结点：prev 从哨兵开始，删表头也不用特判
bool removeOne(Node *head, int x) {
    Node *prev = head;
    while (prev->next != NULL && prev->next->data != x) {
        prev = prev->next;
    }
    if (prev->next == NULL) {
        return false;
    }
    Node *q = prev->next;
    prev->next = q->next;
    delete q;
    return true;
}

// 释放：哨兵也要一起删
void freeList(Node *head) {
    while (head != NULL) {
        Node *t = head->next;
        delete head;
        head = t;
    }
}

int main() {
    // 1. 头插：顺序反转
    Node *head = initList();
    insertHead(head, 1);
    insertHead(head, 2);
    insertHead(head, 3);
    cout << "头插：";
    printList(head);
    freeList(head);

    // 2. 尾插：顺序与输入一致
    head = initList();
    for (int i = 1; i <= 3; i++) {
        insertTail(head, i);
    }
    cout << "尾插：";
    printList(head);
    cout << "长度：" << length(head) << endl;

    // 3. 查找
    if (find(head, 2) != NULL)
        cout << "找到 2" << endl;
    else
        cout << "没有 2" << endl;

    // 4. 头插 0
    insertHead(head, 0);
    cout << "头插 0：";
    printList(head);

    // 5. 删除 2
    if (removeOne(head, 2))
        cout << "删除成功" << endl;
    cout << "删 2：";
    printList(head);

    freeList(head);
    return 0;
}
