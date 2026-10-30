cmake_minimum_required(VERSION 4.3)
project(ProgrammingAssignment4_Threads C)

set(CMAKE_C_STANDARD 11)

add_executable(ProgrammingAssignment4_Threads
        pthreads-example-simpler.c
        findstrings.kschne11-nlmilazz.h
        findstrings.kschne11-nlmilazz.c)
