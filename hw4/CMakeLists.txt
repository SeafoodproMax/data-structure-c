cmake_minimum_required(VERSION 4.0)
project(hw4 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -g -O0")

add_executable(hw4 main.c
)
add_executable(pA pA.c)
add_executable(pB pB.c)
add_executable(pC pC.c)
add_executable(pD
        pD/main.c
        pD/mst.h
        pD/mst.c)
add_executable(pE pE/main.c
        pE/hash.h
        pE/hash.c)