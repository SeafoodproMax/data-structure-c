cmake_minimum_required(VERSION 4.0)
project(template C)

set(CMAKE_C_STANDARD 11)

add_executable(template main.c
        List/CDLL.c)

add_executable(heap Heap/Heap.c)
