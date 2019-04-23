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
            createToken(); //TODO do smth with created token
        }
        c = buffer.getChar();
        automat.checkSymbol(c);
    }

    if (!automat.tokenQueue.isEmpty()) {
        createToken();
    }

    automat.endAutomat();
}

Automat::Token Scanner::createToken() {
    int typeNumber = automat.convertCharToInt(automat.tokenQueue.popSymbol());
    auto tokentype = Automat::TokenType(typeNumber);
    Automat::Token token = automat.createToken(tokentype);
    if (tokentype == Automat::IdentifierToken) {
        char *str = token.storage.lexem;
        token.storage.key = symtable.insert(str);
//        std::cout << symtable.lookup(token.storage.key).getLexem() << std::endl;
    }
    return token;
}
