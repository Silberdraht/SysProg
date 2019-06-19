//
// Created by noahp on 12/04/2019.
//

#include <malloc.h>
#include <fstream>
#include "Buffer.h"

Buffer::Buffer() {

    load(&buffer1);
    current = buffer1;
    next = buffer1;

}

Buffer::~Buffer() {

    delete(current);
    delete(next);
    delete(buffer1);
    delete(buffer2);
}



char Buffer::getChar() {

    current = next;
    if (*current == '\0') {
        if (current == &buffer1[buffer_size]) {
            clear_buffer(&buffer2);
            load(&buffer2);
            current = buffer2;
            next = buffer2;
        }
        else if (current == &buffer2[buffer_size]) {
            clear_buffer(&buffer1);
            load(&buffer1);
            current = buffer1;
            next = buffer1;
        }
        else {
            return '\0'; //end of lexical analysis
        }
    }
    next++;
    return *current;

}


void Buffer::load(char **buffer) {

    if (*buffer != nullptr) {
        delete []*buffer;
    }
    *buffer = (char *) malloc(buffer_size + 1);//new char[buffer_size+1];

    std::fstream stream;
    stream.open(file);
    stream.seekg(amount_read);

    int index = 0;
    char c;
    while (index < buffer_size && stream.get(c)) {
        (*buffer)[index] = '\0';
        (*buffer)[index] = c;
        index++;
    }
    (*buffer)[index] = '\0';
    stream.close();
    amount_read += index;

}


void Buffer::clear_buffer(char **buffer) {
    if (*buffer != nullptr) {
        int counter = (int) (buffer_size - 1);
        while (counter >= 0) {
            (*buffer)[counter] = '\0';
            counter--;
        }
    }
}
