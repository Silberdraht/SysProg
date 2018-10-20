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
        idstate,
        ifstate,
        whilestate,
        signstate,
        equalstate,
        colonstate,
        andstate,
        equalcolonstate,
        letterstate,
        mixedstate

    };
    struct tokenDigit {

        int line;
        int column;
        int value;


    };


    struct tokenIdent {

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

    int currentLine = 1;
    int currentColumn = 1;
    int startColumn;
    int startLine;



    state stateActive = init;

    void createTokenDigit();

    void createTokenSign();

    void createTokenLetter();

    bool isLetter(char c);

    bool isDigit(char c);

    bool isSign(char c);

    bool isSignAnd(char c);

    bool isSignEqual(char c);

    bool isSignColon(char c);

    bool isBlank(char c);

    bool isNewLine(char c);


   int convertCharToInt(char c);





};