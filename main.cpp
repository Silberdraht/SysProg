#include "Scanner.h"
#include "AST/ASTBuild/ASTCreator.h"
#include <iostream>
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

    CodeBuilder builder;
    builder.makeCode(creator);

	return 0;
}


int main() {


    std::string input{};
    cout << "Please enter a valid sentence (with spaces):\n>" << std::endl;
    getline(cin, input);


    Scanner scanner;
	scanner.initializeSymtable();
	scanner.startScanner();

    //Output to check correctness of generated tokens
    ScannerTest test(scanner);

    testTwo(scanner);
    return 0;
}




