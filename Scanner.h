//
// Created by noahp on 14/04/2019.
//

#ifndef SYSPROG_SCANNER_H
#define SYSPROG_SCANNER_H

#include "Buffer.h"
#include "Automat.h"
#include "Symtable.h"
#include "TokenList.h"


class Scanner {

private:
    Buffer buffer;
    Automat automat;
    Automat::Token createToken();
    TokenList tokens;

public:
    Scanner();
    ~Scanner();

    Symtable symtable;
    void startScanner();
    Automat::Token nextToken();
    int hasTokens();

};


#endif //SYSPROG_SCANNER_H