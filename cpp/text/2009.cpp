#include <iostream>
using namespace std;

// 已知一个带有表头结点的单链表，结点结构为：| data | link |
// 假设该链表只给出了头指针 list。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第 k 个位置上的结点（k 为正整数）。若查找成功，算法输出该结点的 data 域的值，并返回 1；否则，只返回 0。
struct Node{
    int data;
    Node *link;
};

int ans(Node *head, int k){
    if(head == NULL || k <= 0){
        return 0;
    }
    Node *p = head;
    Node *q = head;
    for(int i = 0; i < k; i++){
        if(q != NULL && q->link != NULL){
            q = q->link;
        }
        else{
            return 0;
        }
    }
    while(q != NULL){
        q = q->link;
        p = p->link;
    }
        cout << p->data << endl;
        return 1;
}