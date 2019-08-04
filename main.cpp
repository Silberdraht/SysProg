#include "TestAutomat.h"
#include "Scanner.h"


int main() {

    //std::ofstream ofs {"out.txt",std::ios_base::binary};

    /*
    std::ofstream ofs {"out.txt",std::ios_base::binary};
    ofs << "Test lolz" << std::endl;
    ofs << "Test lolz2" << std::endl;
    ofs << "Test lolz3" << std::endl;
*/
    Scanner scanner;
    scanner.startScanner();

    std::fstream stream;
    stream.open("D:\\\\cppeclipse\\\\test\\\\src\\\\out.txt");
    //stream.open("F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\out.txt");
    //stream.open("C:\\\\Users\\\\Silberdraht\\\\Desktop\\\\beispieltest.txt");

    while (scanner.hasTokens()) {
        Automat::Token token = scanner.nextToken();

        Automat::TokenType type = token.tokenType;
        char *tokentype;
        char *additional = nullptr;
        char *additionalHead = nullptr;
        switch (type) {
            case Automat::IdentifierToken:
                tokentype = (char *) "Identifier";
                additionalHead = (char *) "Lexem: ";
                //additional = scanner.symtable.lookup(token.storage.key).getLexem(); //TODO fix segmentation fault
                break;
            case Automat::SignToken:
                tokentype = (char *) "Sign      ";
                additionalHead = (char*) "Operator: ";
                additional = token.storage.sign;
                break;
            case Automat::DigitToken:
                tokentype = (char *) "Digit     ";
                additionalHead = (char *) "Value: ";
                additional = (char *) token.storage.number;
                break;
            case Automat::ErrorToken:
                tokentype = (char *) "Error     ";
                additionalHead = (char *) "String: ";
                //additional = token.storage.error; //TODO
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
        if (additional != nullptr) {
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
