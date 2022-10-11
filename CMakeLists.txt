cmake_minimum_required(VERSION 3.23)
project(COMP348_Search_and_Replace C)

set(CMAKE_C_STANDARD 11)

add_executable(a.out replace.c replace.h traversal.c traversal.h text.c text.h report.c report.h)
