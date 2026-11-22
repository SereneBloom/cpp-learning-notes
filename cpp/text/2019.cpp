#include <iostream>
using namespace std;

typedef struct node{
    int data;
    struct node *next;
}NODE;

void ans(NODE *L){
    if(L == NULL) return ;
    NODE *p = L->next;
    while(p != NULL && p->next != NULL){   // 原写法用 ||，p 为 NULL 时右侧 p->next 照样求值 → 崩溃
        NODE *q = p;
        // 原写法问题：
        //   ① q 从不前进，走不到尾部
        //   ② 先改 q->next->next = p->next 会接成自环
        //   ③ 外层 p = p->next->next，插入后这个表达式已指错位置
        // 思路：每轮找到尾结点的前驱 q，把尾结点 last 插到 p 之后
        while(q->next->next != NULL){
            q = q->next;
        }
        NODE *last = q->next;
        q->next = NULL;
        last->next = p->next;
        p->next = last;
        p = last->next;
    }
}