//
// Created by noahp on 12/04/2019.
//

#include <malloc.h>
#include "Buffer.h"
#include <fstream>

Buffer::Buffer() {

    load(&buffer1);
    current = buffer1;
    next = buffer1;

}

Buffer::~Buffer() {

    delete_buffer(&buffer1);
    delete_buffer(&buffer2);
    free(current);
    free(next);

}

char Buffer::getChar() {

    current = next;
    if (*current == '\0') {
        if (current == &buffer1[buffer_size]) {
            //delete_buffer(&buffer2);
            clear_buffer(&buffer2);
            load(&buffer2);
            current = buffer2;
            next = buffer2;
        }
        else if (current == &buffer2[buffer_size]) {
            //delete_buffer(&buffer1);
            clear_buffer(&buffer1);
            load(&buffer1);
            current = buffer1;
            next = buffer1;
        }
        else {
            return ' '; //end of lexical analysis
        }
    }
    next++;
    return *current;

}

void Buffer::load(char **buffer) {
    //clear_buffer(buffer);
    if (*buffer != NULL) {
        realloc(*buffer, buffer_size + 1);
    } else {
        *buffer = (char *) malloc(buffer_size + 1);//new char[buffer_size+1];
    }
    //*buffer = 0x00;
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
    buffer[buffer_size] = '\0';
    stream.close();
    amount_read += index;

}

void Buffer::delete_buffer(char **buffer) {
    for (size_t index=buffer_size-1; index != 0; index--) {
        char c = (*buffer)[index];
        delete(&c);
    }
}

void Buffer::clear_buffer(char **buffer) {
    if (*buffer != 0) {
        int counter = (int) (buffer_size - 1);
        while (counter >= 0) {
            (*buffer)[counter] = '\0';
            counter--;
        }
    }
}

//void Buffer::load(char **buffer) {
//    //(buffer == buffer1 ? delete_buffer1() : delete_buffer2());
//    *buffer = (char *) malloc((buffer_size) * sizeof(char));
//
//    std::fstream stream;
//    stream.open("F:\\Studium\\Compilerbau2019\\SysProg\\beispieltest.txt", std::fstream::in);
//    int index = 0;
//    char c;
//    while (index < buffer_size && stream.get(c)) {
//        *buffer[index*sizeof(char)] = c;
//        //*(buffer + index) = c;
//        index++;
//    }
//    //buffer[index] = '\0';
//    stream.close();
//    //buffer1 = buffer;
//}
//
//long Buffer::delete_buffer1() {
//
//    current = buffer1;
//    while (&current) {
//        char *c = current;
//        current = current+1;
//        delete c;
//    }
//
//}
