//
// Created by Silberdraht on 09.10.2018.
//


#ifndef SYSPROG_AUTOMATA_H
#define SYSPROG_AUTOMATA_H

#endif //SYSPROG_AUTOMATA_H

#include <iostream>
#include "LinkedList.h"


class Automat {


public:
    Automat();
    ~Automat();

    //LinkedList list;

    void checkSymbol(char c);






    enum state {
        init,
        final,
        error,
        digistate,
        ifstate,
        whilestate,
        signstate,
        equalstate,
        colonstate,
        andstate,
        equalcolonstate,
        letterstate,
        commentstate,
        commentstate2


    };

    enum TokenType {
        SignToken,
        DigitToken,
        IdentifierToken,
        ErrorToken,
        IfToken,
        WhileToken

    };

    struct Token {
        unsigned int line, column;
        TokenType tokenType;
        union Storage {
            long number;
            //Insert Key für Hash
            char error;


        } storage;




    };


    unsigned int currentLine = 1;
    unsigned int currentColumn = 0;
    unsigned int startColumn;
    unsigned int startLine;
    long number;




    state stateActive = init;

    Token createToken(TokenType tokenType);

    Token createTokenDigit();

    Token createTokenSign();

    Token createTokenLetter();

    Token createTokenError();

    Token createTokenIf();

    Token createTokenWhile();

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