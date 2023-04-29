project(Assignment_3)

cmake_minimum_required(VERSION 3.1.4)

add_executable(Assignment__3 Game_window.h
                             Game_window.cpp
                             Assignment__3.cpp
)

add_subdirectory(Assignment_2)

# Without it, the files are not in the same dir as the executable.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Images_dir/Day.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Images_dir/Night.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Images_dir/Doctor.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Images_dir/Civilian.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Images_dir/Gangster.jpg 
          ${CMAKE_CURRENT_SOURCE_DIR}/Players.txt
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "LINK_OPTIONS: ${LINK_OPTIONS}")

# ------------------------------------------------------------------------------------------
# LINK Assignment__3. with GUI & FLTK & Assignment 2 files
target_include_directories(Assignment__3 PUBLIC ${CMAKE_SOURCE_DIR}/fltk-1.3.5 ${CMAKE_BINARY_DIR}/fltk-1.3.5 ${CMAKE_SOURCE_DIR}/GUI ../GUI ./ 
                            ${CMAKE_SOURCE_DIR}/Assignment_3/Assignment_2
)
target_link_directories(Assignment__3 PUBLIC ${CMAKE_BINARY_DIR}/fltk-1.3.5/lib/Debug)

# Not necessary on windows
# target_link_options(chapter.12.3 PUBLIC -lfltk -lm -lpthread -ldl -lfltk_images -lstdc++ -lfltk_jpeg)
# target_compile_options(chapter.12.3 PUBLIC "-D_THREAD_SAFE -D_REENTRANT -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE")
# target_link_directories(chapter.12.3 PUBLIC /usr/local/lib)

target_link_libraries(Assignment__3 PUBLIC bookgui fltk fltk_images Assignment2)
if (APPLE)
    target_link_libraries(Assignment__3 PUBLIC "-framework Cocoa")
endif()
# ------------------------------------------------------------------------------------------

message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_LINK_LIBRARY_FLAGS: ${CMAKE_CXX_LINK_LIBRARY_FLAGS}")