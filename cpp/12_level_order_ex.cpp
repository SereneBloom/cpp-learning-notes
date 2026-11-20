// 第 12 课练习：二叉树的层序遍历
// 建树、释放、队列的代码已经给好，你只写四个遍历/统计函数
#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

// 按先序输入建树，-1 表示空（已给出）
TreeNode *createTree() {
    int x;
    cin >> x;
    if (x == -1) return NULL;
    TreeNode *t = new TreeNode;
    t->data = x;
    t->left = createTree();
    t->right = createTree();
    return t;
}

void freeTree(TreeNode *t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

// ===================== 队列（已给出，不要改） =====================
#define MAXSIZE 100

struct SqQueue {
    TreeNode *data[MAXSIZE];
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

bool enQueue(SqQueue &Q, TreeNode *x) {
    if ((Q.rear + 1) % MAXSIZE == Q.front) return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return true;
}

bool deQueue(SqQueue &Q, TreeNode *&x) {
    if (Q.front == Q.rear) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return true;
}

// 当前队列元素个数
int queueLength(SqQueue &Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// ===================== 练习 =====================

// 练习 1：层序遍历，按 BFS 顺序打印所有结点值，用空格分隔
// 提示：空树直接 return；根入队；循环 { 出队、打印、左孩子入队、右孩子入队 }
void levelOrder(TreeNode *t) {
    // TODO
    if(t == NULL){
        return ;
    }
    SqQueue Q;
    initQueue(Q);
    enQueue(Q, t);
    while(queueLength(Q) != 0){
        TreeNode *x;
        deQueue(Q, x);
        cout << x->data << " ";
        // 原写法缺这两行：出队后没把孩子补到队尾，队列出完根就空了
        if(x->left != NULL){
            enQueue(Q, x->left);
        }
        if(x->right != NULL){
            enQueue(Q, x->right);
        }
    }
    
}

// 练习 2：按层输出，每层单独一行，格式「第 k 层：a b c」
// 提示：每轮开始先用 queueLength(Q) 记住本层结点数 cur，
//       然后 for 循环出队 cur 个结点，边出队边把它们的左右孩子入队。
void levelOrderByLevel(TreeNode *t) {
    // TODO
    if(t == NULL){                 // 补：空树直接返回，否则 enQueue(NULL) 后解引用会崩
        return ;
    }
    SqQueue Q;
    initQueue(Q);
    int level = 1;
    enQueue(Q, t);
    // 原写法：整个函数只跑一遍，没有外层循环，只输出第 1 层
    while(!queueEmpty(Q)){
        int cur = queueLength(Q);  // 原写法：int num 取在循环外，只取一次；必须每轮重新取
        cout << "第 " << level << " 层：";   // 原写法：cout << "这是第" << level << "层" 而且在循环外
        for(int i = 0; i < cur; i ++){
            TreeNode *x;
            deQueue(Q, x);
            cout << x->data << " ";
            // 原写法：enQueue(Q, t->left); enQueue(Q, t->right);  用了 t 而不是 x，且没判空
            if(x->left != NULL){
                enQueue(Q, x->left);
            }
            if(x->right != NULL){
                enQueue(Q, x->right);
            }
        }
        cout << endl;
        level ++;                  // 原写法：level++ 在循环外，只会加一次
    }
}

// 练习 3：求树的宽度（结点最多的那一层的结点数），空树返回 0
// 提示：和练习 2 一样逐层处理，每层把 cur 和当前最大值比较
int treeWidth(TreeNode *t) {
    // TODO
    return 0;
}

// 练习 4（进阶）：判断是否为完全二叉树
// 完全二叉树：按层序编号 1..n 的结点，编号之间没有空档。
// 直观做法：层序遍历时「空孩子也入队」，
//   一旦出队遇到 NULL，说明后面不该再有真结点了；
//   若之后又出队到非空结点，就不是完全二叉树。
// 提示：
//   bool seenNull = false;
//   while 队不空:
//       deQueue 出 p
//       if (p == NULL) seenNull = true;
//       else {
//           if (seenNull) return false;      // null 之后又冒出真结点
//           enQueue(Q, p->left);             // 空孩子也要入队！
//           enQueue(Q, p->right);
//       }
bool isComplete(TreeNode *t) {
    // TODO
    return true;
}

int main() {
    cout << "请按先序输入结点值，-1 表示空：" << endl;
    cout << "例如 1 2 -1 -1 3 4 -1 -1 5 -1 -1" << endl;
    TreeNode *root = createTree();

    cout << "层序遍历：";
    levelOrder(root);
    cout << endl;

    cout << "按层输出：" << endl;
    levelOrderByLevel(root);

    cout << "树的宽度：" << treeWidth(root) << endl;

    cout << "是否完全二叉树：" << (isComplete(root) ? "是" : "否") << endl;

    freeTree(root);
    root = NULL;
    return 0;
}
