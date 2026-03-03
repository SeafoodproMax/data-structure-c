#ifndef DATA_STRUCTURE_C_MIN_COST_SPANNING_TREE_H
#define DATA_STRUCTURE_C_MIN_COST_SPANNING_TREE_H

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

long long kruskal_mcst(int num_vertices, Edge edges_array[], int num_edges);
long long prim_mcst(int num_vertices, int adj_matrix[num_vertices][num_vertices]);

#endif
