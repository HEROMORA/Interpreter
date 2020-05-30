cmake_minimum_required(VERSION 3.15)
project(SimpleInterpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(SimpleInterpreter main.c heap.c heap.h bst.c bst.h types.h)