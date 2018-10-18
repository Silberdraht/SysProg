//
// Created by Silberdraht on 09.10.2018.
//


#include "Automat.h"

LinkedList listAutomat;


Automat::Automat() {

}
Automat::~Automat() {

}



void Automat::checkSymbol(char c) {


    switch (stateActive) {
        case init:
            if (isDigit(c)) {
                stateActive = digistate;
                listAutomat.addSymbol(c);
            }

            if (isSign(c)) {
                listAutomat.addSymbol(c);
                createTokenSign();


            }

            if (isSignEqual(c)) {
                stateActive = qualstate;
                listAutomat.addSymbol(c);

            }

            if(isSignAnd(c)) {
                stateActive = andstate;
                listAutomat.addSymbol(c);


            }

            if(isSignColon(c)) {
                stateActive = colonstate;
                listAutomat.addSymbol(c);

            }
            break;

        case digistate:
            if (isDigit(c)) {

                listAutomat.addSymbol(c);
            } else {
                //wenn char kein Digit, gehe wieder in
                // initzustand baue ein DigitToken und rufe checkSymbol mit c neu auf.


                //create int token
                createTokenDigit();

                stateActive = init;
                //listAutomat.addSymbol(c);
                checkSymbol(c);
            }
            break;

        case signstate:
            if (isSign(c)) {



            } else {
                createTokenSign();
                stateActive = init;
                checkSymbol(c);

            }
            break;

        //Erstes char in der LL ist ein '='
        case qualstate:
            if (isSignEqual(c)) {
                listAutomat.addSymbol(c);
                createTokenSign();
                stateActive = init;
            } else {
                createTokenSign();
                stateActive = init;
                checkSymbol(c);

            }

            break;
        //TO Fix was passiert wenn ein Doppelpunkt geschrieben wird.
        case andstate:

            if (isSignColon(c)) {


            } else {

                createTokenSign();
                stateActive = init;
                checkSymbol(c);
            }

            break;
    }
}

//TO FIX return value and token creation
    void Automat::createTokenDigit() {
        tokenDigit test;
        int ca[listAutomat.listLength()];
        int counter = listAutomat.listLength();
        int counter2 = counter;
        while (!listAutomat.isEmpty()) {

            //Fügt Inhalte der Verkettenen Liste in ein Char Array
            ca[counter-1] = convertCharToInt(listAutomat.popSymbol());

            //std::cout << ca[counter] << std::endl;

            counter--;


        }
        //std::cout << "Anzahl Counter nach while: " << std::endl;
        //std::cout << counter2 << std::endl;
        //std::cout << ca[0] << std::endl;
        //std::cout << ca[1] << std::endl;
        //std::cout << ca[2] << std::endl;


        int digitValue = 0;
        int power = 1;

        while (counter2 > 0) {

            digitValue += ((ca[counter2-1]) * power);


            power *= 10;
            counter2--;
        }



        std::cout << "Int value of Token: " << std::endl;
        std::cout << digitValue << std::endl;

        tokenDigit token;
        token.value = digitValue;


    }
//Fix return and test
    void Automat::createTokenSign() {


        tokenSign token;

        token.type[listAutomat.listLength()];

        for (int i = listAutomat.listLength(); i > -1; i--) {
            token.type[i-1] = listAutomat.popSymbol();
        }


    }

    bool Automat::isDigit(char c) {

        switch(c) {

            case '0':
                return true;
            case '1':
                return true;
            case '2':
                return true;
            case '3':
                return true;
            case '4':
                return true;
            case '5':
                return true;
            case '6':
                return true;
            case '7':
                return true;
            case '8':
                return true;
            case '9':
                return true;

            default:
                return false;

        }

    }

bool Automat::isSign(char c) {

    switch(c) {

        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '<':
            return true;
        case '>':
            return true;
        case '!':
            return true;
        case ';':
            return true;
        case '(':
            return true;
        case ')':
            return true;
        case '{':
            return true;
        case '}':
            return true;
        case '[':
            return true;
        case ']':
            return true;

        default:
            return false;

    }

}

bool Automat::isSignAnd(char c) {
    return c == '&';

}

bool Automat::isSignColon(char c) {
    return c == ':';

}

bool Automat::isSignEqual(char c) {
    return c == '=';
}


int Automat::convertCharToInt(char c) {

    switch(c) {

        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;

        default:;
    }

}







    //if (c != '\n' && c != ' ' && c != '/t') {

    //  if (isDigit(c)) {


    //  }

    //List is empty



    //list.addSymbol(c);


    //  }


