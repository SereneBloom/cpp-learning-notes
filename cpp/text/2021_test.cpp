#include <iostream>
#include <cstdlib>
using namespace std;
#include "2021.cpp"

void init(MGraph &G, int n){
    G.numVertices = n;
    G.numEdges = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G.Edge[i][j] = 0;
}
void addEdge(MGraph &G, int u, int v){
    G.Edge[u][v] = 1;
    G.Edge[v][u] = 1;
}

int refAns(MGraph &G){
    int odd = 0;
    for (int i = 0; i < G.numVertices; i++){
        int d = 0;
        for (int j = 0; j < G.numVertices; j++) if (G.Edge[i][j]) d++;
        if (d % 2) odd++;
    }
    return (odd == 0 || odd == 2) ? 1 : 0;
}

int passCnt = 0, failCnt = 0;

void run(const char *name, MGraph &G){
    int got = IsExistEL(G);
    int want = refAns(G);
    if (got == want){ passCnt++; cout << "[通过] " << name << " 结果=" << got << endl; }
    else { failCnt++; cout << "[失败] " << name << " 结果=" << got << " 期望=" << want << endl; }
}

int main(){
    MGraph G;

    init(G, 1); run("A 单顶点无边（0 奇度）", G);

    init(G, 3); addEdge(G, 0, 1); addEdge(G, 1, 2);
    run("B 路径 1-2-3（2 奇度）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 0, 2); addEdge(G, 0, 3);
    run("C 星形 K1,3（4 奇度）", G);

    init(G, 3); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 0);
    run("D 三角形（0 奇度）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 3); addEdge(G, 3, 0);
    run("E 四边形（0 奇度）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 3); addEdge(G, 3, 0); addEdge(G, 0, 2);
    run("F 四边形+一条对角线（2 奇度）", G);

    init(G, 4);
    addEdge(G, 0, 1); addEdge(G, 0, 2); addEdge(G, 0, 3); addEdge(G, 1, 2); addEdge(G, 1, 3); addEdge(G, 2, 3);
    run("G 完全图 K4（4 奇度）", G);

    init(G, 5); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 3, 4);
    run("H 两条分离的边（4 奇度）", G);

    init(G, 6);
    addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 0);
    addEdge(G, 3, 4); addEdge(G, 4, 5); addEdge(G, 5, 3);
    run("I 两个不相连的三角形（0 奇度，但实际无 EL 路径）", G);

    cout << "手写用例：通过 " << passCnt << " 个，失败 " << failCnt << " 个" << endl;

    // 随机无向图
    int rndPass = 0, rndFail = 0;
    srand(2021);
    for (int t = 0; t < 3000; t++){
        int n = 2 + rand() % 7;
        init(G, n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (rand() % 100 < 35) addEdge(G, i, j);
        if (IsExistEL(G) == refAns(G)) rndPass++;
        else {
            rndFail++;
            if (rndFail <= 3) cout << "[随机失败] n=" << n << endl;
        }
    }
    cout << "随机用例：通过 " << rndPass << " 个，失败 " << rndFail << " 个" << endl;
    cout << "===== 通过 " << (passCnt + rndPass) << " 个，失败 " << (failCnt + rndFail) << " 个 =====" << endl;
    return (failCnt + rndFail) == 0 ? 0 : 1;
}
