#ifndef DATA_STRUCTURE_C_HEAP_H
#define DATA_STRUCTURE_C_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef int (*ComparisonFunction)(const void *a, const void *b);

typedef struct Heap Heap;

Heap *newHeap(size_t max_capacity, ComparisonFunction comp);
void freeHeap(Heap *heap);

bool isEmptyHeap(Heap *heap);
int topHeap(Heap *heap);

void insertHeap(Heap *heap, int data);
void deleteHeap(Heap *heap);

#endif
