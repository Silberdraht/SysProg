#include "Scanner.h"
#include "AST/ASTBuild/ASTCreator.h"
#include <iostream>
#include <chrono>
#include "tests/ScannerTest.h"
#include "parser/CodeBuilder.h"

using namespace std;




int testTwo(Scanner scanner) {
	cout << "scanner finished" << endl;
	ASTCreator creator = ASTCreator(scanner);
	while (scanner.hasTokens()) {
        Token token = scanner.nextToken();
		cout <<"neues Token:";
		if(token.tokenType == 0| token.tokenType == 2) {
		cout <<"neues Token:" << scanner.symtable.lookup(token.storage.key).getLexem();
		}
		cout  <<endl;
		if(creator.computeToken(token)) {
			cout << "test failed" << endl;
		}
	}
	creator.finish();
	creator.hasError();

    CodeBuilder builder(creator, scanner.symtable);
    builder.makeCode();

	return 0;
}


int main() {

//
//    std::string input{};
//    cout << "Please enter a valid sentence (with spaces):\n>" << std::endl;
//    getline(cin, input);

    auto starttime = chrono::steady_clock::now();
    Scanner scanner;
	scanner.startScanner();

    //Output to check correctness of generated tokens
    ScannerTest test(scanner);
    if (!scanner.isWithoutErrors()) {
        return 1;
    }
    //testTwo(scanner);

    ASTCreator creator = ASTCreator(scanner);
    creator.buildTree();

    CodeBuilder builder(creator, scanner.symtable);
    builder.makeCode();

    auto endtime = chrono::steady_clock::now();
    std::cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(endtime - starttime).count() << std::endl;
    std::cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(endtime - starttime).count() << std::endl;

    return 0;
}




