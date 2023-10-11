cmake_minimum_required(VERSION 3.26)
project(exo5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(exo5
        principal_liste.c
        sequences.c
        sequences.h)
