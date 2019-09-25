#include "Scanner/Scanner.h"
#include "parser/AST/ASTBuild/ASTCreator.h"
#include <iostream>
#include <chrono>
#include "tests/ScannerTest.h"
#include "parser/CodeBuilder.h"

using namespace std;

int main(int argc, char* argv[]) {

    char* file;
    if (argc > 1) {
        file = argv[1];
    } else {
        file = (char *) R"(../input_code.txt)";
    }
    auto starttime = chrono::steady_clock::now();
    Scanner scanner = Scanner(Buffer(file));
	scanner.startScanner();

    //Output to check correctness of generated tokens
    ScannerTest test(scanner);

    if (!scanner.isWithoutErrors()) {
        return 1;
    } else {
        cout << "Scanner completed without error" << endl;
    }

    ASTCreator creator = ASTCreator(scanner);
    creator.buildTree();

    CodeBuilder builder(creator, scanner.symtable);
    builder.makeCode();

    auto endtime = chrono::steady_clock::now();
    std::cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(endtime - starttime).count() << std::endl;
    std::cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(endtime - starttime).count() << std::endl;

    return 0;
}




