#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MOD 1000000007

typedef struct {
    int head;
    bool end;
} Node;

typedef struct {
    int to;
    int next;
    unsigned char c;
} Edge;

static Node *nodes = NULL;
static Edge *edges = NULL;
static int node_cnt = 0, node_cap = 0;
static int edge_cnt = 0, edge_cap = 0;

static void trim_newline(char *s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}

static void ensure_node_cap(int need) {
    if (need <= node_cap) return;
    int newcap = (node_cap == 0) ? 2 : node_cap;
    while (newcap < need) newcap *= 2;
    Node *p = (Node*)realloc(nodes, (size_t)newcap * sizeof(Node));
    if (!p) { fprintf(stderr, "realloc nodes failed\n"); exit(1); }
    nodes = p;
    node_cap = newcap;
}

static void ensure_edge_cap(int need) {
    if (need <= edge_cap) return;
    int newcap = (edge_cap == 0) ? 4 : edge_cap;
    while (newcap < need) newcap *= 2;
    Edge *p = (Edge*)realloc(edges, (size_t)newcap * sizeof(Edge));
    if (!p) { fprintf(stderr, "realloc edges failed\n"); exit(1); }
    edges = p;
    edge_cap = newcap;
}

static int new_node(void) {
    ensure_node_cap(node_cnt + 1);
    int id = node_cnt++;
    nodes[id].head = -1;
    nodes[id].end = false;
    return id;
}

static int add_edge(int from, unsigned char c, int to) {
    ensure_edge_cap(edge_cnt + 1);
    int id = edge_cnt++;
    edges[id].to = to;
    edges[id].c = c;
    edges[id].next = nodes[from].head;
    nodes[from].head = id;
    return id;
}

// find edge labeled c from node u, return child node id or -1
static int find_child(int u, unsigned char c) {
    for (int e = nodes[u].head; e != -1; e = edges[e].next) {
        if (edges[e].c == c) return edges[e].to;
    }
    return -1;
}

// get or create child via c
static int get_or_create_child(int u, unsigned char c) {
    for (int e = nodes[u].head; e != -1; e = edges[e].next) {
        if (edges[e].c == c) return edges[e].to;
    }
    int v = new_node();
    add_edge(u, c, v);
    return v;
}

static void trie_init(void) {
    free(nodes); free(edges);
    nodes = NULL; edges = NULL;
    node_cnt = node_cap = 0;
    edge_cnt = edge_cap = 0;
    new_node(); // root = 0
}

static void trie_insert(const char *w) {
    int cur = 0;
    for (int i = 0; w[i]; i++) {
        unsigned char c = (unsigned char)w[i];
        if (c < 'a' || c > 'z') return;
        cur = get_or_create_child(cur, c);
    }
    nodes[cur].end = true;
}

static int solve(const char *s) {
    int n = (int)strlen(s);
    int *dp = (int*)calloc((size_t)n + 1, sizeof(int));
    if (!dp) { fprintf(stderr, "calloc dp failed\n"); exit(1); }

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] == 0) continue;
        int cur = 0;
        for (int j = i; j < n; j++) {
            unsigned char c = (unsigned char)s[j];
            if (c < 'a' || c > 'z') break;
            cur = find_child(cur, c);
            if (cur == -1) break;
            if (nodes[cur].end) {
                int v = dp[j + 1] + dp[i];
                if (v >= MOD) v -= MOD;
                dp[j + 1] = v;
            }
        }
    }

    int ans = dp[n];
    free(dp);
    return ans;
}

int main(void) {
    char s[5005];
    char line[6000];

    while (true) {
        if (!fgets(s, sizeof(s), stdin)) break;
        trim_newline(s);
        if (s[0] == '\0') continue;

        if (!fgets(line, sizeof(line), stdin)) break;
        int k = atoi(line);

        trie_init();
        for (int i = 0; i < k; i++) {
            if (!fgets(line, sizeof(line), stdin)) return 0;
            trim_newline(line);
            trie_insert(line);
        }

        printf("%d\n", solve(s));
    }

    free(nodes);
    free(edges);
    return 0;
}