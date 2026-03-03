#ifndef DATA_STRUCTURE_C_MIN_COST_SPANNING_TREE_H
#define DATA_STRUCTURE_C_MIN_COST_SPANNING_TREE_H

/**
 * @brief Structure representing an edge in the graph.
 */
typedef struct {
    int u;
    int v;
    int weight;
} Edge;

/**
 * @brief Computes the minimum-cost spanning tree using Kruskal's algorithm.
 *
 * @param num_vertices The number of vertices in the graph.
 * @param edges_array The array containing all graph edges.
 * @param num_edges The total number of edges in the array.
 * @return long long The total MST weight, or -1 if the graph is disconnected.
 */
long long kruskal_mcst(int num_vertices, Edge edges_array[], int num_edges);

/**
 * @brief Computes the minimum-cost spanning tree using Prim's algorithm.
 *
 * This implementation uses an adjacency matrix and an O(V) extract-min scan.
 *
 * @param num_vertices The number of vertices in the graph.
 * @param adj_matrix The adjacency matrix, using `INT_MAX` for no direct edge.
 * @return long long The total MST weight, or -1 if the graph is disconnected.
 */
long long prim_mcst(int num_vertices, int adj_matrix[num_vertices][num_vertices]);

#endif
