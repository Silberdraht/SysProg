//
// Created by noahp on 12/04/2019.
//

#ifndef SYSPROG_BUFFER_H
#define SYSPROG_BUFFER_H

#endif //SYSPROG_BUFFER_H

//#include "LinkedList.h"

class Buffer {

private:
    char *current;
    char *next;
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    int amount_read = 0;

    size_t buffer_size = 16;
    char *file = (char *) "F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\beispieltest.txt";
    //char *file = (char *) ".\\beispieltest.txt";
    void clear_buffer(char **buffer);
    void load(char **buffer);

public:
    Buffer();
    ~Buffer();
    char getChar();


    void delete_buffer(char **buffer);

};



