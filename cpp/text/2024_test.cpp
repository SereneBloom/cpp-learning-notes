// 2024 真题测试文件：判断有向图是否存在唯一拓扑排序
// g++ -std=c++11 -Wall -pedantic -fexec-charset=GBK -o test2024.exe 2024_test.cpp
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "2024.cpp"

void init(MGraph &G, int n){
    G.numVertices = n;
    G.numEdges = 0;
    for (int i = 0; i < n; i++){
        G.verticesList[i] = (char)('A' + i);
        for (int j = 0; j < n; j++) G.Edge[i][j] = 0;
    }
}
void addEdge(MGraph &G, int u, int v){ G.Edge[u][v] = 1; G.numEdges++; }

// 独立标准答案：Kahn，每步统计入度为 0 的顶点个数，必须恰好 1
int refAns(const MGraph &G){
    int n = G.numVertices;
    int indeg[MAXV] = {0};
    bool done[MAXV] = {false};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (G.Edge[i][j]) indeg[j]++;
    for (int step = 0; step < n; step++){
        int cnt = 0, pick = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && indeg[i] == 0){ cnt++; pick = i; }
        if (cnt != 1) return 0;
        done[pick] = true;
        for (int k = 0; k < n; k++) if (G.Edge[pick][k]) indeg[k]--;
    }
    return 1;
}

int pass = 0, fail = 0;

void run(const char *name, MGraph &G){
    int want = refAns(G);
    int got = uniquely(G);
    if (got == want){ pass++; cout << "[通过] " << name << "  结果=" << got << endl; }
    else { fail++; cout << "[失败] " << name << "  结果=" << got << " 期望=" << want << endl; }
}

int main(){
    cout << "===== 2024 真题：唯一拓扑排序判定 测试 =====" << endl;

    MGraph G;

    init(G, 1);
    run("A 单顶点（唯一）", G);

    init(G, 2);
    run("B 两个孤立点（不唯一）", G);

    init(G, 2); addEdge(G, 0, 1);
    run("C 0->1（唯一）", G);

    init(G, 3); addEdge(G, 0, 1); addEdge(G, 1, 2);
    run("D 链 0->1->2（唯一）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 3);
    run("E 链 0->1->2->3（唯一）", G);

    init(G, 2); addEdge(G, 0, 1); addEdge(G, 1, 0);
    run("F 二元环（无拓扑序）", G);

    init(G, 3); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 0);
    run("G 三元环（无拓扑序）", G);

    init(G, 3); addEdge(G, 0, 2); addEdge(G, 1, 2);
    run("H 0->2, 1->2（不唯一）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 0, 2); addEdge(G, 1, 3); addEdge(G, 2, 3);
    run("I 菱形 DAG（不唯一）", G);

    init(G, 3); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 0, 2);
    run("J 0->1,1->2,0->2（唯一，多余边不影响）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 3); addEdge(G, 3, 0);
    run("K 四元环（无拓扑序）", G);

    init(G, 3);
    run("L 三个孤立点（不唯一）", G);

    init(G, 4); addEdge(G, 0, 3); addEdge(G, 1, 3); addEdge(G, 2, 3);
    run("M 三个点都指向 3（不唯一）", G);

    init(G, 5); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 2, 3); addEdge(G, 3, 4); addEdge(G, 0, 4);
    run("N 长链 + 一条跨边（唯一）", G);

    init(G, 4); addEdge(G, 0, 1); addEdge(G, 1, 2); addEdge(G, 0, 3);
    run("O 0->1->2 且 0->3（不唯一）", G);

    cout << "手写用例：通过 " << pass << " 个，失败 " << fail << " 个" << endl;

    // 随机 DAG：先随机一个拓扑次序，再只加「前指向后」的边，保证无环
    srand(2024);
    int rPass = 0, rFail = 0;
    for (int t = 0; t < 3000; t++){
        int n = 2 + rand() % 7;
        init(G, n);
        int order[MAXV];
        for (int i = 0; i < n; i++) order[i] = i;
        for (int i = n - 1; i > 0; i--) swap(order[i], order[rand() % (i + 1)]);
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++)
                if (rand() % 100 < 30) addEdge(G, order[a], order[b]);
        int want = refAns(G);
        int got = uniquely(G);
        if (got == want) rPass++;
        else {
            rFail++;
            if (rFail <= 3) cout << "[随机失败] n=" << n << " got=" << got << " want=" << want << endl;
        }
    }
    cout << "随机 DAG 用例：通过 " << rPass << " 个，失败 " << rFail << " 个" << endl;

    // 随机「可能带环」的图：完全随机加边
    int cPass = 0, cFail = 0;
    for (int t = 0; t < 2000; t++){
        int n = 2 + rand() % 6;
        init(G, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && rand() % 100 < 20) addEdge(G, i, j);
        int want = refAns(G);
        int got = uniquely(G);
        if (got == want) cPass++;
        else {
            cFail++;
            if (cFail <= 3) cout << "[随机带环失败] n=" << n << " got=" << got << " want=" << want << endl;
        }
    }
    cout << "随机带环用例：通过 " << cPass << " 个，失败 " << cFail << " 个" << endl;

    cout << "===== 通过 " << (pass + rPass + cPass) << " 个，失败 "
         << (fail + rFail + cFail) << " 个 =====" << endl;
    return (fail + rFail + cFail) == 0 ? 0 : 1;
}
