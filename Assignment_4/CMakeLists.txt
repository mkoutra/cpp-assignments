project(Assignment_4)

cmake_minimum_required(VERSION 3.1.4)

add_executable(Assignment_4 PoliticalParty.h
                            std_lib_facilities.h
                            PoliticalParty.cpp
                            Assignment_4.cpp
)

# Without it, the files are not in the same dir as the executable.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/RedParty.txt 
          ${CMAKE_CURRENT_SOURCE_DIR}/BlueParty.txt 
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)