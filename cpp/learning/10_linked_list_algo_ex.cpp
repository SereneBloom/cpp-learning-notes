// 第 10 课练习：链表高频算法
// 一律使用带头结点的单链表，哨兵 head 不算数据结点
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *initList() {
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    return head;
}

void insertTail(Node *head, int x) {
    Node *tail = head;
    while (tail->next != NULL) tail = tail->next;
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    tail->next = p;
}

void printList(Node *head) {
    for (Node *p = head->next; p != NULL; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *t = head->next;
        delete head;
        head = t;
    }
}

// 练习 1：删除倒数第 k 个结点，要求只遍历一趟
// 思路：fast 先走 k 步，然后 slow、fast 同步走，fast 到尾时 slow 正好在倒数第 k 个的前驱
// 返回是否删除成功（k 超过表长应返回 false）
bool deleteLastKth(Node *head, int k) {
    if (k <= 0) return false;               // 补：k = 0 时循环不跑，f 未初始化会崩
    Node *p = head->next;
    Node *q = head->next;
    for(int i = 0; i < k; i++){
        // 原写法：if(q->next == NULL) 提前一格判断，k == 表长时误判失败
        if(q == NULL){
            return false;
        }
        q = q->next;
    }
    Node *f = head;                          // 原写法：Node *f; 未初始化
    while(q != NULL){
        f = p;
        p = p->next;
        q = q->next;
    }
    f->next = p->next;                       // 原写法：f->next = f->next->next; 结果相同但语义绕
    delete(p);
    return true;
}

