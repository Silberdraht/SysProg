//
// Created by noahp on 12/04/2019.
//

#ifndef SYSPROG_BUFFER_H
#define SYSPROG_BUFFER_H

#include <fstream>
#include "memory"

class Buffer {
private:
    size_t buffer_size = 16;
    std::shared_ptr<char[]> current;
    std::shared_ptr<char[]> buffer1;
    std::shared_ptr<char[]> buffer2;
    int next_char = 0;
    int amount_read = 0;
    char *file; // = (char *) R"(../input_code.txt)";
    void clear_buffer(std::shared_ptr<char[]> buffer);
    void load(std::shared_ptr<char[]> buffer);

public:
    explicit Buffer(char* file);
    char getChar();
};

#endif //SYSPROG_BUFFER_H