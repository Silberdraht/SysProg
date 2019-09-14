    //
    // Created by Silberdraht on 09.10.2018.
    //


#include <tgmath.h>
#include "Automat.h"


    void Automat::checkSymbol(char c) {

        switch (stateActive) {
            case init:
                if (isDigit(c)) {
                    precedingCR = false; //Carriage Return not followed by a \n;
                    currentColumn++;
                    stateActive = digitstate;
                    listAutomat.push_front(c);

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
                    listAutomat.push_front(c);
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
                    listAutomat.push_front(c);
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
                    listAutomat.push_front(c);
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
                    listAutomat.push_front(c);
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
                    listAutomat.push_front(c);
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
                else if (isEOF(c)) {
                    break;
                }

                else if (isInvalidCharacter(c)) {
                    precedingCR = false;
                    currentColumn++;
                    if (useBufferedStartColumn) {
                        bufferedStartColumn = currentColumn;
                    } else {
                        startColumn = currentColumn;
                    }
                    startLine = currentLine;

                    listAutomat.push_front(c);
                    prepareTokenError();
                }
                break;


            case digitstate:
                //std::cout << "digit: " << std::endl;
                if (isDigit(c)) {
                    listAutomat.push_front(c);
                        currentColumn++;

                } else {
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
                    listAutomat.push_front(c);
                }
//                else if (isInvalidCharacter(c)) {
//                    currentColumn++;
//                    listAutomat.push_front(c);
//                    stateActive = errorstate;
//                }
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
                    listAutomat.push_front(c);
                    prepareTokenSign();
                    stateActive = init;
                } else{
                    listAutomat.push_front(c);
                    currentColumn++;
                    stateActive = errorstate;
                }

                break;


            case equalstate:
                if (isSignColon(c)) {
                    currentColumn++;
                    listAutomat.push_front(c);
                    stateActive = equalcolonstate;
                } else {
                    prepareTokenSign();
                    stateActive = init;
                    useBufferedStartColumn = true;
                    checkSymbol(c);
                }
                break;


            case colonstate:
                if (isSignEqual(c)) {
                    currentColumn++;
                    listAutomat.push_front(c);
                    prepareTokenSign();
                    stateActive = init;
                }
                else if (isStar(c)) {
                    currentColumn++;
                    listAutomat.pop_front();
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
                    listAutomat.push_front(c);
                    prepareTokenSign();
                    stateActive = init;
                } else {
                    //Erzeugt ein Token '=' und ein Token ':'
                    char temp = listAutomat.pop_front();
                    prepareTokenSign();
                    useBufferedSign = true;
                    listAutomat.push_front(temp);
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

            case errorstate:
                if (isNewLine(c) || isBlank(c)) {
                    prepareTokenError();
                    stateActive = init;
                    checkSymbol(c);
                } else {
                    currentColumn++;
                    listAutomat.push_front(c);
                }
        }
    }


    Token Automat::createToken(TokenType tokenType) {

        Token token{};
        token.line = getStartLine();
        token.column = getStartColumn();
        token.tokenType = tokenType;

        switch (tokenType) {
            case IdentifierToken:
                //token.storage.lexem = copyChar(identifier);
                //this->clearIdentifier();
                break;

            case DigitToken:
                token.storage.number = this->number;
                break;

            case ErrorToken:
                token.storage.error = copyChar(error);
                break;

            case SignToken:
//                token.storage.sign = sign;
//                if (useBufferedSign) {
//                    sign = bufferedSign;
//                    useBufferedSign = false;
//                }
                //token.storage.sign = temp; //copyChar(sign);
                //this->clearSign();
                break;

            default:
                break;
        }

        return token;
    }


    void Automat::prepareTokenError() {
        int amount = listAutomat.size();
        char *string = new char[amount + 1];

        for (int i = amount; i >= 0; i--) {
            //token.lexem[i-1] = listAutomat.pop_front();
            char symbol = listAutomat.pop_front();
            if (symbol == ' ' && i == 0) {
                string++;
            }
            else {
                string[i] = symbol;
            }
        }
        string[amount] = '\0';
        error = string;
        tokenQueue.push_back('3'); //Errortoken
    }


    void Automat::prepareTokenDigit() {

        int power = 1;
        int value = 0;
        bool overflow = false;
        while (!listAutomat.empty()) {
            value += power*convertCharToInt(listAutomat.pop_front());
            if (value < 0) {
                overflow = true;
                break;
            }
            power*=10;
        }
        if (!overflow) {
            this->number = value;
            tokenQueue.push_back('1'); //Digittoken
        } else {
            this->error = (char*)"Integer overflow";
            tokenQueue.push_back('3'); //Errortoken
        }
    }


    void Automat::prepareTokenSign() {

        int amount = listAutomat.size();
        char *string = new char[amount + 1];

        for (int i = amount; i >= 0; i--) {
            char symbol = listAutomat.pop_front();
            if (symbol == ' ' && i == 0) {
                string++;
            } else {
                string[i] = symbol;
            }
        }
        string[amount] = '\0';
        if (useBufferedSign) {
            bufferedSign = string;
        } else {
            sign = string;
        }
       // delete []string;

        tokenQueue.push_back('0'); //Signtoken
    }



    void Automat::prepareTokenLetter() {

        if (listAutomat.size() == 2) {

            char toTest[2];
            char arIf[2] = {'i', 'f'};
            char arIf2[2] = {'I', 'F'};

            toTest[1] = listAutomat.pop_front();
            toTest[0] = listAutomat.pop_front();

            if (Automat::isArrayEqual(arIf, toTest, 2) || Automat::isArrayEqual(arIf2, toTest, 2)) {

                tokenQueue.push_back('4'); //Iftoken
                return;
            }
            listAutomat.push_front(toTest[0]);
            listAutomat.push_front(toTest[1]);
        }

        else if (listAutomat.size() == 3) {

            char toTest[3];
            char arInt[3] = {'i', 'n', 't'};

            toTest[2] = listAutomat.pop_front();
            toTest[1] = listAutomat.pop_front();
            toTest[0] = listAutomat.pop_front();

            if (Automat::isArrayEqual(arInt, toTest, 3)) {

                tokenQueue.push_back('7'); //int token
                return;
            }
            listAutomat.push_front(toTest[0]);
            listAutomat.push_front(toTest[1]);
            listAutomat.push_front(toTest[2]);
        }

        else if (listAutomat.size() == 4) {

            char toTest[4];
            char arElse[4] = {'e', 'l', 's', 'e'};
            char arElse2[4] = {'E', 'L', 'S', 'E'};
            char arRead[4] = {'r', 'e', 'a', 'd'};

            toTest[3] = listAutomat.pop_front();
            toTest[2] = listAutomat.pop_front();
            toTest[1] = listAutomat.pop_front();
            toTest[0] = listAutomat.pop_front();

            if (Automat::isArrayEqual(arElse, toTest, 4) || Automat::isArrayEqual(arElse2, toTest, 4)) {

                tokenQueue.push_front('6'); //Else Token
                return;
            }
            else if (Automat::isArrayEqual(arRead, toTest, 4)) {
                tokenQueue.push_front('8'); //Read Token
                return;
            }
            listAutomat.push_front(toTest[0]);
            listAutomat.push_front(toTest[1]);
            listAutomat.push_front(toTest[2]);
            listAutomat.push_front(toTest[3]);
        }

        else if (listAutomat.size() == 5) {

            char toTest[5];
            char arIf[5] = {'w', 'h', 'i', 'l', 'e'};
            char arIf2[5] = {'W', 'H', 'I', 'L', 'E'};
            char arWrite[5] = {'w', 'r', 'i', 't', 'e'};

            toTest[4] = listAutomat.pop_front();
            toTest[3] = listAutomat.pop_front();
            toTest[2] = listAutomat.pop_front();
            toTest[1] = listAutomat.pop_front();
            toTest[0] = listAutomat.pop_front();

            if (Automat::isArrayEqual(arIf, toTest, 5) || Automat::isArrayEqual(arIf2, toTest, 5)) {

                tokenQueue.push_front('5'); //Whiletoken
                return;
            }
            else if (Automat::isArrayEqual(arWrite, toTest, 5)) {
                tokenQueue.push_front('9'); //Write Token
                return;
            }

            listAutomat.push_front(toTest[0]);
            listAutomat.push_front(toTest[1]);
            listAutomat.push_front(toTest[2]);
            listAutomat.push_front(toTest[3]);
            listAutomat.push_front(toTest[4]);
        }


        int amount = listAutomat.size();
        char *string = new char[amount + 1];

        for (int i = amount; i >= 0; i--) {
            //token.lexem[i-1] = listAutomat.pop_front();
            char symbol = listAutomat.pop_front();
            if (symbol == ' ' && i == 0) {
                string++;
            }
            else {
                string[i] = symbol;
            }
        }
        string[amount] = '\0';
        identifier = string;
        //delete []string;
        tokenQueue.push_back('2'); //Identifiertoken
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
        return c == ' ' || c == '\t'; // ||c != '\000';
    }


    bool Automat::isNewLine(char c) {
        if (c == '\r') {
            precedingCR = true;  //DOS&Windows: \r\n <=> Linux: \n <=> Mac: \r
            return true;
        }
        else if (c == '\n') {
            precedingCR = false;
            return true;
        }
        return false;
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


    bool Automat::isInvalidCharacter(char c) {
        return (!isStar(c) && (!isNewLine(c)) && (!isBlank(c)) && (!isLetter(c)) && (!isDigit(c))
                && (!isSignColon(c)) && (!isSignAnd(c)) && (!isSignEqual(c)) && (!isSign(c))); //&& c != '\000'
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
            default:
                return 0;
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
            i++;
        }
        for (int j=i-1;j>=0;j--) {
            identifier[j] = '\0';
        }
    }

    char* Automat::getIdentifer() {
        return copyChar(identifier);
    }


    void Automat::clearSign() {
        int i = 0;
        while (sign[i] != '\0') {
            i++;
        }
        for (int j=i-1;j>=0;j--) {
            sign[j] = '\0';
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

    bool Automat::isEOF(char c) {
        return c == '\000';
    }
