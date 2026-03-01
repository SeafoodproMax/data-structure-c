#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Heap {
    // This Heap is suggested to be implemented with 1-based index
    int *arr;
    int tail;
    int MAX_HEAP_SIZE;
} *Heap;

int swap(int *a, int *b);

Heap initHeap(int maxSize);
void freeHeap(Heap heap);
bool isEmptyHeap(Heap heap);
void bubbleDownHeap(Heap heap, int keyIndex);
void bubbleUpHeap(Heap heap, int keyIndex);
void pushHeap(Heap heap, int num);
int popHeap(Heap heap);
void increaseKey(Heap heap, int index, int delta);

int main() {
    while (true) {
        int N;
        if (scanf("%d", &N) == EOF) {
            break;
        }
        getchar();  // consume '\n'

        Heap heap = initHeap(N);
        for (int i = 0; i < N; i++) {
            char buffer[256];
            fgets(buffer, 256, stdin);
            int operation;
            sscanf(buffer, "%d", &operation);
            switch (operation) {
                case 0:     // TODO: Inserting x into the heap
                    int x;
                    sscanf(buffer, "%*[^ ]%d", &x);
                    pushHeap(heap, x);
                    break;
                case 1:     // TODO: Sub heap[1] by heap[2] and rebalance
                    int first = popHeap(heap), second = popHeap(heap);
                    pushHeap(heap, first - second);
                    break;
                case 2:     // TODO: Change the (0-based) index value by increasing "delta"
                    sscanf(buffer, "%*[^ ]%d %d", &first, &second);
                    increaseKey(heap, first+1, second);  // Convert to 1-based index
                    break;
                default:
            }
        }
        for (int i = 1; i <= heap->tail; i++) {
            printf("%d ", heap->arr[i]);
        }
        printf("\n");
        freeHeap(heap);
    }
    return 0;
}


int swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    return 0;
}
Heap initHeap(int maxSize) {
    // This Heap is 1-based index
    Heap heap = malloc(sizeof(Heap));
    heap->arr = (int*)malloc(sizeof(int)*(maxSize+1));  // 1-based index
    heap->tail = 0;
    heap->MAX_HEAP_SIZE = maxSize;
    return heap;
}
void freeHeap(Heap heap) {
    free(heap->arr);
    free(heap);
}
bool isEmptyHeap(Heap heap) {
    return heap->tail == 0;
}
int topHeap(Heap heap) {
    if (isEmptyHeap(heap)) {
        perror("Heap is empty\n");
        return -1;
    }
    return heap->arr[1];
}
void pushHeap(Heap heap, int num) {
    if (heap->tail+1 > heap->MAX_HEAP_SIZE) {
        perror("Heap is full\n");
        return;
    }
    heap->arr[++heap->tail] = num;
    int keyIndex = heap->tail;
    bubbleUpHeap(heap, keyIndex);
}
int popHeap(Heap heap) {
    if (isEmptyHeap(heap)) {
        perror("Pop from an empty heap\n");
    }

    const int top = heap->arr[1];

    if (heap->tail == 1) {     // ← 特判只剩一個元素
        --heap->tail;
        return top;
    }
    // Bubble down
    swap(&heap->arr[1], &heap->arr[heap->tail]);
    --heap->tail;
    int keyIndex = 1;
    bubbleDownHeap(heap, keyIndex);
    return top;
}
void bubbleDownHeap(Heap heap, int keyIndex) {
    if (keyIndex < 1 || keyIndex > heap->tail) {
        perror("Invalid parent index in bubbleDownHeap\n");
        return;
    }
    while (keyIndex*2 <= heap->tail) {
        int leftChild = keyIndex*2, rightChild = keyIndex*2+1, bigChild;
        if (rightChild <= heap->tail) {
            bigChild = (heap->arr[leftChild] >= heap->arr[rightChild]) ? leftChild : rightChild;
        } else {
            bigChild = leftChild;
        }
        if (heap->arr[keyIndex] < heap->arr[bigChild]) {
            swap(&heap->arr[keyIndex], &heap->arr[bigChild]);
            keyIndex = bigChild;
        } else {
            break;
        }
    }
}
void bubbleUpHeap(Heap heap, int keyIndex) {
    if (keyIndex < 1 || keyIndex > heap->tail) {
        perror("Invalid parent index in bubbleUpHeap\n");
        return;
    }
    int parent = keyIndex/2;
    while (parent >= 1) {  // Have parent
        if (heap->arr[keyIndex] > heap->arr[parent]) {
            swap(&heap->arr[keyIndex], &heap->arr[parent]);
            keyIndex = parent;
            parent = keyIndex/2;
        } else {
            break;
        }
    }
}
void increaseKey(Heap heap, int index, int delta) {
    heap->arr[index] += delta;
    int parent = index/2, leftChild = index*2, rightChild = leftChild+1;
    if (parent >= 1 && heap->arr[index] > heap->arr[parent]) {
        bubbleUpHeap(heap, index);
    } else if (leftChild <= heap->tail) {   // Has at least left child
        bubbleDownHeap(heap, index); // Do nothing if no need to bubble down
    }
}