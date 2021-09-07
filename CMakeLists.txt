cmake_minimum_required(VERSION 3.13)
project(keyd)

set(CMAKE_C_STANDARD 99)

add_executable(keyd src/main.c src/config.c src/config.h src/keys.h)