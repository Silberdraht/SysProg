//
// Created by noahp on 12/04/2019.
//

#include <malloc.h>
#include <fstream>
#include "Buffer.h"


Buffer::Buffer() :
current{std::shared_ptr<char[]> (new char[buffer_size +  1])},
next{std::shared_ptr<char[]> (new char[buffer_size +  1])},
buffer1{std::shared_ptr<char[]> (new char[buffer_size +  1])},
buffer2{std::shared_ptr<char[]> (new char[buffer_size +  1])}
{

    load(buffer1);
    current = buffer1;
    next = buffer1;

}

Buffer::~Buffer() {
}



char Buffer::getChar() {
    if(current.operator[](new_current) == '\0'){
        int i = 0;
        //TODO copy to clear
        //TODO check clear
        /// We use buffer 1 right now
        if(current.get() == buffer1.get()){
            //Clear Buffer2
            clear_buffer(buffer2);
            load(buffer2);
            current = buffer2;
            new_current = 0;
        }
        else if(current.get() == buffer2.get()){
            //Clear Buffer1
            clear_buffer(buffer1);
            load(buffer1);
            current = buffer1;
            new_current = 0;
        }
        else {
            return '\0';
        }
        return current.operator[](new_current);
    }
}


void Buffer::load(std::shared_ptr<char[]> buffer) {

   // if (*buffer != nullptr) {
     //   delete []*buffer;
    //}
    //*buffer = (char *) malloc(buffer_size + 1);//new char[buffer_size+1];

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
