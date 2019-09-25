cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES_AUFGABE_1
        Scanner/main_ScannerOnly.cpp
        Scanner/Automat.cpp Scanner/Automat.h
        Scanner/Buffer.cpp Scanner/Buffer.h
        Scanner/Symtable.cpp Scanner/Symtable.h
        Scanner/StringTable.cpp Scanner/StringTable.h
        Scanner/Information.cpp Scanner/Information.h
        Scanner/Scanner.cpp Scanner/Scanner.h
        lib/Link_List.h
        tests/ScannerTest.cpp tests/ScannerTest.h)
set(SOURCE_FILES_AUFGABE_2
        main.cpp
        Scanner/Automat.cpp Scanner/Automat.h
        Scanner/Buffer.cpp Scanner/Buffer.h
        Scanner/Symtable.cpp Scanner/Symtable.h
        Scanner/StringTable.cpp Scanner/StringTable.h
        Scanner/Information.cpp Scanner/Information.h
        Scanner/Scanner.cpp Scanner/Scanner.h
        tests/ScannerTest.cpp tests/ScannerTest.h
        parser/CodeBuilder.h parser/CodeBuilder.cpp
        lib/Link_List.h
        parser/AST/ASTNode.h parser/AST/ASTNode.cpp
        parser/AST/ASTBuild/ASTCreator.h parser/AST/ASTBuild/ASTCreator.cpp
        parser/AST/ASTBuild/ASTStack.h parser/AST/ASTBuild/ASTStack.cpp)
set(SOURCE_FILES_PHILIPPS_TESTS
        lib/Link_List.h tests/Link_List_Test.cpp tests/Link_List_Test.h)

add_executable(Aufgabe1 ${SOURCE_FILES_AUFGABE_1})
add_executable(Aufgabe2 ${SOURCE_FILES_AUFGABE_2})
add_executable(Philipp_Test ${SOURCE_FILES_PHILIPPS_TESTS})