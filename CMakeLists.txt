cmake_minimum_required(VERSION 3.14)
project(SimpleInterpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(SimpleInterpreter main.c DataStructures/heap.c DataStructures/heap.h DataStructures/bst.c DataStructures/bst.h DataStructures/stack.c DataStructures/stack.h validations.c validations.h tools.c tools.h ReadEvaluate/evaluation.c ReadEvaluate/evaluation.h ReadEvaluate/io.c ReadEvaluate/io.h DataStructures/types.h)