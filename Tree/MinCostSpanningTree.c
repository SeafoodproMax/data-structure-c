//
// Created by 林勁博 on 2025/12/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h> // For memset, used in DSU

// ----------------------------------------------------------------------
// I. Mandatory Graph Structures
// ----------------------------------------------------------------------

/**
 * @brief Structure representing an edge in the graph.
 */
typedef struct {
    int u, v;       ///< The two vertices connected by the edge (source and destination).
    int weight;     ///< The weight/cost of the edge.
} Edge;

// ----------------------------------------------------------------------
// II. Disjoint Set Union (DSU) Implementation (from DSU.c)
// ----------------------------------------------------------------------

#define DSU_MAX_SIZE 100 // Renamed to avoid conflicts, ensure this is large enough for your graphs
int parent[DSU_MAX_SIZE];
int rank_arr[DSU_MAX_SIZE];

/**
 * @brief Initializes the DSU structure for 'n' elements (0 to n-1).
 * @param n The number of elements to initialize.
 */
void dsu_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank_arr[i] = 0;
    }
}

/**
 * @brief Finds the representative (root) of the set containing element 'i'.
 * Uses Path Compression.
 * @param i The element index.
 * @return int The root of the set containing i.
 */
int dsu_find(int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = dsu_find(parent[i]);
}

/**
 * @brief Merges the sets containing elements 'i' and 'j'. Uses Union by Rank.
 * @param i The first element index.
 * @param j The second element index.
 * @return int 1 if the union was successful (they were in different sets), 0 otherwise.
 */
