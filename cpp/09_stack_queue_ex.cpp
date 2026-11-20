// 第 09 课：栈与队列练习
// 练习 1：十进制转八进制，用顺序栈实现，不允许用 printf 的格式控制
// 练习 2：括号匹配，支持 ( ) [ ] { } 三种
// 练习 3：循环队列模拟：先入队 n 个数再全部出队打印，最后检查队空
// 练习 4：用两个栈实现队列（入队、出队、判空）

#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 50

struct SqStack
{
    int data[MAXSIZE];
    int top;
};

void initStack(SqStack &S)
{
    S.top = -1;
}

bool stackEmpty(SqStack &S)
{
    return S.top == -1;
}

bool push(SqStack &S, int x)
{
    if (S.top == MAXSIZE - 1)
        return false;
    S.top++;
    S.data[S.top] = x;
    return true;
}

bool pop(SqStack &S, int &x)
{
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    S.top--;
    return true;
}

struct SqQueue
{
    int data[MAXSIZE];
    int front;
    int rear;
};

void initQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

bool enQueue(SqQueue &Q, int x)
{
    if ((Q.rear + 1) % MAXSIZE == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return true;
}

bool deQueue(SqQueue &Q, int &x)
{
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return true;
}

// 练习 1：十进制转八进制，把八进制的每一位打印出来
void decToOct(int n)
{
    // TODO:
    //   1) 建栈并初始化
    //   2) 当 n > 0 时，把 n % 8 压栈，然后 n = n / 8
    //   3) 依次弹栈并打印每一位（弹出来的顺序正好是高位到低位）
    //   4) 注意 n 为 0 时要输出 0
    if (n == 0)
    {
        cout << 0;
        return;
    }
    SqStack S;
    initStack(S);
    while (n > 0)
    {
        push(S, n % 8);
        n /= 8;
    }
    while (S.top != -1)
    {
        cout << S.data[S.top];
        S.top--;
    }
}

// 练习 2：括号匹配
bool bracketMatch(string s)
{
    // TODO:
    //   1) 遍历每个字符
    //   2) 左括号入栈
    //   3) 右括号：栈空返回 false；否则弹出栈顶，类型不配返回 false
    //   4) 遍历结束返回 stackEmpty(S)
    SqStack S;
    initStack(S);
    // 原写法：i < s.size()  int 与无符号数比较，-Wall 警告
    for (int i = 0; i < (int)s.size(); i++)
    {
        char c = s[i];
        // 原写法：if(c == '(' || '[' || '{')  '[' 和 '{' 是非零常量，条件恒真，所有字符都入栈
        if (c == '(' || c == '[' || c == '{')
        {
            push(S, c);
        }
        // 原写法：独立的 if(c == ')' || ']' || '}')
        else if (c == ')' || c == ']' || c == '}')
        {
            if (stackEmpty(S))
            {
                return false;
            }
            // 原写法：S.top == '('  拿下标和字符比，永远不相等，右括号从不弹栈
            int t;
            pop(S, t); // 原写法：S.top --;
            if (!((c == ')' && t == '(') || (c == ']' && t == '[') || (c == '}' && t == '{')))
            {
                return false;
            }
        }
    }
    // 原写法：if(stackEmpty(S)){ return false; } return true;  判断方向反了
    return stackEmpty(S);
}

// 练习 3：循环队列模拟
void queueDemo(int n)
{
    // TODO:
    //   1) 建队列并初始化
    //   2) 读入 n 个整数依次入队，入队失败要提示"队满"
    //   3) 再依次出队并打印
    //   4) 出队完打印是否队空（front == rear）
    SqQueue Q;
    initQueue(Q);
    for (int i = 0; i < n; i++)
    {
        if ((Q.rear + 1) % MAXSIZE == Q.front)
        {
            cout << "full" << endl;
        }
        int x;
        cin >> x;
        enQueue(Q, x);
    }
    int x;
    // 原写法：while(Q.rear % MAXSIZE != Q.front)  rear 已经是取模后的值，再取模没有意义
    while (Q.front != Q.rear)
    {
        // 原写法：x = Q.data[Q.front];  多余，deQueue 的 int &x 已经把队头值带回来了
        deQueue(Q, x);
        cout << x << " ";
    }
    // 原写法：if(!deQueue(Q,x)){ cout << "empty" << endl; }  为了判空多出队一次
    cout << (Q.front == Q.rear ? "empty" : "not empty") << endl;
}

// 练习 4：两个栈实现队列
struct TwoStackQueue
{
    SqStack s1; // 负责入队
    SqStack s2; // 负责出队
};

void initTSQ(TwoStackQueue &Q)
{
    initStack(Q.s1);
    initStack(Q.s2);
}

void tsqPush(TwoStackQueue &Q, int x)
{
    // TODO: 直接压入 s1
    push(Q.s1, x);
}

bool tsqPop(TwoStackQueue &Q, int &x)
{
    // TODO:
    //   1) 如果 s2 非空，直接从 s2 弹一个返回
    //   2) 如果 s2 为空，先把 s1 全部弹出并压入 s2（顺序就反过来了）
    //   3) 再判断 s2 是否为空，空说明整个队列没元素，返回 false
    //   4) 否则从 s2 弹一个给 x，返回 true
    if(!stackEmpty(Q.s2)){
        // 原写法：pop(Q.s2, x);  未检查返回值
        if(!pop(Q.s2, x)) return false;
    }else{
        int k;
        // 原写法：while(Q.s1.top != -1)  直接访问内部字段，改为调用 stackEmpty
        while(!stackEmpty(Q.s1)){
            pop(Q.s1, k);
            push(Q.s2, k);
        }
        if(stackEmpty(Q.s2)){
            return false;
        }else{
            if(!pop(Q.s2, x)) return false;
        }
    }
    return true;
}

int main()
{
    cout << "练习 1：10 转八进制 = ";
    decToOct(10);
    cout << "，64 转八进制 = ";
    decToOct(64);
    cout << "，0 转八进制 = ";
    decToOct(0);
    cout << endl;

    string tests[] = {"(()[])", "([)]", "(()", "())", "{([])}"};
    cout << "练习 2：" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "  " << tests[i] << " -> " << (bracketMatch(tests[i]) ? "匹配" : "不匹配") << endl;
    }

    cout << "练习 3：请输入入队个数 n：" << endl;
    int n = 0;
    cin >> n;
    queueDemo(n);

    cout << "练习 4：" << endl;
    TwoStackQueue Q;
    initTSQ(Q);
    tsqPush(Q, 1);
    tsqPush(Q, 2);
    tsqPush(Q, 3);
    int x = 0;
    cout << "  出队顺序：";
    while (tsqPop(Q, x))
        cout << x << " ";
    cout << endl;

    return 0;
}
