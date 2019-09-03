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
        Scanner.cpp Scanner.h TokenList.cpp TokenList.h
        lib/Link_List.h parser/Test.cpp parser/Test.h)
set(SOURCE_FILES_AUFGABE_2
        parser/generateasb.cpp parser/generateasb.h
        parser/Node.cpp parser/Node.h
        lib/Link_List.h)
set(SOURCE_FILES_PHILIPPS_TESTS
        lib/Link_List.h tests/Link_List_Test.cpp tests/Link_List_Test.h)

add_executable(Aufgabe1 ${SOURCE_FILES_AUFGABE_1})
add_executable(Aufgabe2 ${SOURCE_FILES_AUFGABE_2})
add_executable(Philipp_Test ${SOURCE_FILES_PHILIPPS_TESTS})