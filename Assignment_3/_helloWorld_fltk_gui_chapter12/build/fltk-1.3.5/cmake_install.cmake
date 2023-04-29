# Install script for directory: /home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/FL" USE_SOURCE_PERMISSIONS REGEX "/\\.svn$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/FL" USE_SOURCE_PERMISSIONS)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake"
         "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/CMakeFiles/Export/share/fltk/FLTK-Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/CMakeFiles/Export/share/fltk/FLTK-Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/CMakeFiles/Export/share/fltk/FLTK-Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES
    "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/etc/FLTKConfig.cmake"
    "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/CMake/FLTK-Functions.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/etc/UseFLTK.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/bin/fltk-config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "fluid.1" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/fluid.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "fltk-config.1" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/fltk-config.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man3" TYPE FILE RENAME "fltk.3" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/fltk.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man6" TYPE FILE RENAME "blocks.6" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/blocks.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man6" TYPE FILE RENAME "checkers.6" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/checkers.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man6" TYPE FILE RENAME "sudoku.6" FILES "/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/fltk-1.3.5/documentation/src/sudoku.man")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/jpeg/cmake_install.cmake")
  include("/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/fluid/cmake_install.cmake")
  include("/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/src/cmake_install.cmake")
  include("/home/michalis/Documents/CSD/CS150/Assignments/Assignment_3/_helloWorld_fltk_gui_chapter12/build/fltk-1.3.5/test/cmake_install.cmake")

endif()

