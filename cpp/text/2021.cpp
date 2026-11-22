#include <iostream>
using namespace std;
const int MAXV = 100;

typedef struct{
    int numVertices, numEdges;
    char VerticesList[MAXV];
    int Edge[MAXV][MAXV];
}MGraph;

// 2021 真题：判断无向图 G 中是否存在欧拉路径（EL 路径）
//
// 原写法（错误）：
//   ① 无向图中 C[i]、R[i] 都等于顶点 i 的度数（边在两个方向各记一次），
//      C[i] + R[i] = 2 × 度数，恒为偶数 → count 永远是 0 → 函数无条件返回 1
//   ② int R[G.numVertices]; 是变长数组（VLA，非标准 C++），且未初始化，
//      C[i]++ 在垃圾值上累加，属未定义行为（-Wall 不报，-pedantic 才报）
//   ③ 严格定义还要求非孤立顶点构成的子图连通（官方数据一般保证连通）
//
// 正确判据（无向图）：度数为奇数的顶点个数为 0 或 2

int IsExistEL(MGraph G){
    int odd = 0;                                  // 奇度顶点个数
    for(int i = 0; i < G.numVertices; i++){
        int deg = 0;
        for(int j = 0; j < G.numVertices; j++){
            // 原写法：C[i]++; R[j]++; 然后判 (C[i]+R[i]) % 2
            if(G.Edge[i][j] != 0){
                deg++;                            // 无向图：第 i 行非零个数就是 i 的度数
            }
        }
        if(deg % 2 != 0){
            odd++;
        }
    }
    if(odd == 0 || odd == 2){
        return 1;
    }
    return 0;
}
