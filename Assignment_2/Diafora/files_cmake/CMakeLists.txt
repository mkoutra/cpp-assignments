project(ReadFiles)

cmake_minimum_required(VERSION 3.1.4)

set(CXX_STANDARD 17)

#configure_file(ReadFile_Config.h.in ReadFile_Config.h)

add_executable(files_tests.exe files_tests.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/file.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})