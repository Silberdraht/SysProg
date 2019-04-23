cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Automat.cpp Automat.h
        LinkedList.cpp LinkedList.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        InformationLinkedList.cpp InformationLinkedList.h
        Scanner.cpp Scanner.h TokenList.cpp TokenList.h)

add_executable(SysProg ${SOURCE_FILES})