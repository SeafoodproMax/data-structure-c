cmake_minimum_required(VERSION 4.0)
project(hw5 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw5 main.c
        test.c
        test.h
        test_interface.h)

add_executable(temp temp.c)
