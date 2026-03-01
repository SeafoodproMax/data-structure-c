#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mst.h"

#define MAX_HEAP_SIZE MAX_EDGES+5

bool visited[MAX_NODES];

Edge *minHeap[MAX_HEAP_SIZE];   // 1-based heap array
int rear = 0;
void pushHeap(Edge *newEdge) {
    if (rear >= MAX_HEAP_SIZE-1) {
        perror("Heap Overflow\n");
        return;
    }
    rear++;
    minHeap[rear] = newEdge;
    int child = rear, parent = rear/2;
    while (parent > 0 && minHeap[child]->w < minHeap[parent]->w) {
        Edge *temp = minHeap[child];
        minHeap[child] = minHeap[parent];
        minHeap[parent] = temp;
        child = parent;
        parent = parent/2;
    }
}
void popHeap() {
    if (rear == 0) {
        perror("Heap Underflow\n");
        return;
    }
    minHeap[1] = minHeap[rear];
    rear--;
    int curr = 1;
    while (2*curr <= rear) {
        int lChild = 2*curr;
        int rChild = 2*curr+1;
        int currChild;
        if (rChild <= rear && minHeap[rChild]->w < minHeap[lChild]->w) {
            currChild = rChild;
        }
        else currChild = lChild;
        if (minHeap[curr]->w > minHeap[currChild]->w) {
            Edge *temp = minHeap[currChild];
            minHeap[currChild] = minHeap[curr];
            minHeap[curr] = temp;
            curr = currChild;
            continue;
        }
        break;
    }
}
Edge* getMinHeap() {
    if (rear == 0) return NULL;
    return minHeap[1];
}
bool isEmptyHeap() {
    return rear == 0;
}

void generate_mst(Node *node) {     // Prim's algorithm
    // Initialize min Heap
    rear = 0;
    // Init visited
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
    }
    // Prim's Algo
    Node *currNode = node;
    visited[currNode->id] = true;
    for (int i = 0; i < currNode->edge_count; i++) {
        pushHeap(currNode->edges[i]);
    }
    while (!isEmptyHeap()) {
        Edge *currEdge = getMinHeap();
        popHeap();
        if (visited[currEdge->u->id] && visited[currEdge->v->id]) continue;

        currEdge->keep = 1;
        currNode = visited[currEdge->u->id] ? currEdge->v : currEdge->u;
        visited[currNode->id] = true;
        for (int i = 0; i < currNode->edge_count; i++) {
            Edge *e = currNode->edges[i];
            if (!visited[e->u->id] || !visited[e->v->id])
                pushHeap(e);
        }
    }
}