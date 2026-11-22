// 2019 真题测试文件：重排链表为 a1, an, a2, a(n-1), ...
// 用法：g++ -std=c++11 -Wall -fexec-charset=GBK -o test2019.exe 2019_test.cpp
#include <iostream>
#include <vector>
using namespace std;

#include "2019.cpp"        // 引入被测函数 ans()

int passCnt = 0, failCnt = 0;

NODE *makeList(const vector<int> &a){
    NODE *L = new NODE;
    L->data = 0;
    L->next = NULL;
    NODE *t = L;
    for (size_t i = 0; i < a.size(); i++){
        NODE *p = new NODE;
        p->data = a[i];
        p->next = NULL;
        t->next = p;
        t = p;
    }
    return L;
}

// 带步数上限的收集，防止死循环 / 成环时测试卡住
vector<int> collect(NODE *L, bool &ok){
    vector<int> v;
    ok = true;
    int step = 0;
    for (NODE *p = L->next; p != NULL; p = p->next){
        v.push_back(p->data);
        if (++step > 500){        // 成环会超过上限
            ok = false;
            break;
        }
    }
    return v;
}

// 期望结果：偶数位取前半（a0,a1,...），奇数位取后半倒序
vector<int> expect(const vector<int> &a){
    int n = (int)a.size();
    vector<int> r;
    for (int i = 0; i < n; i++){
        if (i % 2 == 0) r.push_back(a[i / 2]);
        else            r.push_back(a[n - 1 - i / 2]);
    }
    return r;
}

void printVec(const vector<int> &v){
    cout << "[";
    for (size_t i = 0; i < v.size(); i++){
        if (i) cout << " ";
        cout << v[i];
    }
    cout << "]";
}

void check(const string &name, const vector<int> &a){
    NODE *L = makeList(a);
    bool ok = true;
    vector<int> got = collect(L, ok);
    ans(L);
    got = collect(L, ok);
    vector<int> exp = expect(a);

    if (ok && got == exp){
        passCnt++;
        if (passCnt <= 25){
            cout << "[通过] " << name << "  输入=";
            printVec(a);
            cout << " 输出=";
            printVec(got);
            cout << endl;
        }
    } else {
        failCnt++;
        cout << "[失败] " << name << "  输入=";
        printVec(a);
        cout << "\n        返回=";
        printVec(got);
        cout << "\n        期望=";
        printVec(exp);
        if (!ok) cout << "\n        （链路异常：成环或超长）";
        cout << endl;
    }
}

int main(){
    cout << "===== 2019 真题：重排链表 a1,an,a2,a(n-1),... 测试 =====" << endl;

    const char *names[] = {"空表", "单结点", "两结点", "三结点", "四结点",
                           "五结点", "六结点", "七结点", "十结点"};
    int sizes[] = {0, 1, 2, 3, 4, 5, 6, 7, 10};

    for (int k = 0; k < 9; k++){
        vector<int> a;
        for (int i = 0; i < sizes[k]; i++) a.push_back(i + 1);
        check(names[k], a);
    }

    {
        vector<int> a;
        a.push_back(7);
        a.push_back(-3);
        a.push_back(0);
        a.push_back(9);
        check("含负数与 0", a);
    }
    {
        vector<int> a;
        for (int i = 0; i < 6; i++) a.push_back(5);
        check("全部相同", a);
    }
    {
        vector<int> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        a.push_back(5);
        a.push_back(6);
        a.push_back(7);
        a.push_back(8);
        check("八结点", a);
    }
    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // ---------- 随机用例 ----------
    srand(2019);
    int rnd = 0;
    for (int t = 0; t < 2000; t++){
        int n = rand() % 21;                 // 0 ~ 20
        vector<int> a;
        for (int i = 0; i < n; i++) a.push_back(rand() % 201 - 100);
        check("随机", a);
        rnd++;
    }
    cout << "随机用例：" << rnd << " 个" << endl;

    cout << "===== 通过 " << passCnt << " 个，失败 " << failCnt << " 个 =====" << endl;
    return failCnt == 0 ? 0 : 1;
}
