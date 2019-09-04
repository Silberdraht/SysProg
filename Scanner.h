//
// Created by noahp on 14/04/2019.
//

#ifndef SYSPROG_SCANNER_H
#define SYSPROG_SCANNER_H

#include "Buffer.h"
#include "Automat.h"
#include "Symtable.h"
#include "TokenList.h"
#include "lib/Link_List.h"


class Scanner {

private:
    Buffer buffer;
    Automat automat;
    Token createToken();
    Link_List<Token> tokens;

public:
	Key plus;
	Key minus;
	Key equals;
	Key star;
	Key greater;
	Key lesser;
	Key sAnd;
	Key semicolon;
	Key exclamationMark;
	Key bracketOpen;
	Key bracketClose;
	Key curlyBracketOpen;
	Key curlyBracketClose;
	Key squareBracketOpen;
	Key squareBracketClose;
	Key colonEquals;
	Key colon;
	Key equalsColonEquals;
	Key andAnd;
	Scanner();
	~Scanner();

	Symtable symtable;
	void initializeSymtable();

	void startScanner();
	Automat::Token nextToken();
	int hasTokens();

};

#endif //SYSPROG_SCANNER_H
