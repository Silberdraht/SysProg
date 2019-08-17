//
// Created by noahp on 23/04/2019.
//

#ifndef SYSPROG_TOKENLIST_H
#define SYSPROG_TOKENLIST_H


#include "Automat.h"

class TokenList {

    struct Symbol {

        Automat::Token token;
        Symbol *next;

    };


public:
    TokenList();

    ~TokenList();


    void addToken(Automat::Token token);

    Automat::Token popToken();

    Automat::Token TokenList::getToken(int i);

    bool isEmpty();

    int listLength();


private:
    Symbol *head;
    int countSymbol = 0;

};


#endif //SYSPROG_TOKENLIST_H
