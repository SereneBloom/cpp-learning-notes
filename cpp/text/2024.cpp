#include <iostream>
using namespace std;

const int MAXV = 1000;
typedef struct // 图的类型定义
{
    int numVertices, numEdges; // 图的顶点数和有向边数
    char verticesList[MAXV];   // 顶点表，MAXV 为已定义常量
    int Edge[MAXV][MAXV];      // 邻接矩阵
} MGraph;

int uniquely(MGraph G){
    int R[G.numVertices]; // 记录入度
    int C[G.numVertices]; // 记录出度
    for(int i = 0; i < G.numVertices; i++){
        R[i] = 0;
        C[i] = 0;
    }
    for(int i = 0; i < G.numVertices; i++){
        for(int j = 0; j < G.numVertices; j++){
            if(G.Edge[i][j] != 0){
                R[j] += 1;
                C[i] += 1;
            }
        }
    }
}