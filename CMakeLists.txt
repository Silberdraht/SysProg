cmake_minimum_required(VERSION 3.6)
project(SysProg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (USE_SANITIZER STREQUAL "Address")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
elseif (USE_SANITIZER STREQUAL "Thread")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
elseif (USE_SANITIZER STREQUAL "Undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
elseif (USE_SANITIZER STREQUAL "Leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=leak")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
elseif (USE_SANITIZER STREQUAL "Memory")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=memory")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
endif()

set(SOURCE_FILES_AUFGABE_1
        main.cpp
        Automat.cpp Automat.h
        LinkedList.cpp LinkedList.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        Scanner.cpp Scanner.h
        tests/ScannerTest.cpp tests/ScannerTest.h)
set(SOURCE_FILES_AUFGABE_2
        main.cpp
        Automat.cpp Automat.h
        LinkedList.cpp LinkedList.h
        Buffer.cpp Buffer.h
        Symtable.cpp Symtable.h
        StringTable.cpp StringTable.h
        Information.cpp Information.h
        Scanner.cpp Scanner.h
        tests/ScannerTest.cpp tests/ScannerTest.h
        parser/CodeBuilder.h parser/CodeBuilder.cpp
        lib/Link_List.h
        AST/ASTNode.h AST/ASTNode.cpp
        AST/ASTBuild/ASTCreator.h AST/ASTBuild/ASTCreator.cpp
        AST/ASTBuild/ASTStack.h AST/ASTBuild/ASTStack.cpp)
set(SOURCE_FILES_PHILIPPS_TESTS
        lib/Link_List.h tests/Link_List_Test.cpp tests/Link_List_Test.h)

add_executable(Aufgabe1 ${SOURCE_FILES_AUFGABE_1})
add_executable(Aufgabe2 ${SOURCE_FILES_AUFGABE_2})
add_executable(Philipp_Test ${SOURCE_FILES_PHILIPPS_TESTS})