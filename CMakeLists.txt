cmake_minimum_required (VERSION 2.8)
project (MainCraft)
add_definitions (-std=c++11)

include_directories (include)
set (SRC_DIR src/)

add_executable (mainCraft ${SRC_DIR}mainCraft.cpp)