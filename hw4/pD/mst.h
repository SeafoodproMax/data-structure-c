#ifndef HW4_MST_H
#define HW4_MST_H

#define MAX_NODES 100000
#define MAX_EDGES 1200000

typedef struct Edge {
    struct Node *u;
    struct Node *v;
    int w;
    char keep;
    void *var;
} Edge;
typedef struct Node {
    int id;
    int edge_count;
    Edge **edges;
    void *var;
} Node;
void generate_mst(Node *node);

#endif //HW4_MST_H