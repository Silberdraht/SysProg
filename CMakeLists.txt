cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES_AUFGABE_1
        main.cpp
        Automat.cpp Automat.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        Scanner.cpp Scanner.h
        tests/ScannerTest.cpp tests/ScannerTest.h)
set(SOURCE_FILES_AUFGABE_2
        main.cpp
        Automat.cpp Automat.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        Scanner.cpp Scanner.h
        tests/ScannerTest.cpp tests/ScannerTest.h
        parser/CodeBuilder.h parser/CodeBuilder.cpp
        lib/Link_List.h lib/Stack.h
        AST/ASTNode.h AST/ASTNode.cpp
        AST/ASTBuild/ASTCreator.h AST/ASTBuild/ASTCreator.cpp
        AST/ASTBuild/ASTStack.h AST/ASTBuild/ASTStack.cpp)
set(SOURCE_FILES_PHILIPPS_TESTS
        lib/Link_List.h tests/Link_List_Test.cpp tests/Link_List_Test.h)

add_executable(Aufgabe1 ${SOURCE_FILES_AUFGABE_1})
add_executable(Aufgabe2 ${SOURCE_FILES_AUFGABE_2})
add_executable(Philipp_Test ${SOURCE_FILES_PHILIPPS_TESTS})