#include "TestAutomat.h"
#include "Scanner.h"


int main() {

    Scanner scanner;
    scanner.initializeSymtable();
    scanner.startScanner();
    std::fstream stream;
    stream.open(R"(../out.txt)");
    //stream.open("F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\out.txt");
    //stream.open("C:\\\\Users\\\\Silberdraht\\\\Desktop\\\\beispieltest.txt");
    bool hasAdditionalInformation;
    while (scanner.hasTokens()) {
        Automat::Token token = scanner.nextToken();

        Automat::TokenType type = token.tokenType;
        char *tokentype;
        char *additional = nullptr;
        char *additionalHead = nullptr;
        hasAdditionalInformation = false;
        switch (type) {
            case Automat::IdentifierToken:
                tokentype = (char *) "Identifier";
                additionalHead = (char *) "Lexem: ";
                additional = scanner.symtable.lookup(token.storage.key).getLexem(); //TODO fix segmentation fault
                hasAdditionalInformation = true;
                break;
            case Automat::SignToken:
                tokentype = (char *) "Sign      ";
                additionalHead = (char*) "Operator: ";
                //additional = scanner.symtable.lookup(token.storage.key).getLexem();
                //additional = token.storage.sign;
                //hasAdditionalInformation = true;
                break;
            case Automat::DigitToken:
                tokentype = (char *) "Digit     ";
                additionalHead = (char *) "Value: ";
                additional = (char *) token.storage.number;
                hasAdditionalInformation = true;
                break;
            case Automat::ErrorToken:
                tokentype = (char *) "Error     ";
                additionalHead = (char *) "String: ";
                //additional = token.storage.error; //TODO
                hasAdditionalInformation = true;
                break;
            case Automat::IfToken:
                tokentype = (char *) "If        ";
                break;
            case Automat::WhileToken:
                tokentype = (char *) "While     ";
                break;
            default: "NOT FOUND";
        }

        stream << "Token " << tokentype << "\t\t";
        stream << "Line: " << token.line << " Column: " << token.column << "\t\t";
        if (hasAdditionalInformation) {
            //stream << additionalHead << additional;
        }
        stream <<  '\n';
    }

    stream.close();

    return 0;


//    enum TokenType {
//        SignToken = 0,
//        DigitToken = 1,
//        IdentifierToken = 2,
//        ErrorToken = 3,
//        IfToken = 4,
//        WhileToken = 5
//    };
}