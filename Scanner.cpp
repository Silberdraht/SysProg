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
            tokens.addToken(createToken());
        }
        c = buffer.getChar();
        automat.checkSymbol(c);

//        std::ofstream ofs {"out.txt",std::ios_base::app};
//        ofs  << "Token " <<  << " Line: "<< automat.getLine() << " Column: " << automat.getColumn() << std::endl;
    }

    if (!automat.tokenQueue.isEmpty()) {
        tokens.addToken(createToken());
    }

    automat.endAutomat();
}

void Scanner::initializeSymtable() {
    plus = symtable.insert((char *) "+");
    minus = symtable.insert((char *) "-");;
    equals = symtable.insert((char *) "=");;
    star = symtable.insert((char *) "*");;
    greater = symtable.insert((char *) ">");;
    lesser = symtable.insert((char *) "<");;
    sAnd = symtable.insert((char *) "&");;
    semicolon = symtable.insert((char *) ";");;
    exclamationMark = symtable.insert((char *) "!");;
    bracketOpen = symtable.insert((char *) "(");;
    bracketClose = symtable.insert((char *) ")");;
    curlyBracketOpen = symtable.insert((char *) "{");;
    curlyBracketClose = symtable.insert((char *) "}");;
    squareBracketOpen = symtable.insert((char *) "[");;
    squareBracketClose = symtable.insert((char *) "]");;
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
    else if (tokentype == Automat::SignToken) {

        switch(*token.storage.sign) {

            case '+':
                token.storage.key = plus;
            case '-':
                token.storage.key = minus;
            case '*':
                token.storage.key = star;
            case '<':
                token.storage.key = greater;
            case '>':
                token.storage.key = lesser;
            case '&':
                token.storage.key = sAnd;
            case '!':
                token.storage.key = exclamationMark;
            case ';':
                token.storage.key = semicolon;
            case '(':
                token.storage.key = bracketOpen;
            case ')':
                token.storage.key = bracketClose;
            case '{':
                token.storage.key = curlyBracketOpen;
            case '}':
                token.storage.key = curlyBracketClose;
            case '[':
                token.storage.key = squareBracketOpen;
            case ']':
                token.storage.key = squareBracketClose;
        }
    }
    return token;
}

Automat::Token Scanner::nextToken() {

    return this->tokens.popToken();
}

int Scanner::hasTokens() {
    return !this->tokens.isEmpty();
}


