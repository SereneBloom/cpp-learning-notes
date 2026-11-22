// 2012 真题测试文件：找两个链表的共同后缀起始结点
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2012.exe 2012_test.cpp
//       然后运行 test2012.exe
#include <iostream>
using namespace std;

#include "2012.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

// 建一条带头结点的链表，数据依次为 a[0..n-1]
Node *makeList(const int *a, int n) {
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    Node *tail = head;
    for (int i = 0; i < n; i++) {
        Node *p = new Node;
        p->data = a[i];
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return head;
}

Node *tailOf(Node *head) {
    while (head->next != NULL) head = head->next;
    return head;
}

// 打印一条链表的数据，只用于失败时排查
void printList(const char *tag, Node *head) {
    cout << tag << "[";
    for (Node *p = head->next; p != NULL; p = p->next) {
        cout << p->data;
        if (p->next != NULL) cout << " ";
    }
    cout << "]";
}

void check(const string &name, Node *h1, Node *h2, Node *exp) {
    Node *got = ans(h1, h2);
    if (got == exp) {
        passCnt++;
        cout << "[通过] " << name << endl;
    } else {
        failCnt++;
        cout << "[失败] " << name << "  ";
        printList("str1=", h1);
        cout << "  ";
        printList("str2=", h2);
        cout << "  返回=" << (got == NULL ? "NULL" : "结点")
             << "  期望=" << (exp == NULL ? "NULL" : "结点") << endl;
    }
}

int main() {
    cout << "===== 2012 真题：共同后缀起始结点 测试 =====" << endl;

    // ---------- 1. 两侧都是空表 ----------
    {
        Node *h1 = makeList(NULL, 0);
        Node *h2 = makeList(NULL, 0);
        check("两侧都是空表", h1, h2, NULL);
    }

    // ---------- 2. 一侧空表，一侧非空 ----------
    {
        int b[] = {1, 2};
        Node *h1 = makeList(NULL, 0);
        Node *h2 = makeList(b, 2);
        check("str1 空、str2 非空", h1, h2, NULL);
    }

    // ---------- 3. 等长，共享后两个 ----------
    {
        int a[] = {1, 2}, b[] = {9, 9}, s[] = {7, 8};
        Node *h1 = makeList(a, 2);
        Node *h2 = makeList(b, 2);
        Node *sh = makeList(s, 2);
        tailOf(h1)->next = sh->next;       // 两条链表的尾部指向同一段
        tailOf(h2)->next = sh->next;
        check("等长，共享 2 个", h1, h2, sh->next);
    }

    // ---------- 4. 长链在前（str1 比 str2 长） ----------
    {
        int a[] = {1, 2, 3}, b[] = {9}, s[] = {7, 8};
        Node *h1 = makeList(a, 3);
        Node *h2 = makeList(b, 1);
        Node *sh = makeList(s, 2);
        tailOf(h1)->next = sh->next;
        tailOf(h2)->next = sh->next;
        check("str1 长 2 个结点", h1, h2, sh->next);
    }

    // ---------- 5. 短链在前（str2 比 str1 长） ----------
    {
        int a[] = {9}, b[] = {1, 2, 3}, s[] = {7, 8};
        Node *h1 = makeList(a, 1);
        Node *h2 = makeList(b, 3);
        Node *sh = makeList(s, 2);
        tailOf(h1)->next = sh->next;
        tailOf(h2)->next = sh->next;
        check("str2 长 2 个结点", h1, h2, sh->next);
    }

    // ---------- 6. 只共享最后一个结点 ----------
    {
        int a[] = {1, 2, 3}, b[] = {4, 5, 6}, s[] = {7};
        Node *h1 = makeList(a, 3);
        Node *h2 = makeList(b, 3);
        Node *sh = makeList(s, 1);
        tailOf(h1)->next = sh->next;
        tailOf(h2)->next = sh->next;
        check("等长，只共享尾结点", h1, h2, sh->next);
    }

    // ---------- 7. 长度差 2，只共享尾结点 ----------
    {
        int a[] = {1, 2}, b[] = {3, 4, 5, 6}, s[] = {7};
        Node *h1 = makeList(a, 2);
        Node *h2 = makeList(b, 4);
        Node *sh = makeList(s, 1);
        tailOf(h1)->next = sh->next;
        tailOf(h2)->next = sh->next;
        check("长度差 2，只共享尾结点", h1, h2, sh->next);
    }

    // ---------- 8. 值相同但结点不同（无公共后缀） ----------
    {
        int a[] = {1, 2, 3}, b[] = {1, 2, 3};
        Node *h1 = makeList(a, 3);
        Node *h2 = makeList(b, 3);
        check("值相同但结点不同", h1, h2, NULL);
    }

    // ---------- 9. 完全共享（两条表头指向同一段数据） ----------
    {
        int a[] = {1, 2, 3};
        Node *h1 = makeList(a, 3);
        Node *h2 = makeList(NULL, 0);
        h2->next = h1->next;               // 从第一个数据结点起完全共用
        check("完全共享", h1, h2, h1->next);
    }

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
