cmake_minimum_required(VERSION 3.13)
project(grafo_adjacencia C)

set(CMAKE_C_STANDARD 11)

add_executable(grafo_adjacencia main.c grafo.c)