// 练习 2：返回环的入口结点，无环返回 NULL
// 思路：快慢指针相遇后，让 slow 回到 head->next，两人每次各走 1 步，再次相遇处就是入口
Node *findCycleEntry(Node *head) {
    Node *slow = head->next;                  // 原命名 show 应为 slow
    Node *fast = head->next;
    // 原写法：while(fast->next->next != NULL && show->next != NULL && fast != show)
    //   ① fast->next 未判空就取 next，空表/短表崩溃
    //   ② 两人起点相同，fast != show 初始为假，循环零次执行
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;              // 相遇即跳出
    }
    // 原写法：没有判无环，永远返回 head->next；题目要求无环返回 NULL
    if (fast == NULL || fast->next == NULL) return NULL;
    slow = head->next;                        // 一个指针回到起点
    // 原写法：while(fast->next != NULL && show && fast != show) 条件多余且重置后立刻结束
    while (slow != fast) {                    // 两人同速走，再相遇处就是入口
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 练习 3：删除非递减有序链表中的重复元素，使每个值只出现一次
// 例：1 1 2 3 3 3 4 -> 1 2 3 4
void deleteDuplicates(Node *head) {
    // 原写法问题：
    //   ① k = p; p = p->next; 后 k 是前驱、p 是后继，重复时 delete(k) 删了要保留的结点
    //   ② k->next = p->next 已经把 p 跨过，却把 k 自己释放，链表断开
    //   ③ delete 后 p 悬空，下一轮 p->next 是 use-after-free
    // 改为「当前 vs 后继」，不需要前驱指针
    Node *p = head->next;
    while (p != NULL && p->next != NULL) {
        if (p->data == p->next->data) {
            Node *del = p->next;
            p->next = del->next;      // p 跨过后继
            delete del;
            // p 不前进：新的后继可能仍重复
        } else {
            p = p->next;              // 不重复才前进
        }
    }
}

// 练习 4：判断两个带头结点的链表是否相交（物理上共用同一个结点）
// 思路：先分别求长度，让长的先走长度差，再同步走，相遇即相交
bool isIntersect(Node *a, Node *b) {
    // 原写法问题：
    //   ① p、q 在 L116/L126 重复声明，编译报 redeclaration
    //   ② 求长度时 while(p != NULL){ a_n++; } 没有 p = p->next，死循环
    //   ③ 比较循环 while(p->next != NULL){...} 同样不前进，死循环
    //   ④ 相交判定要比较结点地址 p == q，不是 p->next == q->next
    Node *p = a->next;
    Node *q = b->next;

    int a_n = 0, b_n = 0;
    for (Node *t = p; t != NULL; t = t->next) a_n++;
    for (Node *t = q; t != NULL; t = t->next) b_n++;

    int k = a_n - b_n;
    if (k > 0) {
        for (int i = 0; i < k; i++) p = p->next;    // a 长，a 先走差值
    } else {
        for (int i = 0; i < -k; i++) q = q->next;   // b 长，b 先走
    }

    while (p != NULL && q != NULL) {
        if (p == q) return true;                    // 地址相同即共用结点
        p = p->next;
        q = q->next;
    }
    return false;
}

int main() {
    // 练习 1 测试：1 2 3 4 5 删倒数第 2 个，应得 1 2 3 5
    Node *L1 = initList();
    for (int i = 1; i <= 5; i++) insertTail(L1, i);
    // TODO: 调用 deleteLastKth(L1, 2) 并 printList(L1)
    cout << "删倒数第 2 个：";
    if (deleteLastKth(L1, 2)) printList(L1); else cout << "delete fail" << endl;
    freeList(L1);

    // k == 表长时删第一个数据结点
    Node *L1b = initList();
    for (int i = 1; i <= 5; i++) insertTail(L1b, i);
    cout << "删倒数第 5 个：";
    if (deleteLastKth(L1b, 5)) printList(L1b); else cout << "delete fail" << endl;
    cout << "空表再删倒数第 5 个（应失败）：";
    if (deleteLastKth(L1b, 5)) printList(L1b); else cout << "delete fail" << endl;
    freeList(L1b);

    // 练习 2 测试：造环 1 2 3 4，尾结点指回第 2 个，入口应是 2
    // TODO: 建表、造环、调用 findCycleEntry、拆环
    Node *L2 = initList();
    for (int i = 1; i <= 4; i++) insertTail(L2, i);
    cout << "无环时入口：";
    if (findCycleEntry(L2) == NULL) cout << "NULL" << endl; else cout << "有返回值" << endl;
    Node *tail2 = L2->next;
    while (tail2->next != NULL) tail2 = tail2->next;
    tail2->next = L2->next->next;              // 尾结点指回结点 2，形成环
    Node *entry = findCycleEntry(L2);
    cout << "环入口：" << (entry != NULL ? entry->data : -1) << endl;
    tail2->next = NULL;                        // 拆环，否则 freeList 会死循环
    freeList(L2);

    // 练习 3 测试：1 1 2 3 3 3 4，应得 1 2 3 4
    Node *L3 = initList();
    for (int i = 0; i < 7; i++) {
        int v[] = {1, 1, 2, 3, 3, 3, 4};
        insertTail(L3, v[i]);
    }
    // TODO: 调用 deleteDuplicates(L3) 并 printList(L3)
    deleteDuplicates(L3);
    cout << "去重后：";
    printList(L3);
    freeList(L3);

    // 全重复的边界
    Node *L3b = initList();
    for (int i = 0; i < 3; i++) insertTail(L3b, 5);
    deleteDuplicates(L3b);
    cout << "全相同时：";
    printList(L3b);
    freeList(L3b);

    // 练习 4 测试：两条链在某个结点后共用
    // TODO: 先各建一条，再让短链的尾结点指向长链中间的某个结点，然后调用 isIntersect
    Node *A4 = initList();                     // 1 2 3 4
    for (int i = 1; i <= 4; i++) insertTail(A4, i);
    Node *B4 = initList();                     // 9
    insertTail(B4, 9);

    cout << "两条独立链表：";
    if (isIntersect(A4, B4)) cout << "相交" << endl; else cout << "不相交" << endl;

    B4->next->next = A4->next->next->next;     // 9 的 next 指向 A 的结点 3，共用后半段
    cout << "共用结点 3 之后：";
    if (isIntersect(A4, B4)) cout << "相交" << endl; else cout << "不相交" << endl;

    B4->next->next = NULL;                     // 断开共用部分，避免重复释放
    freeList(B4);
    freeList(A4);

    return 0;
}
