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
    while (c != '\0') {
        while (!automat.tokenQueue.isEmpty()) {
            int typeNumber = automat.convertCharToInt(automat.tokenQueue.popSymbol());
            Automat::TokenType tokentype = Automat::TokenType(typeNumber);
            Automat::Token token = automat.createToken(tokentype);
            if (automat.identifier != nullptr && *(automat.identifier) != '\0') {
                token.storage.key = symtable.insert(automat.identifier);
            }
        }
        c = buffer.getChar();
        automat.checkSymbol(c);
    }

    if (!automat.tokenQueue.isEmpty()) {
        int typeNumber = automat.convertCharToInt(automat.tokenQueue.popSymbol());
        Automat::TokenType tokentype = Automat::TokenType(typeNumber);
        Automat::Token token = automat.createToken(tokentype);
        if (automat.identifier != nullptr && *(automat.identifier) != '\0') {
            token.storage.key = symtable.insert(automat.identifier);
        }
    }

    automat.endAutomat();
}
