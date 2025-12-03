cmake_minimum_required(VERSION 4.0)
project(template C)

set(CMAKE_C_STANDARD 11)

add_executable(template main.c
        List/CDLL.c
        Tree/BST.c
        DSU/DSU.c)

add_executable(DSU DSU/DSU.c)
