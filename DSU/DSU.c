//
// Created by 林勁博 on 2025/12/3.
//

#include <stdio.h>

#define MAX_SIZE 100
int parent[MAX_SIZE];
int rank_arr[MAX_SIZE];

/**
 * @brief Initializes the DSU structure for 'n' elements (0 to n-1).
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
 */
int dsu_find(int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = dsu_find(parent[i]);
}

/**
 * @brief Merges the sets containing elements 'i' and 'j'.
 * Uses Union by Rank.
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