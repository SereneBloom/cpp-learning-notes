// 2015 真题测试文件：删除绝对值重复的结点（只保留第一次出现）
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2015.exe 2015_test.cpp
//       然后运行 test2015.exe
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#include "2015.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

// 建一条带头结点的链表
Node *makeList(const vector<int> &a) {
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    Node *tail = head;
    for (size_t i = 0; i < a.size(); i++) {
        Node *p = new Node;
        p->data = a[i];
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return head;
}

// 把链表数据抄进 vector
vector<int> toVector(Node *head) {
    vector<int> r;
    for (Node *p = head->next; p != NULL; p = p->next) r.push_back(p->data);
    return r;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *t = head->next;
        delete head;
        head = t;
    }
}

void printVec(const vector<int> &v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << " ";
        cout << v[i];
    }
    cout << "]";
}

// 暴力标准答案：按绝对值首次出现保留
// 注意：标记数组必须覆盖被测代码支持的绝对值上界（MaxSize-1），
//       否则测试程序自己会越界（这正是第一次运行崩溃的原因）
vector<int> expectDedup(const vector<int> &a) {
    bool seen[MaxSize] = {false};
    vector<int> r;
    for (size_t i = 0; i < a.size(); i++) {
        int k = a[i] < 0 ? -a[i] : a[i];
        if (k >= MaxSize) {            // 超出被测代码支持的区间，直接报错退出
            cout << "[测试程序错误] 用例值 " << a[i] << " 超出 MaxSize=" << MaxSize << endl;
            exit(2);
        }
        if (!seen[k]) {
            seen[k] = true;
            r.push_back(a[i]);
        }
    }
    return r;
}

void check(const string &name, const vector<int> &a) {
    Node *head = makeList(a);
    ans(head);
    vector<int> got = toVector(head);
    vector<int> exp = expectDedup(a);
    if (got == exp) {
        passCnt++;
        cout << "[通过] " << name << "  ";
        printVec(a);
        cout << " -> ";
        printVec(got);
        cout << endl;
    } else {
        failCnt++;
        cout << "[失败] " << name << "  ";
        printVec(a);
        cout << " 返回=";
        printVec(got);
        cout << " 期望=";
        printVec(exp);
        cout << endl;
    }
    freeList(head);
}

int main() {
    cout << "===== 2015 真题：删除绝对值重复结点 测试 =====" << endl;

    // ---------- 一、手写边界用例 ----------
    check("空表（只有头结点）", vector<int>());
    check("单结点", vector<int>(1, 7));

    {
        int t[] = {1, 2, 3, 4};
        check("全部不同", vector<int>(t, t + 4));
    }
    {
        int t[] = {1, -1, 2, -3, 3};
        check("含负数，符号不同但绝对值相同", vector<int>(t, t + 5));
    }
    {
        int t[] = {5, 5, 5, 5};
        check("四个相同", vector<int>(t, t + 4));
    }
    {
        int t[] = {-2, 2, -2, 2};
        check("负数在前", vector<int>(t, t + 4));
    }
    {
        int t[] = {2, 1, 2, 3, 1};
        check("验证保序（不能改变首次出现顺序）", vector<int>(t, t + 5));
    }
    {
        int t[] = {0, 0, 1, 0};
        check("含 0（abs(0)=0）", vector<int>(t, t + 4));
    }
    {
        int t[] = {9999, -9999, 1};
        check("绝对值触及上界 9999", vector<int>(t, t + 3));
    }
    {
        int t[] = {-1, 1, -1, 1, 2, -1, 2};
        check("长序列反复出现", vector<int>(t, t + 7));
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 二、随机用例 ----------
    // 值域限制在 [-50, 50]，避免超出 MaxSize
    srand(2015);
    int rndTotal = 0;
    for (int t = 0; t < 3000; t++) {
        int n = rand() % 16;
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int v = rand() % 101 - 50;
            a.push_back(v);
        }
        check("随机", a);
        rndTotal++;
    }
    cout << "随机用例：" << rndTotal << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
