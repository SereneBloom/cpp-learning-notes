// 第 09 课：栈与队列
// 顺序栈：top 指向栈顶元素下标，空栈 top == -1
// 循环队列：牺牲一个单元区分空和满，front == rear 表示空

#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 50

// ---------------- 顺序栈 ----------------
struct SqStack {
    int data[MAXSIZE];
    int top;
};

void initStack(SqStack &S) {
    S.top = -1;
}

bool stackEmpty(SqStack &S) {
    return S.top == -1;
}

bool push(SqStack &S, int x) {
    if (S.top == MAXSIZE - 1) return false;   // 栈满
    S.top++;
    S.data[S.top] = x;
    return true;
}

bool pop(SqStack &S, int &x) {
    if (S.top == -1) return false;            // 栈空
    x = S.data[S.top];
    S.top--;
    return true;
}

// ---------------- 循环队列 ----------------
struct SqQueue {
    int data[MAXSIZE];
    int front;
    int rear;
};

void initQueue(SqQueue &Q) {
    Q.front = 0;
    Q.rear = 0;
}

bool queueEmpty(SqQueue &Q) {
    return Q.front == Q.rear;
}

bool enQueue(SqQueue &Q, int x) {
    if ((Q.rear + 1) % MAXSIZE == Q.front) return false;   // 队满
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return true;
}

bool deQueue(SqQueue &Q, int &x) {
    if (Q.front == Q.rear) return false;      // 队空
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return true;
}

// ---------------- 栈的应用：括号匹配 ----------------
bool bracketMatch(string s) {
    SqStack S;
    initStack(S);
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            push(S, c);                       // char 自动转成 int 存
        } else if (c == ')' || c == ']' || c == '}') {
            if (stackEmpty(S)) return false;  // 右括号多了
            int t = 0;
            pop(S, t);
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{')) return false;   // 类型不配对
        }
    }
    return stackEmpty(S);                     // 左括号没配完也是错
}

int main() {
    // 栈
    SqStack S;
    initStack(S);
    push(S, 1);
    push(S, 2);
    push(S, 3);
    int x = 0;
    cout << "栈出栈顺序：";
    while (pop(S, x)) cout << x << " ";
    cout << endl;

    // 循环队列
    SqQueue Q;
    initQueue(Q);
    enQueue(Q, 10);
    enQueue(Q, 20);
    enQueue(Q, 30);
    cout << "队列出队顺序：";
    while (deQueue(Q, x)) cout << x << " ";
    cout << endl;

    cout << "队空时再出队：" << (deQueue(Q, x) ? "成功" : "失败") << endl;

    // 队列环形绕回测试：连续进出 3 轮
    initQueue(Q);
    for (int r = 0; r < 3; r++) {
        enQueue(Q, r);
        deQueue(Q, x);
    }
    cout << "环形使用后仍为空：" << (queueEmpty(Q) ? "是" : "否") << endl;

    // 括号匹配
    string tests[] = {"(()[])", "([)]", "(()", "())", "{([])}"};
    for (int i = 0; i < 5; i++) {
        cout << tests[i] << " -> " << (bracketMatch(tests[i]) ? "匹配" : "不匹配") << endl;
    }

    return 0;
}
