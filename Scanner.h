//
// Created by noahp on 14/04/2019.
//

#ifndef SYSPROG_SCANNER_H
#define SYSPROG_SCANNER_H

#include "Buffer.h"
#include "Automat.h"


class Scanner {

private:
    Buffer buffer;
    Automat automat;

public:
    Scanner();
    ~Scanner();

    void startScanner();

};


#endif //SYSPROG_SCANNER_H