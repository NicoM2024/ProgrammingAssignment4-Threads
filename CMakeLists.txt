cmake_minimum_required(VERSION 3.30.5)
project(ProgrammingAssignment4_Threads C)

set(CMAKE_C_STANDARD 11)

add_executable(ProgrammingAssignment4_Threads
        findstrings.kschne11-nlmilazz.h
        findstrings.kschne11-nlmilazz.c)

add_executable(Thread_Example
        pthreads-example-simpler.c)