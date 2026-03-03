#ifndef DATA_STRUCTURE_C_DSU_H
#define DATA_STRUCTURE_C_DSU_H

/**
 * @brief Initializes the DSU structure for `n` elements.
 *
 * @param n The number of elements to initialize.
 */
void dsu_init(int n);

/**
 * @brief Finds the representative of the set containing `i`.
 *
 * Uses path compression.
 *
 * @param i The element index.
 * @return int The root of the set containing `i`.
 */
int dsu_find(int i);

/**
 * @brief Merges the sets containing `i` and `j`.
 *
 * Uses union by rank.
 *
 * @param i The first element index.
 * @param j The second element index.
 * @return int 1 if the union merged two different sets, 0 otherwise.
 */
int dsu_union(int i, int j);

#endif
