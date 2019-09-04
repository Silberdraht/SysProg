#include "Scanner.h"
#include "AST/ASTBuild/ASTCreator.h"
#include <iostream>
using namespace std;


int testTwo() {
	Scanner scanner;
	scanner.initializeSymtable();
	scanner.startScanner();
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

int test() {
	Scanner scanner;
	scanner.initializeSymtable();
	scanner.startScanner();
	std::fstream stream;
	stream.open(R"(D:\\cppeclipse\\test\\out.txt)");
	//stream.open("F:\\\\Studium\\\\Compilerbau2019\\\\SysProg\\\\out.txt");
	//stream.open("C:\\\\Users\\\\Silberdraht\\\\Desktop\\\\beispieltest.txt");

	while (scanner.hasTokens()) {
		Automat::Token token = scanner.nextToken();
		Automat::TokenType type = token.tokenType;

		switch (type) {
		case Automat::IdentifierToken:
			stream << "Token Identifier" << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << "\t\t"
					<< "Contains: "
					<< scanner.symtable.lookup(token.storage.key).getLexem()
					<< '\n';
			break;

		case Automat::SignToken:
			stream << "Token Sign      " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << "\t\t"
					<< "Contains: "
					<< scanner.symtable.lookup(token.storage.key).getLexem()
					<< '\n';
			break;

		case Automat::DigitToken:
			stream << "Token Digit     " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << "\t\t"
					<< "Contains: " << token.storage.number << '\n'; // << additional;
			break;

		case Automat::ErrorToken:
			stream << "Token Error     " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << "\t\t"
					<< "Contains: " << token.storage.error << '\n';
			break;

		case Automat::IfToken:
			stream << "Token If        " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		case Automat::WhileToken:
			stream << "Token While     " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		case Automat::IntToken:
			stream << "Token int        " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		case Automat::ElseToken:
			stream << "Token Else       " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		case Automat::WriteToken:
			stream << "Token Write      " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		case Automat::ReadToken:
			stream << "Token Read       " << "\t\t" << "Line/Column: "
					<< token.line << "/" << token.column << '\n';
			break;

		default:
			break;
		}

	}

	stream.close();

	return 0;
}

int main() {
	return testTwo();
}




