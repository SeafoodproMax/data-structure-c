cmake_minimum_required(VERSION 4.0)
project(hw1)

set(CMAKE_CXX_STANDARD 20)

add_executable(pA pA.cpp)
add_executable(pB pB.c)
add_executable(pC pC.c)
add_executable(pD pD.c)

add_executable(DS pA.c DS/node.c DS/list.c DS/stack.c DS/queue.c
        pC.c
        pD_arr.c)

