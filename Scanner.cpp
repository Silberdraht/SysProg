//
// Created by noahp on 14/04/2019.
//

#include "Scanner.h"
#include "Symtable.h"
#include "Automat.h"

Scanner::Scanner() {

}

Scanner::~Scanner() {

}

void Scanner::startScanner() {

    char c = ' ';
    while (c != '\0') {                 // loop getting single characters
        c = buffer.getChar();
        automat.checkSymbol(c);
    }

    automat.endAutomat();
}
