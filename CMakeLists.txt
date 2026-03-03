cmake_minimum_required(VERSION 4.0)
project(template C)

set(CMAKE_C_STANDARD 11)

add_executable(template main.c
        List/CDLL.c
        Tree/BST.c
        DSU/DSU.c
        bloom_filter.c)

add_executable(f-heap Heap/fibonacci_heap.c)
add_executable(min-cost-spanning-tree Tree/MinCostSpanningTree.c)
add_executable(stack Stack/Stack.c)
add_executable(queue Queue/Queue.c)
