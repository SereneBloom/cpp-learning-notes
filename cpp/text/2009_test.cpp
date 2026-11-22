// 2009 真题测试文件：穷举各种输入验证 ans()
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2009.exe 2009_test.cpp
//       然后运行 test2009.exe（本文件自带 main，不依赖 2009.cpp）
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

#include "2009.cpp"        // 把被测函数 ans() 引进来

// 建一条带头结点的单链表，data 依次为 1..n；n = 0 时只有头结点
Node *buildList(int n) {
    Node *head = new Node;
    head->data = 0;
    head->link = NULL;
    Node *tail = head;
    for (int i = 1; i <= n; i++) {
        Node *p = new Node;
        p->data = i;
        p->link = NULL;
        tail->link = p;
        tail = p;
    }
    return head;
}

// 用数组建链表，可造重复值、负数值
Node *buildList(const int *a, int n) {
    Node *head = new Node;
    head->data = 0;
    head->link = NULL;
    Node *tail = head;
    for (int i = 0; i < n; i++) {
        Node *p = new Node;
        p->data = a[i];
        p->link = NULL;
        tail->link = p;
        tail = p;
    }
    return head;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *t = head->link;
        delete head;
        head = t;
    }
}

int passCnt = 0, failCnt = 0;

// 调用 ans()，把它的屏幕输出截获到 printed 里，返回函数返回值
int runAns(Node *head, int k, string &printed) {
    ostringstream buf;
    streambuf *old = cout.rdbuf(buf.rdbuf());
    int ret = ans(head, k);
    cout.rdbuf(old);
    printed = buf.str();
    // 去掉首尾空白和换行，方便比较
    while (!printed.empty() && isspace((unsigned char)printed.front())) printed.erase(printed.begin());
    while (!printed.empty() && isspace((unsigned char)printed.back())) printed.pop_back();
    return ret;
}

// 一个测试用例：名称、链表、k、期望返回值、期望输出
void check(const string &name, Node *head, int k, int expRet, const string &expOut) {
    string printed;
    int ret = runAns(head, k, printed);
    bool ok = (ret == expRet) && (printed == expOut);
    cout << (ok ? "[通过] " : "[失败] ") << name << "  k=" << k
         << "  返回=" << ret << "(期望 " << expRet << ")"
         << "  输出=\"" << printed << "\"(期望 \"" << expOut << "\")" << endl;
    if (ok) passCnt++; else failCnt++;
}

// 题面外的输入，只观察实际行为，不计入通过率
void observe(const string &name, Node *head, int k) {
    string printed;
    int ret = runAns(head, k, printed);
    cout << "[观察] " << name << "  k=" << k
         << "  返回=" << ret << "  输出=\"" << printed << "\"" << endl;
}

int main() {
    cout << "===== 2009 真题：倒数第 k 个结点 测试 =====" << endl;

    // ---------- 1. 非法头指针 ----------
    check("head 为 NULL", NULL, 1, 0, "");

    // ---------- 2. 空表（只有头结点） ----------
    Node *empty = buildList(0);
    check("空表", empty, 1, 0, "");
    check("空表", empty, 3, 0, "");
    check("空表", empty, 100, 0, "");
    freeList(empty);

    // ---------- 3. 只有一个结点 ----------
    Node *one = buildList(1);
    check("单结点", one, 1, 1, "1");
    check("单结点越界", one, 2, 0, "");
    check("单结点越界", one, 99, 0, "");
    freeList(one);

    // ---------- 4. 两个结点 ----------
    Node *two = buildList(2);
    check("两结点", two, 1, 1, "2");
    check("两结点", two, 2, 1, "1");
    check("两结点越界", two, 3, 0, "");
    freeList(two);

    // ---------- 5. 五个结点，k 从 1 到 6 ----------
    Node *five = buildList(5);
    check("五结点", five, 1, 1, "5");
    check("五结点", five, 2, 1, "4");
    check("五结点", five, 3, 1, "3");
    check("五结点", five, 4, 1, "2");
    check("五结点", five, 5, 1, "1");
    check("五结点越界一格", five, 6, 0, "");
    freeList(five);

    // ---------- 6. 一百个结点，k 取各处 ----------
    Node *hundred = buildList(100);
    check("百结点", hundred, 1, 1, "100");
    check("百结点", hundred, 50, 1, "51");
    check("百结点", hundred, 99, 1, "2");
    check("百结点", hundred, 100, 1, "1");
    check("百结点越界一格", hundred, 101, 0, "");
    freeList(hundred);

    // ---------- 7. 所有值相同 ----------
    int same[] = {7, 7, 7};
    Node *s1 = buildList(same, 3);
    check("全相同值", s1, 1, 1, "7");
    check("全相同值", s1, 3, 1, "7");
    check("全相同值越界", s1, 4, 0, "");
    freeList(s1);

    // ---------- 8. 含负数 ----------
    int neg[] = {-3, -1, -2};
    Node *s2 = buildList(neg, 3);
    check("含负数", s2, 1, 1, "-2");
    check("含负数", s2, 3, 1, "-3");
    freeList(s2);

    // ---------- 9. 题目要求是 k 为正整数，下面只观察 ----------
    Node *five2 = buildList(5);
    observe("k=0（题面外）", five2, 0);
    observe("k=-1（题面外）", five2, -1);
    freeList(five2);

    cout << "===== 结果：通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
