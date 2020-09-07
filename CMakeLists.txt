cmake_minimum_required(VERSION 3.13)
project(grafo_adjacencia C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_executable(grafo_adjacencia main.c grafo.c)