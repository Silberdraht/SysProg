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
        letterstate


    };

    enum TokenType {
        SignToken,
        DigitToken,
        IdentifierToken,
        ErrorToken,
        IfToken,
        ElseToken

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
    struct tokenDigit {

        int line;
        int column;
        int value;


    };


    struct tokenIdentifier {

        int line;
        int column;
        char lexem[];


    };

    struct tokenError {
        int line;
        int column;

    };


    struct tokenSign {

        char type[];
        int line;
        int column;
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

    bool isLetter(char c);

    bool isDigit(char c);

    bool isSign(char c);

    bool isSignAnd(char c);

    bool isSignEqual(char c);

    bool isSignColon(char c);

    bool isBlank(char c);

    bool isNewLine(char c);

    unsigned int getLine();

    unsigned int getColumn();

    unsigned int getStartLine();

    unsigned int getStartColumn();

    long getNumber();


   int convertCharToInt(char c);





};