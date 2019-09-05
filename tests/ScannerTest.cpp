//
// Created by noahp on 04/09/2019.
//

#include "ScannerTest.h"

ScannerTest::ScannerTest(Scanner scanner) : scanner{scanner} {
    outputTokensToFile();
}

void ScannerTest::outputTokensToFile() {

    std::fstream stream;
    stream.open(R"(../out.txt)");
    //stream.open("F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\out.txt");
    //stream.open("C:\\\\Users\\\\Silberdraht\\\\Desktop\\\\beispieltest.txt");

    while (scanner.hasTokens()) {
        Token token = scanner.nextToken();
        TokenType type = token.tokenType;

        switch (type) {
            case IdentifierToken:
                stream << "Token Identifier" << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << scanner.symtable.lookup(token.storage.key).getLexem() << '\n';
                break;

            case SignToken:
                stream << "Token Sign      " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << scanner.symtable.lookup(token.storage.key).getLexem() << '\n';
                break;

            case DigitToken:
                stream << "Token Digit     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << token.storage.number << '\n'; // << additional;
                break;

            case ErrorToken:
                stream << "Token Error     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << "\t\t"
                       << "Contains: " << token.storage.error << '\n';
                break;

            case IfToken:
                stream << "Token If        " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            case WhileToken:
                stream << "Token While     " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            case IntToken:
                stream << "Token int        " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            case ElseToken:
                stream << "Token Else       " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            case WriteToken:
                stream << "Token Write      " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            case ReadToken:
                stream << "Token Read       " << "\t\t"
                       << "Line/Column: " << token.line << "/" << token.column << '\n';
                break;

            default:
                break;
        }

    }

    stream.close();
}
