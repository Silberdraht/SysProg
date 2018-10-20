//
// Created by Silberdraht on 09.10.2018.
//


#include "Automat.h"

LinkedList listAutomat;


Automat::Automat() {

}
Automat::~Automat() {

}


//To Fix count line und column
void Automat::checkSymbol(char c) {


    switch (stateActive) {
        case init:
            //std::cout << "Init: " << std::endl;
            if (isDigit(c)) {
                stateActive = digistate;
                listAutomat.addSymbol(c);

                //Speichert den Anfang des Tokens
                startColumn = currentColumn;
                startLine = currentLine;
                //Zählt die Postion weiter
                currentColumn++;
            }
            //Alle Sign ausser =, & und :
            if (isSign(c)) {
                listAutomat.addSymbol(c);
                startColumn = currentColumn;
                startLine = currentLine;
                createTokenSign();
                currentColumn++;


            }

            if (isSignEqual(c)) {
                stateActive = equalstate;

                //Speichert den Anfang des Tokens
                startColumn = currentColumn;
                startLine = currentLine;
                listAutomat.addSymbol(c);
                currentColumn++;

            }

            if(isSignAnd(c)) {
                stateActive = andstate;
                //Speichert den Anfang des Tokens
                startColumn = currentColumn;
                startLine = currentLine;
                listAutomat.addSymbol(c);
                currentColumn++;


            }

            if(isSignColon(c)) {
                stateActive = colonstate;
                //Speichert den Anfang des Tokens
                startColumn = currentColumn;
                startLine = currentLine;
                listAutomat.addSymbol(c);
                currentColumn++;

            }

            if (isLetter(c)) {

                stateActive = letterstate;
                //Speichert den Anfang des Tokens
                startColumn = currentColumn;
                startLine = currentLine;
                listAutomat.addSymbol(c);
                currentColumn++;

            }

            if (isBlank(c)) {
                currentColumn++;


            }

            if (isNewLine(c)) {
                currentColumn = 1;
                currentLine++;


            }
            break;



        case digistate:
            //std::cout << "digit: " << std::endl;
            if (isDigit(c)) {

                listAutomat.addSymbol(c);
                currentColumn++;
            } else {
                //wenn char kein Digit, gehe wieder in
                // initzustand baue ein DigitToken und rufe checkSymbol mit c neu auf.


                createTokenDigit();

                stateActive = init;

                checkSymbol(c);
            }
            break;

        case signstate:
            std::cout << "This should never happen! " << std::endl;

            break;

        case letterstate:
            //std::cout << "Letterstate: " << std::endl;
            if(isLetter(c) || (isDigit(c))) {
                listAutomat.addSymbol(c);

            } else {

                createTokenLetter();
                stateActive = init;
                checkSymbol(c);
            }

            break;

        //Erstes char in der LL ist ein '&'
        case andstate:
            //std::cout << "Andstate: " << std::endl;
            if (isSignAnd(c)) {
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
        case equalstate:
            //std::cout << "equalstate: " << std::endl;
            if (isSignColon(c)) {

                listAutomat.addSymbol(c);
                stateActive = equalcolonstate;

            } else {

                createTokenSign();
                stateActive = init;
                checkSymbol(c);
            }

            break;

        case colonstate:
            //std::cout << "colonstate: " << std::endl;
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
            //In der Liste steht '=' ':'
        case equalcolonstate:
            //std::cout << "equalstate: " << std::endl;
            if (isSignEqual(c)) {
                listAutomat.addSymbol(c);
                createTokenSign();
                stateActive = init;

            } else {
                //Erzeugt ein Token '=' und ein Token ':'
                char temp = listAutomat.popSymbol();
                createTokenSign();
                listAutomat.addSymbol(temp);
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


            counter--;


        }



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
//Wie passe ich die länge von Type an?
    void Automat::createTokenSign() {


        tokenSign token;

        token.type[listAutomat.listLength()];

        for (int i = listAutomat.listLength(); i > -1; i--) {
            //token.type[i-1] = listAutomat.popSymbol();

            std::cout << listAutomat.popSymbol() << std::endl;

        }


    }
//To fix set length of lexem
void Automat::createTokenLetter() {

    tokenIdent token;

    token.lexem[listAutomat.listLength()];

    for (int i = listAutomat.listLength(); i > -1; i--) {
        //token.lexem[i-1] = listAutomat.popSymbol();

        std::cout << listAutomat.popSymbol() << std::endl;
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

bool Automat::isBlank(char c) {

    return c == ' ' || c == '\t';
}

bool Automat::isNewLine(char c) {

    return c == '\n';
}



bool Automat::isSignColon(char c) {
    return c == ':';

}

bool Automat::isSignEqual(char c) {
    return c == '=';
}


bool Automat::isLetter(char c) {


    return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
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


