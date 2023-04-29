# A library with the files from assignment 2 necessary 
# to play the game using the console.
project(Assign2)

cmake_minimum_required(VERSION 3.1.4)

add_library(Assignment2 Player.h 
                        Round.h
                        std_lib_facilities.h
                        Player.cpp
                        Round.cpp
)
