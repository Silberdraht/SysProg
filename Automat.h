//
// Created by Silberdraht on 09.10.2018.
//


#ifndef SYSPROG_AUTOMATA_H
#define SYSPROG_AUTOMATA_H

#include <iostream>
#include "Symtable.h"

enum TokenType {
    SignToken = 0,
    DigitToken = 1,
    IdentifierToken = 2,
    ErrorToken = 3,
    IfToken = 4,
    WhileToken = 5,
    ElseToken = 6,
    IntToken = 7,
    ReadToken = 8,
    WriteToken = 9
};

struct Token {
    unsigned int line, column;
    TokenType tokenType;
    union Storage {
        Key key; //Insert Key für Hash
        int number;
        char* error;
    } storage;

};

class Automat {


public:
    Link_List<char> listAutomat;
    Link_List<char> tokenQueue;

    void checkSymbol(char c);

    Token createToken(TokenType tokenType);

    void endAutomat();

    static char* copyChar(const char *string);
    int convertCharToInt(char c);

    char *getIdentifer();
    void clearIdentifier();

    char *sign = nullptr;
    char *bufferedSign = nullptr;
    bool useBufferedSign = false;

private:
    char *lexeme = nullptr;
    char *error = nullptr;

    enum state {
        init,
        digitstate,
        equalstate,
        colonstate,
        andstate,
        equalcolonstate,
        letterstate,
        commentstate,
        commentstate2,
        errorstate
    };

    unsigned int currentLine = 1;
    unsigned int currentColumn = 0;
    unsigned int startColumn = 0;
    unsigned int bufferedStartColumn;
    bool useBufferedStartColumn = false;
    unsigned int startLine;
    int number;
    bool precedingCR = false;  //avoiding duplicate new line count on a windows machine

    state stateActive = init;

    void prepareTokenDigit();

    void prepareTokenSign();

    void prepareTokenLetter();

    void prepareTokenError();

    bool isLetter(char c);

    bool isDigit(char c);

    bool isSign(char c);

    bool isSignAnd(char c);

    bool isSignEqual(char c);

    bool isSignColon(char c);

    bool isBlank(char c);

    bool isNewLine(char c);

    bool isEOF(char c);

    bool isStar(char c);

    bool isInvalidCharacter(char c);

    bool isArrayEqual(char ar1[], char ar2[], int length);

    unsigned int getStartLine();

    unsigned int getStartColumn();

    char* getContentsOfAutomat();

};

#endif //SYSPROG_AUTOMATA_H