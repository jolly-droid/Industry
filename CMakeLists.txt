cmake_minimum_required(VERSION 3.17)
project(Industry)

set(CMAKE_CXX_STANDARD 98)

add_executable(Industry main.c library.h library.c server.c server.h forkiFork.c)