#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 2000005
#define MAXD 2700005

int head[MAXN], to[MAXD], nxt[MAXD], indeg[MAXN];
int n, d, edgeCnt = 0;

void addEdge(int u, int v) {
    to[edgeCnt] = v;
    nxt[edgeCnt] = head[u];
    head[u] = edgeCnt++;
    indeg[v]++;
}

int queue[MAXN];

bool hasCycle() {
    int front = 0, rear = 0, cnt = 0;

    // enqueue all nodes with indegree 0
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) queue[rear++] = i;
    }

    while (front < rear) {
        int u = queue[front++];
        cnt++;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            indeg[v]--;
            if (indeg[v] == 0) queue[rear++] = v;
        }
    }

    return cnt < n;  // 若沒全數出隊，表示有環
}

int main() {
    while (scanf("%d %d", &n, &d) != EOF) {
        // 初始化
        edgeCnt = 0;
        for (int i = 0; i < n; i++) {
            head[i] = -1;
            indeg[i] = 0;
        }

        for (int i = 0; i < d; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
        }

        printf("%d\n", hasCycle() ? 1 : 0);
    }
    return 0;
}