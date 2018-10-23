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
                currentColumn = 0;
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
                currentColumn++;
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
                currentColumn++;
                listAutomat.addSymbol(c);
                createTokenSign();
                stateActive = init;
            } else {
                createTokenSign();
                stateActive = init;
                checkSymbol(c);

            }

            break;

        case equalstate:
            //std::cout << "equalstate: " << std::endl;
            if (isSignColon(c)) {
                currentColumn++;
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

                currentColumn++;
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
                currentColumn++;
                listAutomat.addSymbol(c);
                createTokenSign();
                stateActive = init;

            } else {
                //Erzeugt ein Token '=' und ein Token ':'
                char temp = listAutomat.popSymbol();
                createTokenSign();
                listAutomat.addSymbol(temp);
                //Passt die Startposition für das zweite Token an.
                startColumn++;
                createTokenSign();
                stateActive = init;
                checkSymbol(c);

            }

            break;
    }
}

Automat::Token Automat::createToken(TokenType tokenType) {

    Token token;
    token.line = getStartLine();
    token.column = getStartColumn();
    token.tokenType = tokenType;

    switch (tokenType) {
        case IdentifierToken:

            break;

        case DigitToken:

            break;

        case ErrorToken:

            break;

        case SignToken:

            break;

        case IfToken:

            break;

        case ElseToken:

            break;

    }


    return token;
}

//TO FIX return value and token creation
    Automat::Token Automat::createTokenDigit() {

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

        this->number = digitValue;

        std::cout << "Int value of Token: " << std::endl;
        std::cout << digitValue << std::endl;


        //Token token = Automat::createToken(DigitToken);
    /*
        token.value = digitValue;
        token.column = startColumn;
        token.line = startLine;
*/
return Automat::createToken(DigitToken);
    }
//Fix return and test
//Wie passe ich die länge von Type an?
    Automat::Token Automat::createTokenSign() {


        tokenSign token;
        token.column = startColumn;
        token.line = startLine;

        token.type[listAutomat.listLength()];

        for (int i = listAutomat.listLength(); i > -1; i--) {
            //token.type[i-1] = listAutomat.popSymbol();

            std::cout << listAutomat.popSymbol() << std::endl;

        }

return createToken(SignToken);
    }
//To fix set length of lexem
Automat::Token Automat::createTokenLetter() {

    tokenIdentifier token;
    token.column = startColumn;
    token.line = startLine;

    token.lexem[listAutomat.listLength()];

    for (int i = listAutomat.listLength(); i > -1; i--) {
        //token.lexem[i-1] = listAutomat.popSymbol();

        std::cout << listAutomat.popSymbol() << std::endl;
    }

return createToken(IdentifierToken);
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

unsigned int Automat::getLine() {

    return this->currentLine;

}

unsigned int Automat::getColumn() {
    return this->currentColumn;
}

unsigned int Automat::getStartColumn() {

    return this->startColumn;
}

unsigned int Automat::getStartLine() {

    return this->startLine;
}

long Automat::getNumber() {

    return this->number;
}





