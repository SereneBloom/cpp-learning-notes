// 第 06 课：练习（带头结点风格）
// 练习 1：读入 n 个整数，用头插法建表，输出链表以及它的长度。
// 练习 2：读入 n 个整数，用尾插法建表，输出其中的最大值。
// 练习 3：读入 n 个整数建表，再读入 x，删除链表中所有值为 x 的结点，输出剩余链表。
//         注意 x 可能出现在表头，也可能一个都没有。

#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node *next;
};

// 已给：造哨兵，head 永远指向它
Node *initList() {
    Node *head = new Node;
    head->next = NULL;
    return head;
}

// 已给：从头结点之后开始输出
void printList(Node *head) {
    for (Node *p = head->next; p != NULL; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

int main() {
    // 练习 1：头插建表 + 输出 + 长度
    int n;
    cout << "练习 1：请输入个数 n：" << endl;
    cin >> n;
    Node *head = initList();
    for (int i = 0; i < n; i++) {
        Node *p = new Node;
        cout << "请输入第 " << i + 1 << " 个数：" << endl;
        cin >> p->data;
        p->next = head->next;
        head->next = p;
    }
    Node *q1 = head->next;
    int num = 0;
    while (q1 != NULL) {
        num++;
        q1 = q1->next;
    }
    printList(head);
    cout << num << endl;

    // 练习 2：尾插建表 + 最大值
    Node *head2 = initList();
    Node *tail = head2;
    cout << "练习 2：请输入个数 n：" << endl;
    int n2;
    cin >> n2;
    int mx2 = INT_MIN;
    for (int i = 0; i < n2; i++) {
        Node *p2 = new Node;
        cout << "请输入第 " << i + 1 << " 个数：" << endl;
        cin >> p2->data;
        if (p2->data > mx2) {
            mx2 = p2->data;
        }
        p2->next = NULL;
        tail->next = p2;
        tail = tail->next;
    }
    printList(head2);
    cout << mx2 << endl;

    // 练习 3：删除所有值为 x 的结点
    Node *head3 = initList();
    Node *tail3 = head3;
    cout << "练习 3：请输入个数 n：" << endl;
    int n3;
    cin >> n3;
    cout << "请输入要删除的 x：" << endl;
    int x;
    cin >> x;
    for (int i = 0; i < n3; i++) {
        Node *p = new Node;
        cout << "请输入第 " << i + 1 << " 个数：" << endl;
        cin >> p->data;
        p->next = NULL;
        tail3->next = p;
        tail3 = tail3->next;
    }
    Node *q3 = head3;
    while (q3->next != NULL) {
        if (q3->next->data == x) {
            Node *del = q3->next;
            q3->next = del->next;
            delete del;
        } else {
            q3 = q3->next;
        }
    }
    if (head3->next != NULL) {
        printList(head3);
    }
    return 0;
}
