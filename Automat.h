//
// Created by Silberdraht on 09.10.2018.
//


#ifndef SYSPROG_AUTOMATA_H
#define SYSPROG_AUTOMATA_H

#include <iostream>
#include "LinkedList.h"
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
        long number;
        char* lexem;
        char* sign;
        char error;



    } storage;




};

class Automat {


public:
    Automat();
    ~Automat();

    LinkedList listAutomat;

    LinkedList tokenQueue;

    void checkSymbol(char c);

    void endAutomat();

    char *sign = nullptr;
    char *bufferedSign = nullptr;
    bool useBufferedSign = false;
    void clearSign();

    char *identifier = nullptr;
    void clearIdentifier();

    char* copyChar(const char *string);

    enum state {
        init,
//        final,
//        error,
        digistate,
//        ifstate,
//        whilestate,
//        signstate,
        equalstate,
        colonstate,
        andstate,
        equalcolonstate,
        letterstate,
        commentstate,
        commentstate2


    };





    //TokenType tokenReady = NOT_SET;

    unsigned int currentLine = 1;
    unsigned int currentColumn = 0;
    unsigned int startColumn;
    unsigned int bufferedStartColumn;
    bool useBufferedStartColumn;
    unsigned int startLine;
    long number;

    bool precedingCR = false;  //avoiding duplicate new line count on a windows machine

    state stateActive = init;

    Token createToken(TokenType tokenType);

    void prepareTokenDigit();

    void prepareTokenSign();

    void prepareTokenLetter();

    void prepareTokenError();

//    Token createTokenIf();
//
//    Token createTokenWhile();

    bool isLetter(char c);

    bool isDigit(char c);

    bool isSign(char c);

    bool isSignAnd(char c);

    bool isSignEqual(char c);

    bool isSignColon(char c);

    bool isBlank(char c);

    bool isNewLine(char c);

    bool isStar(char c);

    bool isError(char c);


    bool isArrayEqual(char ar1[], char ar2[], int length);

    unsigned int getLine();

    unsigned int getColumn();

    unsigned int getStartLine();

    unsigned int getStartColumn();

    long getNumber();


   int convertCharToInt(char c);

};

#endif //SYSPROG_AUTOMATA_H