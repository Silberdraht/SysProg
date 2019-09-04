#include "Scanner.h"
#include "AST/ASTBuild/ASTCreator.h"
#include <iostream>
using namespace std;
#include "tests/ScannerTest.h"


int testTwo(Scanner scanner) {
	cout << "scanner finished" << endl;
	ASTCreator creator;
	creator.setScanner(scanner);
	while (scanner.hasTokens()) {
		Automat::Token token = scanner.nextToken();
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
	return 0;
}


int main() {
    Scanner scanner;
	scanner.initializeSymtable();
	scanner.startScanner();

    //Output to check correctness of generated tokens
    //ScannerTest test(scanner);

    return testTwo(scanner);
}




