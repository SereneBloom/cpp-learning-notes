// 第 12 课：二叉树的层序遍历（BFS）
//
// 递归的先/中/后序遍历是「一条路走到黑」，而层序遍历要「一层一层按从左到右」访问。
// 靠什么保证顺序？队列。先进先出，正好让上一层的结点排在前、下一层的结点排在后。
//
// 核心循环只有三行：
//   出队一个 -> 打印它 -> 把它的左、右孩子依次入队
//
// 例树（先序输入 1 2 -1 -1 3 4 -1 -1 5 -1 -1）：
//   根是 1；1 的左孩子是 2，右孩子是 3；3 的左孩子是 4，右孩子是 5
// 层序输出：1 2 3 4 5
#include <iostream>
using namespace std;

// 二叉链表结点：数据 + 左孩子 + 右孩子
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

// 按「先序」输入建立二叉树，-1 表示该位置为空
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

// 后序释放：先释放左右子树，再释放自己
void freeTree(TreeNode *t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

// ===================== 队列 =====================
// 与第 09 课的循环队列完全一样，只是数组元素类型从 int 改成 TreeNode*
// 注意：这里存的是「结点的指针」，不是结点的值。存指针才能顺着找到孩子。
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

// 循环队列只能存 MAXSIZE-1 个元素（留一个空位区分空/满）
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

// 当前队列里的元素个数（用来知道「这一层还有几个结点没处理」）
int queueLength(SqQueue &Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// ===================== 层序遍历 =====================
// 版本一：只要求按层序把所有结点打印成一串
void levelOrder(TreeNode *t) {
    if (t == NULL) return;          // 空树直接返回
    SqQueue Q;
    initQueue(Q);
    enQueue(Q, t);                  // 根结点先入队

    while (!queueEmpty(Q)) {
        TreeNode *p;
        deQueue(Q, p);              // ① 出队
        cout << p->data << " ";     // ② 访问
        // ③ 左右孩子依次入队（先左后右，保证同层从左到右）
        if (p->left != NULL) enQueue(Q, p->left);
        if (p->right != NULL) enQueue(Q, p->right);
    }
}

// 版本二：每层单独一行
// 关键思路：进入每一层时，队里的元素「恰好全是这一层的结点」，
// 所以先把当前队长记下来，只出队这么多个，之后新入队的就属于下一层。
void levelOrderByLevel(TreeNode *t) {
    if (t == NULL) return;
    SqQueue Q;
    initQueue(Q);
    enQueue(Q, t);

    int level = 1;
    while (!queueEmpty(Q)) {
        int cur = queueLength(Q);   // 本层结点个数，先记住
        cout << "第 " << level << " 层：";
        for (int i = 0; i < cur; i++) {
            TreeNode *p;
            deQueue(Q, p);
            cout << p->data << " ";
            if (p->left != NULL) enQueue(Q, p->left);
            if (p->right != NULL) enQueue(Q, p->right);
        }
        cout << endl;
        level++;
    }
}

// 版本三：求树的宽度（结点数最多的那一层的结点数）
// 和版本二同构，只是把「本层个数」拿来取最大值
int treeWidth(TreeNode *t) {
    if (t == NULL) return 0;
    SqQueue Q;
    initQueue(Q);
    enQueue(Q, t);

    int maxWidth = 0;
    while (!queueEmpty(Q)) {
        int cur = queueLength(Q);
        if (cur > maxWidth) maxWidth = cur;
        for (int i = 0; i < cur; i++) {
            TreeNode *p;
            deQueue(Q, p);
            if (p->left != NULL) enQueue(Q, p->left);
            if (p->right != NULL) enQueue(Q, p->right);
        }
    }
    return maxWidth;
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

    freeTree(root);
    root = NULL;
    return 0;
}
