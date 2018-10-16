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

    struct tokenDigit {

        int line;
        int column;
        int value;


    };




    enum state {
        init,
        final,
        error,
        digistate,
        idstate,
        ifstate,
        whilestate,
        signstate,
        mixedstate

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
    int currentColumn = 0;



    state stateActive = init;

    void createTokenDigit();



    bool isDigit(char c);

   int convertChartoInt(char c);



};