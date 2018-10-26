    //
    // Created by Silberdraht on 09.10.2018.
    //


    #include "Automat.h"

    LinkedList listAutomat;


    Automat::Automat() {

    }
    Automat::~Automat() {

    }


    //To Fix: Kommentare, Errortokens, IF, Else, EoF
    void Automat::checkSymbol(char c) {


        switch (stateActive) {
            case init:
                //std::cout << "Init: " << std::endl;



                if (isDigit(c)) {
                    currentColumn++;
                    stateActive = digistate;
                    listAutomat.addSymbol(c);

                    //Speichert den Anfang des Tokens
                    startColumn = currentColumn;
                    startLine = currentLine;
                    //Zählt die Postion weiter

                }
                //Alle Sign ausser =, & und :
                if (isSign(c)) {
                    currentColumn++;
                    listAutomat.addSymbol(c);
                    startColumn = currentColumn;
                    startLine = currentLine;

                    createTokenSign();



                }

                if (isSignEqual(c)) {
                    stateActive = equalstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    startColumn = currentColumn;
                    startLine = currentLine;
                    listAutomat.addSymbol(c);


                }

                if(isSignAnd(c)) {
                    stateActive = andstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    startColumn = currentColumn;
                    startLine = currentLine;
                    listAutomat.addSymbol(c);



                }

                if (isSignColon(c)) {
                    stateActive = colonstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    startColumn = currentColumn;
                    startLine = currentLine;
                    listAutomat.addSymbol(c);


                }

                if (isLetter(c)) {

                    stateActive = letterstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    startColumn = currentColumn;
                    startLine = currentLine;
                    listAutomat.addSymbol(c);



                }

                if (isBlank(c)) {
                    currentColumn++;
                    //std::cout << "IsBlank " << std::endl;

                }

                if (isNewLine(c)) {
                    //std::cout << "isNewLine " << std::endl;
                    currentColumn = 0;
                    currentLine++;


                }

                if (isStar(c)) {

                    currentColumn++;
                    stateActive = commentstate;

                }

                if (isError(c)) {


                    currentColumn++;
                    startColumn = currentColumn;
                    startLine = currentLine;

                    listAutomat.addSymbol(c);
                    createTokenError();

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

                if (isSignEqual(c)) {

                    currentColumn++;
                    listAutomat.addSymbol(c);
                    createTokenSign();

                    stateActive = init;
                }

                else if (isStar(c)) {


                    currentColumn++;
                    listAutomat.popSymbol();
                    stateActive = commentstate;

                }

                else {
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

            case commentstate:
                if (c != '\n') {
                    currentColumn++;

                    if (c == '*') {

                        stateActive = commentstate2;
                    }



                } else {

                    currentColumn = 0;
                    currentLine++;


                }

                break;

            case commentstate2:

                if (c != ':') {

                    stateActive = commentstate;
                    checkSymbol(c);

                } else {
                    currentColumn++;
                    stateActive = init;

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
                token.storage.number = this->number;
                break;

            case ErrorToken:
                token.storage.error = listAutomat.popSymbol();

                break;

            case SignToken:

                break;

            case IfToken:

                break;

            case WhileToken:

                break;

        }


        return token;
    }

    Automat::Token Automat::createTokenError() {

        return Automat::createToken(ErrorToken);
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


    return Automat::createToken(DigitToken);
        }
    //Fix return and test

        Automat::Token Automat::createTokenSign() {





            for (int i = listAutomat.listLength(); i > -1; i--) {
                //token.type[i-1] = listAutomat.popSymbol();

                std::cout << listAutomat.popSymbol() << std::endl;

            }

    return createToken(SignToken);
        }


    //To fix set length of lexem
    Automat::Token Automat::createTokenLetter() {

        if (listAutomat.listLength() == 2) {

            char toTest[2];
            char arIf[2] = {'i', 'f'};
            char arIf2[2] = {'I', 'F'};

            toTest[1] = listAutomat.popSymbol();
            toTest[0] = listAutomat.popSymbol();

            if (Automat::isArrayEqual(arIf, toTest, 2) || Automat::isArrayEqual(arIf2, toTest, 2)) {

std::cout << "should create if token" << std::endl;

                return createToken(IfToken);
            }

            listAutomat.addSymbol(toTest[0]);
            listAutomat.addSymbol(toTest[1]);



         }
        else if (listAutomat.listLength() == 5) {

            char toTest[5];
            char arIf[5] = {'w', 'h', 'i','l','e'};
            char arIf2[5] = {'W', 'H', 'I','L','E'};

            toTest[4] = listAutomat.popSymbol();
            toTest[3] = listAutomat.popSymbol();
            toTest[2] = listAutomat.popSymbol();
            toTest[1] = listAutomat.popSymbol();
            toTest[0] = listAutomat.popSymbol();

            if (Automat::isArrayEqual(arIf, toTest, 5) || Automat::isArrayEqual(arIf2, toTest, 5)) {

                std::cout << "should create while token" << std::endl;
                return createToken(WhileToken);
            }

            listAutomat.addSymbol(toTest[0]);
            listAutomat.addSymbol(toTest[1]);
            listAutomat.addSymbol(toTest[2]);
            listAutomat.addSymbol(toTest[3]);
            listAutomat.addSymbol(toTest[4]);


        }

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
            case '–':
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

    bool Automat::isStar(char c) {

        return (c == '*');
    }

    bool Automat::isError(char c) {

        return (!isStar(c) && (!isNewLine(c)) && (!isBlank(c)) && (!isLetter(c)) && (!isDigit(c))
                && (!isSignColon(c)) && (!isSignAnd(c)) && (!isSignEqual(c)) && (!isSign(c)));

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

    bool Automat::isArrayEqual(char ar1[], char ar2[], int length) {

        for (int i = length -1; i > -1; i--) {

            if (ar1[i] != ar2[i]) {

                return false;

            }

        }


        return true;
    }
//Beendet den Automaten
    void Automat::endAutomat() {
    checkSymbol(' ');
    }





