#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
    int data;
    Node *next;
};
const int MaxSize = 10000;
void ans(Node *HEAD){
    if(HEAD->next == NULL) return ;
    bool N[MaxSize] = {false};
    Node *p = HEAD->next;
    Node *q = HEAD;
    while(p != NULL){
        if(!N[abs(p->data)]){
            N[abs(p->data)] = true;
            p = p->next;
            q = q->next;
        }
        else{
            Node *del = p;
            p = p->next;
            q->next = p;
            delete del;
        }
    }
    return ;
}