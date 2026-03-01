#include "mst.h"
#include <stdlib.h>
#include <string.h>

/* 邊的比較函式 */
static int cmp_edge(const void *a, const void *b) {
    Edge *ea = *(Edge **)a;
    Edge *eb = *(Edge **)b;
    return ea->w - eb->w;
}

/* Union-Find 結構 */
typedef struct {
    int *parent;
    int *rank;
} UF;

/* 初始化 UF */
static UF *uf_create(int n) {
    UF *uf = malloc(sizeof(UF));
    uf->parent = malloc(n * sizeof(int));
    uf->rank = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

static int uf_find(UF *uf, int x) {
    if (uf->parent[x] != x)
        uf->parent[x] = uf_find(uf, uf->parent[x]);
    return uf->parent[x];
}

static void uf_union(UF *uf, int x, int y) {
    int px = uf_find(uf, x);
    int py = uf_find(uf, y);
    if (px == py) return;
    if (uf->rank[px] < uf->rank[py]) {
        uf->parent[px] = py;
    } else {
        uf->parent[py] = px;
        if (uf->rank[px] == uf->rank[py])
            uf->rank[px]++;
    }
}

static void uf_free(UF *uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

/* 主函式 */
void generate_mst(Node *start) {
    /* Step 1: 用 BFS 收集所有邊（因為圖可能不只一個連通塊） */
    Edge **edges = malloc(MAX_EDGES * sizeof(Edge *));
    int edge_cnt = 0;
    char *visited = calloc(MAX_NODES, sizeof(char));
    Node **queue = malloc(MAX_NODES * sizeof(Node *));
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start->id] = 1;

    while (front < rear) {
        Node *u = queue[front++];
        for (int i = 0; i < u->edge_count; i++) {
            Edge *e = u->edges[i];
            edges[edge_cnt++] = e;

            Node *v = (e->u == u) ? e->v : e->u;
            if (!visited[v->id]) {
                visited[v->id] = 1;
                queue[rear++] = v;
            }
        }
    }

    free(queue);
    free(visited);

    /* Step 2: 排序所有邊 */
    qsort(edges, edge_cnt, sizeof(Edge *), cmp_edge);

    /* Step 3: Kruskal 演算法 */
    UF *uf = uf_create(MAX_NODES);

    for (int i = 0; i < edge_cnt; i++) {
        Edge *e = edges[i];
        int pu = uf_find(uf, e->u->id);
        int pv = uf_find(uf, e->v->id);
        if (pu != pv) {
            e->keep = 1;        // 選這條邊
            uf_union(uf, pu, pv);
        }
    }

    uf_free(uf);
    free(edges);
}