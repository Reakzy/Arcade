cmake_minimum_required(VERSION 3.8)
project(cpp_arcade)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/Core.hh
        include/DLLoader.hpp
        include/Elem.hh
        include/IDisplayModule.hh
        include/IGameModule.hh
        include/lib_liblapin.hh
        include/libNcurses.hh
        include/libSfml.hh
        include/Pacman.hh
        include/Protocol.hpp
        include/snake.hh
        src/Core.cpp
        src/DLLoader.cpp
        src/main.cpp
        src_lib/lib_liblapin.cpp
        src_lib/libNcurses.cpp
        src_lib/libSfml.cpp
        src_lib/pacman.cpp
        src_lib/snake.cpp)

add_executable(cpp_arcade ${SOURCE_FILES})