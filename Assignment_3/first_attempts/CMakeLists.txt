project(chapter12)

cmake_minimum_required(VERSION 3.1.4)

#add_dependencies()
add_executable(my_window my_window.cpp 
                         std_lib_facilities.h 
                         Player.h Round.h 
                         Player.cpp 
                         Round.cpp
)

# Whitout it, the files are not in the same dir as the executable.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Day.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Night.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Players.txt 
          ${CMAKE_CURRENT_SOURCE_DIR}/Doctor.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Civilian.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Gangster.jpg 
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "LINK_OPTIONS: ${LINK_OPTIONS}")

# ------------------------------------------------------------------------------------------
# LINK my_window. with GUI & FLTK
target_include_directories(my_window PUBLIC ${CMAKE_SOURCE_DIR}/fltk-1.3.5 ${CMAKE_BINARY_DIR}/fltk-1.3.5 ${CMAKE_SOURCE_DIR}/GUI ../GUI ./)
target_link_directories(my_window PUBLIC ${CMAKE_BINARY_DIR}/fltk-1.3.5/lib/Debug)

# Not necessary on windows
# target_link_options(chapter.12.3 PUBLIC -lfltk -lm -lpthread -ldl -lfltk_images -lstdc++ -lfltk_jpeg)
# target_compile_options(chapter.12.3 PUBLIC "-D_THREAD_SAFE -D_REENTRANT -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE")
# target_link_directories(chapter.12.3 PUBLIC /usr/local/lib)

target_link_libraries(my_window PUBLIC bookgui fltk fltk_images)
if (APPLE)
    target_link_libraries(my_window PUBLIC "-framework Cocoa")
endif()
# ------------------------------------------------------------------------------------------

message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_LINK_LIBRARY_FLAGS: ${CMAKE_CXX_LINK_LIBRARY_FLAGS}")
