project(Assignment_1)

cmake_minimum_required(VERSION 3.1.4)

set(CXX_STANDARD 17)

add_library(town_of_salem town_of_salem.cpp)

add_executable(main main.cpp)

target_link_libraries(main town_of_salem)