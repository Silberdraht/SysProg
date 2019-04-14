cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp Automat.cpp Automat.h LinkedList.cpp LinkedList.h TestAutomat.cpp TestAutomat.h Buffer.cpp Buffer.h)

add_executable(SysProg ${SOURCE_FILES})