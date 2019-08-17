//
// Created by noahp on 14/04/2019.
//

#include "Scanner.h"

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

    }

    if (!automat.tokenQueue.isEmpty()) {
        tokens.addToken(createToken());
    }

    automat.endAutomat();
}


void Scanner::initializeSymtable() {
    plus = symtable.insert((char *) "+");
    minus = symtable.insert((char *) "-");
    equals = symtable.insert((char *) "=");
    star = symtable.insert((char *) "*");
    greater = symtable.insert((char *) ">");
    lesser = symtable.insert((char *) "<");
    sAnd = symtable.insert((char *) "&");
    semicolon = symtable.insert((char *) ";");
    exclamationMark = symtable.insert((char *) "!");
    bracketOpen = symtable.insert((char *) "(");
    bracketClose = symtable.insert((char *) ")");
    curlyBracketOpen = symtable.insert((char *) "{");
    curlyBracketClose = symtable.insert((char *) "}");
    squareBracketOpen = symtable.insert((char *) "[");
    squareBracketClose = symtable.insert((char *) "]");
    colon = symtable.insert((char *) ":");
    colonEquals = symtable.insert((char *) ":=");
    equalsColonEquals = symtable.insert((char *) "=:=");
    andAnd = symtable.insert((char *) "&&");
}


Automat::Token Scanner::createToken() {
    int typeNumber = automat.convertCharToInt(automat.tokenQueue.popSymbol());
    auto tokentype = TokenType(typeNumber);
    Automat::Token token = automat.createToken(tokentype);

    if (tokentype == IdentifierToken) {
        char *str = token.storage.lexem;
        token.storage.key = symtable.insert(str);
    }
    else if (tokentype == SignToken) {
        switch(*token.storage.sign) {

            case '+':
                token.storage.key = plus;
                break;
            case '-':
                token.storage.key = minus;
                break;
            case '*':
                token.storage.key = star;
                break;
            case '<':
                token.storage.key = greater;
                break;
            case '>':
                token.storage.key = lesser;
                break;
            case '&':
                if (*(token.storage.sign+1) == '&') {
                    token.storage.key = andAnd;
                } else {
                    token.storage.key = sAnd;
                }
                break;
            case '!':
                token.storage.key = exclamationMark;
                break;
            case ';':
                token.storage.key = semicolon;
                break;
            case '(':
                token.storage.key = bracketOpen;
                break;
            case ')':
                token.storage.key = bracketClose;
                break;
            case '{':
                token.storage.key = curlyBracketOpen;
                break;
            case '}':
                token.storage.key = curlyBracketClose;
                break;
            case '[':
                token.storage.key = squareBracketOpen;
                break;
            case ']':
                token.storage.key = squareBracketClose;
                break;
            case '=':
                if (*(token.storage.sign+1) == ':' && *(token.storage.sign+2) == '=') {
                    token.storage.key = equalsColonEquals;
                } else {
                    token.storage.key = equals;
                }
                break;
            case ':':
                if (*(token.storage.sign+1) == '=') {
                    token.storage.key = colonEquals;
                } else {
                    token.storage.key = colon;
                }
                break;
            default:
                //token.tokenType = Automat::TokenType(3);
                //token.storage.error = (char) token.storage.sign;
                break;

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


