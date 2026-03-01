#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_OPERATION -1

typedef struct pair pair;
struct pair {
    int first;
    int second;
};

void unionDSU(int parent[], int rank[], int a, int b);
int findDSU(int parent[], int index);
int countDSU(int parent[], int size);

/*void dprint(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void dp_print(pair arr[], int size) {
    printf("===============================\n");
    for (int i = 0; i < size; i++) {
        printf("%d %d", arr[i].first, arr[i].second);
        printf("\n");
    }
    printf("===============================\n");
}*/
int main(void) {
    while (true) {
        int n, m, q;
        if (scanf("%d %d %d", &n, &m, &q) == EOF) break;

        int villages[n+1], rank[n+1];
        pair u_operations[m+1];    // 1-based union operation array
        for (int i = 0; i <= n; i++) {
            villages[i] = i;
            rank[i] = 0;
        }
        for (int i = 1; i <= m; i++)
            scanf("%d %d", &u_operations[i].first, &u_operations[i].second);
        pair deleted[q];
        for (int i = 0; i < q; i++) {   // removing operations according to q
            int pos;
            scanf("%d", &pos);
            deleted[i].first = u_operations[pos].first;
            deleted[i].second = u_operations[pos].second;
            u_operations[pos].first = NO_OPERATION;
            u_operations[pos].second = NO_OPERATION;
        }
        int output[q+1];
        for (int i = 1; i <= m; i++) {
            if (u_operations[i].first != NO_OPERATION && u_operations[i].second != NO_OPERATION)
                unionDSU(villages, rank, u_operations[i].first, u_operations[i].second);
        }
        output[0] = countDSU(villages, n+1);
        int prev = output[0];
        for (int i = q-1; i >= 0; i--) {
            int idx1 = deleted[i].first, idx2 = deleted[i].second;
            if (findDSU(villages, idx1) != findDSU(villages, idx2)) {
                output[q-i] = prev-1;
                prev = output[q-i];
            } else {
                output[q-i] = prev;
            }
            unionDSU(villages, rank, idx1, idx2);
        }
        for (int i = q; i >= 0; i--) printf("%d\n", output[i]);
        printf("\n");
    }
    return 0;
}

/*
 * village[] -> disjoint set
 * rank[] -> disjoint set
 *
 * u_operations[] -> pair of operations
 *
 * deleted[] -> stack<pair>
 * output[] -> stack<int>
 */
void unionDSU(int parent[], int rank[], int a, int b) {
    a = findDSU(parent, a);
    b = findDSU(parent, b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            parent[a] = b;
        }
        else if (rank[a] > rank[b]) {
            parent[b] = a;
        }
        else {
            parent[b] = a;
            rank[a]++;
        }
    }
}
int findDSU(int parent[], int index) {
    if (parent[index] != index)
        parent[index] = findDSU(parent, parent[index]);
    return parent[index];
}
int countDSU(int parent[], int size) {  // counting how many disjoint sets are there
    int cnt = 0;
    for (int i = 1; i < size; i++) {
        if (parent[i] == i) cnt++;
    }
    return cnt;
}