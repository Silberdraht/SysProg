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
set(CMAKE_CXX_STANDARD 17)
add_executable(Aufgabe1 ${SOURCE_FILES} cmake-build-debug/parser/generateasb.cpp cmake-build-debug/parser/generateasb.h)
add_executable(Aufgabe2 ${SOURCE_FILES} cmake-build-debug/parser/generateasb.cpp cmake-build-debug/parser/generateasb.h cmake-build-debug/parser/Node.cpp cmake-build-debug/parser/Node.h)