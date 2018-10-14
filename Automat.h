//
// Created by Silberdraht on 09.10.2018.
//

#ifndef SYSPROG_AUTOMATA_H
#define SYSPROG_AUTOMATA_H

#endif //SYSPROG_AUTOMATA_H

#include "LinkedList.h"


class Automat {

private:
    enum state {
        init,
        final,
        error,
        intstate,
        idstate,
        ifstate,
        whilestate,
        signstate,
        mixedstate

    };

    struct tokenInt {

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
    int currentColumn = 0;

    state activState = init;


public:
    Automat();


    void checkSymbol(char c) {

        if (c != '\n' && c != ' ' && c != '/t') {

            //List is empty



            //list.addSymbol(c);



        }

    }

private:
    LinkedList list;


/**
    struct tokenPlus {

        int line;
        int column;
    };

    struct tokenMinus {

        int line;
        int column;
    };

    struct tokenColon {

        int line;
        int column;
    };

    struct tokenStar {

        int line;
        int column;

    };

    struct tokenLessSign {

        int line;
        int column;

    };

    struct tokenMoreSign {

        int line;
        int column;

    };

    struct tokenSemic {

        int line;
        int column;

    };
*/





};