# Data Structure Practice (C)

C implementations of core data structures for a Data Structures course, with documented APIs and time complexity.

## Contents

### Basic Data Structures
- Stack
- Queue
- Heap
- Tree
- DSU (Disjoint Set Union)
- Fibonacci Heap

### Homework
- hw1 ~ hw6

## Implemented Structures and Time Complexity

The table below summarizes the exposed operations currently implemented in:
- `Stack/Stack.c`
- `Queue/Queue.c`
- `Heap/Heap.c`
- `Heap/fibonacci_heap.h`
- `DSU/DSU.c`
- `Tree/BST.c`
- `Tree/MinCostSpanningTree.c`


| Area | Structure | Exposed operations | Time complexity |
|---|---|---|---|
| Stack | Fixed-capacity array stack | `newStack`, `freeStack` | `O(n)` for capacity `n` |
| Stack | Fixed-capacity array stack | `isEmpty`, `isFull`, `topStack` | `O(1)` |
| Stack | Fixed-capacity array stack | `pushStack`, `popStack` | `O(1)` |
| Queue | Circular array queue | `newQueue`, `freeQueue` | `O(n)` for capacity `n` |
| Queue | Circular array queue | `isQueueEmpty`, `isQueueFull`, `frontQueue` | `O(1)` |
| Queue | Circular array queue | `pushQueue`, `popQueue` | `O(1)` |
| Heap | Binary heap (array-based, 1-indexed) | `newHeap`, `freeHeap` | `O(n)` for capacity `n` |
| Heap | Binary heap (array-based, 1-indexed) | `isEmptyHeap`, `topHeap` | `O(1)` |
| Heap | Binary heap (array-based, 1-indexed) | `insertHeap`, `deleteHeap` | `O(log n)` |
| Heap | Fibonacci heap | `createHeap` | `O(1)` |
| Heap | Fibonacci heap | `insertHeap` | `O(1)` amortized |
| Heap | Fibonacci heap | `extractMin` | `O(log n)` amortized |
| Heap | Fibonacci heap | `decreaseKey` | `O(1)` amortized |
| Heap | Fibonacci heap | `deleteNode` | `O(log n)` amortized |
| DSU | Disjoint Set Union (path compression + union by rank) | `dsu_init` | `O(n)` |
| DSU | Disjoint Set Union (path compression + union by rank) | `dsu_find`, `dsu_union` | amortized `O(alpha(n))` |
| Tree | Binary search tree (not self-balancing) | `createBST` | `O(1)` |
| Tree | Binary search tree (not self-balancing) | `findMinBST` | `O(h)`; average `O(log n)`, worst `O(n)` |
| Tree | Binary search tree (not self-balancing) | `insertBST`, `searchBST`, `deleteNodeBST` | `O(h)`; average `O(log n)`, worst `O(n)` |
| Tree utility | Kruskal minimum-cost spanning tree | `kruskal_mcst` | `O(E log E)` |
| Tree utility | Prim minimum-cost spanning tree (array-based) | `prim_mcst` | `O(V^2)` |

## Build & Run
```bash
cmake -S . -B build
cmake --build build

./build/template
./build/f-heap
./build/min-cost-spanning-tree
./build/stack
./build/queue
```