int dsu_union(int i, int j) {
    int root_i = dsu_find(i);
    int root_j = dsu_find(j);

    if (root_i != root_j) {
        if (rank_arr[root_i] < rank_arr[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_arr[root_i] > rank_arr[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank_arr[root_i]++;
        }
        return 1;
    }
    return 0;
}

// ----------------------------------------------------------------------
// III. Heap Implementation (from Heap.c) - Required for Prim's *with decrease-key* or simply to manage keys.
//      (Included here as utility functions only, the Prim template uses an array-based simplification)
// ----------------------------------------------------------------------

/**
 * @brief Type definition for the comparison function.
 * returns > 0 if *a has higher priority than *b.
 */
typedef int (*ComparisonFunction)(const void* a, const void* b);

/**
 * @brief Structure representing a generic-logic Heap.
 */
typedef struct Heap {
    int *data;
    size_t size;             ///< Current number of elements in the heap.
    ComparisonFunction comp; ///< Function pointer defining Max/Min Heap logic.
    size_t capacity;         ///< Maximum capacity of the heap (not including index 0).
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap *heap, size_t i) {
    while (i > 1) {
        size_t parent_i = i / 2;
        if (heap->comp(&heap->data[i], &heap->data[parent_i]) > 0) {
            swap(&heap->data[i], &heap->data[parent_i]);
            i = parent_i;
        } else {
            break;
        }
    }
}

void heapify_down(Heap *heap, size_t i) {
    while (2 * i <= heap->size) {
        size_t left_child = 2 * i;
        size_t right_child = 2 * i + 1;
        size_t preferred_i = i;
        if (heap->comp(&heap->data[left_child], &heap->data[preferred_i]) > 0) {
            preferred_i = left_child;
        }
        if (right_child <= heap->size &&
            heap->comp(&heap->data[right_child], &heap->data[preferred_i]) > 0) {
            preferred_i = right_child;
        }

        if (preferred_i != i) {
            swap(&heap->data[i], &heap->data[preferred_i]);
            i = preferred_i;
        } else {
            break;
        }
    }
}

Heap *newHeap(size_t max_capacity, ComparisonFunction comp) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if (!heap) return NULL;

    heap->data = (int *)malloc(sizeof(int) * (max_capacity + 1));
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = max_capacity;
    heap->comp = comp;

    return heap;
}

void freeHeap(Heap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

bool isEmptyHeap(Heap *heap) {
    return heap->size == 0;
}

int topHeap(Heap *heap) {
    if (isEmptyHeap(heap)) {
        return INT_MIN;
    }
    return heap->data[1];
}

void insertHeap(Heap *heap, int data) {
    if (heap->size >= heap->capacity) {
        fprintf(stderr, "Error: Heap is full!\n");
        return;
    }

    heap->size++;
    heap->data[heap->size] = data;
    heapify_up(heap, heap->size);
}

void deleteHeap(Heap *heap) {
    if (isEmptyHeap(heap)) {
        fprintf(stderr, "Error: Heap is empty!\n");
        return;
    }

    heap->data[1] = heap->data[heap->size];
    heap->size--;

    if (heap->size > 0) {
        heapify_down(heap, 1);
    }
}

// ----------------------------------------------------------------------
// IV. Kruskal's Algorithm Template
// ----------------------------------------------------------------------

/**
 * @brief Compares two Edge structures based on their weight for qsort (ascending order).
 * @param a Pointer to the first Edge.
 * @param b Pointer to the second Edge.
 * @return int A value < 0 if edgeA's weight is less than edgeB's, 0 if equal, and > 0 otherwise.
 */
int compareEdges(const void* a, const void* b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

/**
 * @brief Computes the Minimal Cost Spanning Tree (MCST) using Kruskal's Algorithm.
 * @param num_vertices The number of vertices in the graph (0 to num_vertices-1).
 * @param edges_array The array containing all edges of the graph.
 * @param num_edges The total number of edges in the graph.
 * @return long long The total weight of the MCST. Returns -1 if the graph is disconnected.
 */
long long kruskal_mcst(int num_vertices, Edge edges_array[], int num_edges) {
    dsu_init(num_vertices);

    qsort(edges_array, num_edges, sizeof(Edge), compareEdges);

    long long min_cost = 0;
    int edges_in_mst = 0;

    for (int i = 0; i < num_edges; i++) {
        Edge current_edge = edges_array[i];
        int u = current_edge.u;
        int v = current_edge.v;

        if (dsu_find(u) != dsu_find(v)) {
            dsu_union(u, v);
            min_cost += current_edge.weight;
            edges_in_mst++;
        }

        if (edges_in_mst == num_vertices - 1) {
            break;
        }
    }

    if (edges_in_mst == num_vertices - 1) {
        return min_cost;
    } else {
        return -1;
    }
}

// ----------------------------------------------------------------------
// V. Prim's Algorithm Template
// ----------------------------------------------------------------------

/**
 * @brief Computes the Minimal Cost Spanning Tree (MCST) using Prim's Algorithm.
 * * This implementation uses an array-based approach to simulate the priority queue's
 * 'Extract Min' operation (O(V) complexity per step), resulting in O(V^2) total time.
 *
 * @param num_vertices The number of vertices in the graph (0 to num_vertices-1).
 * @param adj_matrix The graph's adjacency matrix where adj_matrix[u][v] is the edge weight.
 * A value of INT_MAX means no direct edge.
 * @return long long The total weight of the MCST. Returns -1 if the graph is disconnected.
 */
long long prim_mcst(int num_vertices, int adj_matrix[num_vertices][num_vertices]) {
    if (num_vertices > DSU_MAX_SIZE) {
        fprintf(stderr, "Error: Graph size exceeds MAX_SIZE limit for this template.\n");
        return -1;
    }

    // key[i]: Minimum weight to connect vertex i to the MST
    int *key = (int *)malloc(sizeof(int) * num_vertices);
    // in_mst[i]: Tracks if vertex i is already included in the MST
    bool *in_mst = (bool *)malloc(sizeof(bool) * num_vertices);

    // Initialization
    for (int i = 0; i < num_vertices; i++) {
        key[i] = INT_MAX;
        in_mst[i] = false;
    }

    key[0] = 0;
    long long total_cost = 0;
    int mst_size = 0;

    while (mst_size < num_vertices) {
        // Step 1: Extract Min (O(V) time)
        int min_key = INT_MAX;
        int u = -1;
        for (int v = 0; v < num_vertices; v++) {
            if (in_mst[v] == false && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        if (u == -1) {
            break;
        }

        in_mst[u] = true;
        total_cost += min_key;
        mst_size++;

        // Step 2: Update adjacent vertices' key values (O(V) time)
        for (int v = 0; v < num_vertices; v++) {
            if (adj_matrix[u][v] != INT_MAX && in_mst[v] == false && adj_matrix[u][v] < key[v]) {
                key[v] = adj_matrix[u][v];
            }
        }
    }

    free(key);
    free(in_mst);

    if (mst_size == num_vertices) {
        return total_cost;
    } else {
        return -1;
    }
}

#define NUM_VERTICES_EX 5
#define NUM_EDGES_EX 7
#define INF INT_MAX

int main() {
    // --- Kruskal Example ---
    printf("--- Kruskal's Algorithm Example ---\n");
    Edge kruskal_edges[NUM_EDGES_EX] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4},
        {3, 4, 16},
        {2, 4, 7}
    };

    long long kruskal_cost = kruskal_mcst(NUM_VERTICES_EX, kruskal_edges, NUM_EDGES_EX);
    if (kruskal_cost != -1) {
        printf("Kruskal MCST Cost: %lld\n", kruskal_cost);
    } else {
        printf("Kruskal: Graph is disconnected.\n");
    }

    // --- Prim Example ---
    printf("\n--- Prim's Algorithm Example ---\n");
    // Adjacency Matrix representation
    int prim_adj_matrix[NUM_VERTICES_EX][NUM_VERTICES_EX] = {
        //   0   1   2   3   4
        {INF, 10,  6,  5, INF}, // 0
        { 10, INF, INF, 15, INF}, // 1
        {  6, INF, INF,  4,  7}, // 2
        {  5, 15,  4, INF, 16}, // 3
        {INF, INF,  7, 16, INF}  // 4
    };

    long long prim_cost = prim_mcst(NUM_VERTICES_EX, prim_adj_matrix);
    if (prim_cost != -1) {
        printf("Prim MCST Cost: %lld\n", prim_cost);
    } else {
        printf("Prim: Graph is disconnected.\n");
    }

    return 0;
}