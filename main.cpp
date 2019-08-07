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

    while (scanner.hasTokens()) {
        Automat::Token token = scanner.nextToken();
        Automat::TokenType type = token.tokenType;

        switch (type) {
            case Automat::IdentifierToken:
                stream << "Token Identifier" << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << scanner.symtable.lookup(token.storage.key).getLexem() << '\n';
                break;

            case Automat::SignToken:
                stream << "Token Sign      " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << scanner.symtable.lookup(token.storage.key).getLexem() << '\n';
                break;

            case Automat::DigitToken:
                stream << "Token Digit     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << token.storage.number << '\n'; // << additional;
                break;

            case Automat::ErrorToken:
                stream << "Token Error     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << token.storage.error << '\n';
                break;

            case Automat::IfToken:
                stream << "Token If        " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column <<  '\n';
                break;

            case Automat::WhileToken:
                stream << "Token While     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column <<  '\n';
                break;


            default: break;
        }

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