#include <iostream>
using namespace std;

const int MAXV = 100;
typedef struct // 图的类型定义
{
    int numVertices, numEdges; // 图的顶点数和有向边数
    char verticesList[MAXV];   // 顶点表，MAXV 为已定义常量
    int Edge[MAXV][MAXV];      // 邻接矩阵
} MGraph;

// 2024 真题：判断有向图是否存在唯一的拓扑排序序列，唯一返回 1，否则返回 0
// 思路（矩阵模拟删除 + 重算入度）：
//   每轮找「当前入度为 0 的顶点」，必须恰好一个；删掉它、清空它的出边、重算入度。
//   0 个 → 有环，不存在拓扑序；≥2 个 → 顺序不唯一。
//
// 原写法的错误：
//   ① int A[n][n] 声明后从未赋值，后续 if(A[i][j] != 0) 数的是栈上垃圾值，
//      整个函数与输入 G 无关
//   ② else { return 0; } 只要有顶点入度非 0 就返回 0；而过程中绝大多数顶点
//      入度都 > 0，所以 n >= 2 时几乎一律返回 0（实测 5 过 2 挂，全靠蒙对）
//   ③ 重算入度前没有把 R 清零，在上一轮的值上继续 +\=1，入度被重复累加
//   ④ 没有处理「0 个入度为 0」的情形（有环时应返回 0）
//   ⑤ int A[n][n]、int R[n]、bool sign[n] 都是变长数组（-Wvla），且 A 未初始化
//   ⑥ 内层 for(int i...) 与外层 i 重名，变量遮蔽
//   ⑦ MAXV 取 1000 时 MGraph 有 4MB，按值传参会栈溢出（0xC00000FD）

int uniquely(MGraph G){
    int n = G.numVertices;
    int A[MAXV][MAXV];      // 原写法：int A[n][n]; 变长数组且从未赋值
    int R[MAXV];            // 入度
    bool sign[MAXV];        // 原写法：bool sign[n] = {false}; 变长数组

    // ① 拷贝邻接矩阵，同时初始化标记和入度
    for(int i = 0; i < n; i++){
        sign[i] = false;
        R[i] = 0;
        for(int j = 0; j < n; j++){
            A[i][j] = G.Edge[i][j];
        }
    }

    // ② 统计初始入度
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j] != 0){
                R[j] += 1;
            }
        }
    }

    // ③ 做 n 轮，每轮删掉一个入度为 0 的顶点
    for(int step = 0; step < n; step++){     // 原写法：两层 for 遍历 i、j
        int cnt = 0;                         // 本步入度为 0 的顶点个数
        int pick = -1;
        for(int i = 0; i < n; i++){
            if(!sign[i] && R[i] == 0){
                cnt++;
                if(pick == -1) pick = i;
            }
        }
        // 原写法：else { return 0; } 入度非 0 是正常状态，不能据此返回
        if(cnt != 1){                        // 0 个 → 有环；≥2 个 → 拓扑序不唯一
            return 0;
        }

        sign[pick] = true;                   // 标记该顶点已删除

        for(int k = 0; k < n; k++){          // 清空它的所有出边
            A[pick][k] = 0;
        }

        for(int i = 0; i < n; i++){          // 原写法漏了这句，R 在旧值上累加
            R[i] = 0;
        }
        for(int i = 0; i < n; i++){          // 重算入度
            for(int j = 0; j < n; j++){
                if(A[i][j] != 0){
                    R[j] += 1;
                }
            }
        }
    }
    return 1;
}
