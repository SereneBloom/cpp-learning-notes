#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *ans(Node *str1, Node *str2){
    if (str1 == NULL || str2 == NULL) return NULL;
    Node *p = str1->next;
    Node *q = str2->next;
    int n1 = 0, n2 = 0;
    while(p != NULL){
        n1++;
        p = p->next;
    }
    p = str1->next;
    while(q != NULL){
        n2++;
        q = q->next;
    }
    q = str2->next;
    if(n1 > n2){
        for(int i = 0; i < n1 - n2; i++){
            p = p->next;
        }
    }else{
        for(int i = 0; i < n2 - n1; i++){
            q = q->next;
        }
    }
    while(p != NULL){
        if(p == q){
            return p;
        }
        p = p->next;
        q = q->next;
    }
    return NULL;
}