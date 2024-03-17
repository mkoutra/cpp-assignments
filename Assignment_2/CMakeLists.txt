project(Assignment_2)

cmake_minimum_required(VERSION 3.1.4)

set(CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Players.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Assignment_2.exe std_lib_facilities.h 
                           Player.h 
                           Round.h
                           Assignment_2.cpp
                           Player.cpp 
                           Round.cpp)

