//
// Created by noahp on 12/04/2019.
//

#ifndef SYSPROG_BUFFER_H
#define SYSPROG_BUFFER_H



#include <malloc.h>
#include <fstream>

class Buffer {

private:
    char *current = nullptr;
    char *next = nullptr;
    char *buffer1 = nullptr;
    char *buffer2 = nullptr;
    int amount_read = 0;

    size_t buffer_size = 16;
    char *file = (char *) "F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\beispieltest.txt";
   // char *file = (char *) R"(../beispieltest.txt)";
    void clear_buffer(char **buffer);
    void delete_buffer(char **buffer);
    void load(char **buffer);

public:
    Buffer();
    ~Buffer();
    char getChar();

};


#endif //SYSPROG_BUFFER_H