cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_AUFGABE_1
        main.cpp
        Automat.cpp Automat.h
        LinkedList.cpp LinkedList.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        InformationLinkedList.cpp InformationLinkedList.h
        Scanner.cpp Scanner.h TokenList.cpp TokenList.h LinkedList.h)
set(SOURCE_FILES_AUFGABE_2
        LinkedList.h parser/CodeBuilder.h parser/CodeBuilder.cpp)

add_executable(Aufgabe1 ${SOURCE_FILES_AUFGABE_1})
add_executable(Aufgabe2 ${SOURCE_FILES_AUFGABE_2})