// 第 10 课：链表高频算法（统一使用带头结点的单链表）
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

// 建立只有哨兵的头结点
Node *initList() {
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    return head;
}

// 尾插：保持输入顺序
void insertTail(Node *head, int x) {
    Node *tail = head;
    while (tail->next != NULL) tail = tail->next;
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    tail->next = p;
}

void printList(Node *head) {
    for (Node *p = head->next; p != NULL; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

// 就地逆置：头插法，把每个结点依次摘下来插到 head 后面
void reverseList(Node *head) {
    Node *p = head->next;   // p 负责遍历原来的数据结点
    head->next = NULL;      // 结果链表先清空
    while (p != NULL) {
        Node *q = p->next;  // 先存后继，否则接完就找不到后面的结点了
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

// 快慢指针找中间结点：slow 每步 1 格，fast 每步 2 格
Node *findMiddle(Node *head) {
    Node *slow = head->next;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 判环：有环时快指针一定会在环里追上慢指针
bool hasCycle(Node *head) {
    Node *slow = head->next;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 合并两个非递减链表，返回新的带头结点链表（直接摘用原结点）
Node *mergeSorted(Node *a, Node *b) {
    Node *head = initList();
    Node *tail = head;
    Node *p = a->next;
    Node *q = b->next;
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            tail->next = p;
            p = p->next;
        } else {
            tail->next = q;
            q = q->next;
        }
        tail = tail->next;
    }
    tail->next = (p != NULL) ? p : q;   // 剩下的一整段直接接上
    return head;
}

// 释放整条链表（含哨兵）
void freeList(Node *head) {
    while (head != NULL) {
        Node *t = head->next;
        delete head;
        head = t;
    }
}

int main() {
    // 1) 逆置
    Node *L1 = initList();
    for (int i = 1; i <= 5; i++) insertTail(L1, i);
    cout << "原表：";
    printList(L1);
    reverseList(L1);
    cout << "逆置：";
    printList(L1);

    // 2) 中间结点（奇数个 5 个，返回正中间）
    Node *L2 = initList();
    for (int i = 1; i <= 5; i++) insertTail(L2, i);
    cout << "中间结点：" << findMiddle(L2)->data << endl;

    // 3) 判环：先测无环，再人为造环
    cout << "判环（无环）：" << (hasCycle(L2) ? "有环" : "无环") << endl;
    Node *p2 = L2->next;
    while (p2->next != NULL) p2 = p2->next;
    Node *entry = L2->next->next;   // 让尾结点指回第 2 个结点
    p2->next = entry;
    cout << "判环（造环）：" << (hasCycle(L2) ? "有环" : "无环") << endl;
    p2->next = NULL;                // 拆掉环，否则释放时会死循环

    // 4) 合并两个有序链表
    Node *A = initList();
    Node *B = initList();
    for (int i = 1; i <= 7; i += 2) insertTail(A, i);   // 1 3 5 7
    for (int i = 2; i <= 6; i += 2) insertTail(B, i);   // 2 4 6
    Node *C = mergeSorted(A, B);
    cout << "合并：";
    printList(C);

    freeList(L1);
    freeList(L2);
    delete A;       // A、B 的数据结点已经串进 C，只能回收两个哨兵，不能整表释放
    delete B;
    freeList(C);
    return 0;
}
