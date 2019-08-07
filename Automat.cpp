    //
    // Created by Silberdraht on 09.10.2018.
    //


    #include "Automat.h"
#include "Scanner.h"

    //LinkedList listAutomat;


    Automat::Automat() {

    }
    Automat::~Automat() {

    }


    void Automat::checkSymbol(char c) {

        switch (stateActive) {
            case init:
                //std::cout << "Init: " << std::endl;

                if (isDigit(c)) {
                    precedingCR = false; //Carriage Return not followed by a \n;
                    currentColumn++;
                    stateActive = digistate;
                    listAutomat.addSymbol(c);

                    //Speichert den Anfang des Tokens
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;
                    //Zählt die Postion weiter
                }

                //Alle Sign ausser =, & und :
                else if (isSign(c)) {
                    precedingCR = false;
                    currentColumn++;
                    listAutomat.addSymbol(c);
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;

                    prepareTokenSign();
                }

                else if (isSignEqual(c)) {
                    precedingCR = false;
                    stateActive = equalstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;
                    listAutomat.addSymbol(c);
                }

                else if(isSignAnd(c)) {
                    precedingCR = false;
                    stateActive = andstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;
                    listAutomat.addSymbol(c);
                }

                else if (isSignColon(c)) {
                    precedingCR = false;
                    stateActive = colonstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;
                    listAutomat.addSymbol(c);
                }

                else if (isLetter(c)) {
                    precedingCR = false;
                    stateActive = letterstate;
                    currentColumn++;
                    //Speichert den Anfang des Tokens
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;
                    listAutomat.addSymbol(c);
                }

                else if (isBlank(c)) {
                    precedingCR = false;
                    currentColumn++;
                    //std::cout << "IsBlank " << std::endl;
                }

                else if (isNewLine(c)) {
                    //std::cout << "isNewLine " << std::endl;
                    if (!precedingCR) {
                        currentColumn = 0;
                        currentLine++;
                    }
                }


                else if (isError(c)) {
                    precedingCR = false;
                    currentColumn++;
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;

                    listAutomat.addSymbol(c);
                    prepareTokenError();
                }

                break;



            case digistate:
                //std::cout << "digit: " << std::endl;
                if (isDigit(c)) {

                    listAutomat.addSymbol(c);
                    currentColumn++;
                }

                else {
                    //wenn char kein Digit, gehe wieder in
                    // initzustand baue ein DigitToken und rufe checkSymbol mit c neu auf.
                    prepareTokenDigit();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }
                break;


            case letterstate:
                //std::cout << "Letterstate: " << std::endl;
                if(isLetter(c) || (isDigit(c))) {
                    currentColumn++;
                    listAutomat.addSymbol(c);
                }

                else {
                    prepareTokenLetter();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }

                break;

            //Erstes char in der LL ist ein '&'
            case andstate:

                if (isSignAnd(c)) {
                    currentColumn++;
                    listAutomat.addSymbol(c);
                    prepareTokenSign();
                    stateActive = init;
                }

                else {
                    prepareTokenSign();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }

                break;

            case equalstate:

                if (isSignColon(c)) {
                    currentColumn++;
                    listAutomat.addSymbol(c);
                    stateActive = equalcolonstate;
                }

                else {

                    prepareTokenSign();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }

                break;

            case colonstate:

                if (isSignEqual(c)) {

                    currentColumn++;
                    listAutomat.addSymbol(c);
                    prepareTokenSign();
                    stateActive = init;
                }

                else if (isStar(c)) {

                    currentColumn++;
                    listAutomat.popSymbol();
                    stateActive = commentstate;
                }

                else {
                    prepareTokenSign();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }

                break;

                //In der Liste steht '=' ':'
            case equalcolonstate:
                //std::cout << "equalstate: " << std::endl;
                if (isSignEqual(c)) {
                    currentColumn++;
                    listAutomat.addSymbol(c);
                    prepareTokenSign();
                    stateActive = init;
                }

                else {
                    //Erzeugt ein Token '=' und ein Token ':'
                    char temp = listAutomat.popSymbol();
                    prepareTokenSign();
                    listAutomat.addSymbol(temp);
                    //Passt die Startposition für das zweite Token an.
                    currentColumn++; //startColumn++;
                    prepareTokenSign();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }

                break;

            case commentstate:
                if (c != '\n') {
                    currentColumn++;

                    if (c == '*') {
                        stateActive = commentstate2;
                    }
                }

                else {

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

        Token token{};
        token.line = getStartLine();
        token.column = getStartColumn();
        token.tokenType = tokenType;

        switch (tokenType) {
            case IdentifierToken:
                token.storage.lexem = copyChar(identifier);
                this->clearIdentifier();
//                std::cout << token.tokenType << " " << token.storage.lexem << std::endl;
                break;

            case DigitToken:
                token.storage.number = this->number;
//                std::cout << token.tokenType << " " << token.storage.number << std::endl;
                break;

            case ErrorToken:
                token.storage.error = listAutomat.popSymbol();
//                std::cout << token.tokenType << " " << token.storage.error << std::endl;
                break;

            case SignToken:
                token.storage.sign = sign; //copyChar(sign);
//                std::cout << token.tokenType << " " << token.storage.sign << std::endl;
                //this->clearSign();
                break;

            case IfToken:
//                std::cout << token.tokenType << std::endl;
                break;

            case WhileToken:
//                std::cout << token.tokenType << std::endl;
                break;

        }

//        if (tokenType != IdentifierToken) {
//            token.storage.lexem = new char[1];
//            token.storage.lexem[0] = '\0';
//        }
//        if (tokenType != SignToken) {
//            token.storage.sign = new char[1];
//            token.storage.sign[0] = '\0';
//        }
        return token;
    }

    void Automat::prepareTokenError() {
        tokenQueue.addSymbolAsLast('3'); //Errortoken
        //tokenReady = ErrorToken;
        //return Automat::createToken(ErrorToken);
    }

    //TO FIX return value and token creation
    void Automat::prepareTokenDigit() {

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
        tokenQueue.addSymbolAsLast('1'); //Digittoken
        //tokenReady = DigitToken;
        //return createToken(DigitToken);

}
    //Fix return and test


    void Automat::prepareTokenSign() {

        int amount = listAutomat.listLength();
        char *string = new char[amount + 1];

        for (int i = amount; i >= 0; i--) {
            char symbol = listAutomat.popSymbol();
            if (symbol == ' ' && i == 0) {
                string++;
            }
            else {
                string[i] = symbol;
            }
        }
        string[amount] = '\0';
        sign = string;
        delete []string;

        tokenQueue.addSymbolAsLast('0'); //Signtoken
        //tokenReady = SignToken;
        //return createToken(SignToken);
    }


    //To fix set length of lexem
    void Automat::prepareTokenLetter() {

        if (listAutomat.listLength() == 2) {

            char toTest[2];
            char arIf[2] = {'i', 'f'};
            char arIf2[2] = {'I', 'F'};

            toTest[1] = listAutomat.popSymbol();
            toTest[0] = listAutomat.popSymbol();

            if (Automat::isArrayEqual(arIf, toTest, 2) || Automat::isArrayEqual(arIf2, toTest, 2)) {

                tokenQueue.addSymbolAsLast('4'); //Iftoken
                return;
                //tokenReady = IfToken;
                //return createToken(IfToken);
            }
                listAutomat.addSymbol(toTest[0]);
                listAutomat.addSymbol(toTest[1]);
        }

        else if (listAutomat.listLength() == 5) {

            char toTest[5];
            char arIf[5] = {'w', 'h', 'i', 'l', 'e'};
            char arIf2[5] = {'W', 'H', 'I', 'L', 'E'};

            toTest[4] = listAutomat.popSymbol();
            toTest[3] = listAutomat.popSymbol();
            toTest[2] = listAutomat.popSymbol();
            toTest[1] = listAutomat.popSymbol();
            toTest[0] = listAutomat.popSymbol();

            if (Automat::isArrayEqual(arIf, toTest, 5) || Automat::isArrayEqual(arIf2, toTest, 5)) {

                tokenQueue.addSymbol('5'); //Whiletoken
                return;
                //tokenReady = WhileToken;
                //return createToken(WhileToken);
            }
            listAutomat.addSymbol(toTest[0]);
            listAutomat.addSymbol(toTest[1]);
            listAutomat.addSymbol(toTest[2]);
            listAutomat.addSymbol(toTest[3]);
            listAutomat.addSymbol(toTest[4]);
        }


        int amount = listAutomat.listLength();
        char *string = new char[amount + 1];

        for (int i = amount; i >= 0; i--) {
            //token.lexem[i-1] = listAutomat.popSymbol();
            char symbol = listAutomat.popSymbol();
            if (symbol == ' ' && i == 0) {
                string++;
            }
            else {
                string[i] = symbol;
            }
        }
        string[amount] = '\0';
        identifier = string;
        delete []string;
        tokenQueue.addSymbolAsLast('2'); //Identifiertoken
        //this->tokenReady = IdentifierToken;

    }


    /** Hilfsfunktionen **/


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

    //DOS&Windows: \r\n <=> Linux: \n <=> Mac: \r
    bool Automat::isNewLine(char c) {
        if (c == '\r') {
            precedingCR = true;
            return true;
        }
        else if (c == '\n') {
            precedingCR = false;
            return true;
        }
        return false;
        //return c == '\r' || c == '\n';
    }


    bool Automat::isSignColon(char c) {

        return c == ':';

    }


    bool Automat::isSignEqual(char c) {

        return c == '=';

    }


    bool Automat::isLetter(char c) {

        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
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
        unsigned int returnValue = startColumn;
        if (useBufferedStartColumn) {
            useBufferedStartColumn = false;
            startColumn = bufferedStartColumn;
        }
        return returnValue;

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


    void Automat::clearIdentifier() {
        int i = 0;
        while (identifier[i] != '\0') {
            identifier[i] = '\0';
            i++;
        }

    }

    void Automat::clearSign() {
        int i = 0;
        while (sign[i] != '\0') {
            sign[i] = '\0';
            i++;
        }

    }

    char* Automat::copyChar(const char *string) {
        int size = 0;
        while (string[size] != '\0') {
            size++;
        }
        char *copy = new char[size+1];
        for (int index = 0; index <= size; index++) {
            copy[index] = string[index];
        }
        return copy;
    }

    //Beendet den Automaten
    void Automat::endAutomat() {
        checkSymbol(' ');
    }
