//
// Created by noahp on 12/04/2019.
//

#include <fstream>
#include "Buffer.h"

Buffer::Buffer() :
buffer1{std::shared_ptr<char[]> (new char[buffer_size +  1])},
buffer2{std::shared_ptr<char[]> (new char[buffer_size +  1])},
current{buffer1}
{
    load(buffer1);
}

char Buffer::getChar() {
    if(current.operator[](next_char) == '\0'){
        if(next_char < buffer_size){
            return '\0';
        }

        if(current.get() == buffer1.get()){
            //Clear Buffer2
            clear_buffer(buffer2);
            load(buffer2);
            current = buffer2;
            next_char = 0;
        }
        else if(current.get() == buffer2.get()){
            clear_buffer(buffer1);
            load(buffer1);
            current = buffer1;
            next_char = 0;
        }
        else {
            return '\0'; //end
        }
    }
    next_char++;
    return current.operator[](next_char - 1);
}

void Buffer::load(std::shared_ptr<char[]> buffer) {

    std::fstream stream;
    stream.open(file);
    stream.seekg(amount_read);

    int index = 0;
    char c;
    while (index < buffer_size && stream.get(c)) {
        buffer.operator[](index) = '\0';
        buffer.operator[](index) = c;
        index++;
    }
    buffer.operator[](index) = '\0';
    stream.close();
    amount_read += index;
}

void Buffer::clear_buffer(std::shared_ptr<char[]> buffer) {
    int i = 0;
    while(buffer.operator[](i) != '\0'){
        buffer.operator[](i) = 0;
        i++;
    }
}