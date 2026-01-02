cmake_minimum_required(VERSION 4.1)
project(scanf C)

set(CMAKE_C_STANDARD 11)

add_executable(scanf
        main.c
        my_scanf.c
)

add_executable(scanf_test
        test_my_scanf.c
        my_scanf.c
)