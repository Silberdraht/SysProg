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
        if (automat.identifier != nullptr && *(automat.identifier) != '\0') {
            Automat::Token token = automat.createToken(automat.IdentifierToken, automat.identifier);
            token.storage.key = symtable.insert(automat.identifier);
            automat.clearIdentifier();
            //std::cout << symtable.lookup(token.storage.key).getLexem() << " is Lexem" << std::endl;
            //std::cout << symtable.lookup(token.storage.key).getName() << " is Name"<< std::endl;
        }
        c = buffer.getChar();
        automat.checkSymbol(c);
    }

    automat.endAutomat();
}
