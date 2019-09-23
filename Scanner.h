//
// Created by noahp on 14/04/2019.
//

#ifndef SYSPROG_SCANNER_H
#define SYSPROG_SCANNER_H

#include "Buffer.h"
#include "Automat.h"
#include "Symtable.h"
#include "lib/Link_List.h"


class Scanner {

private:
    Buffer buffer;
    Automat automat;
    Token createToken();
    Link_List<Token> tokens;
    void initializeSymtable();
    bool withoutErrors = true;

public:
	Key plus = Key{};
	Key minus = Key{};
	Key equals = Key{};
	Key star = Key{};
	Key greater = Key{};
	Key lesser = Key{};
	Key sAnd = Key{};
	Key semicolon = Key{};
	Key exclamationMark = Key{};
	Key bracketOpen = Key{};
	Key bracketClose = Key{};
	Key curlyBracketOpen = Key{};
	Key curlyBracketClose = Key{};
	Key squareBracketOpen = Key{};
	Key squareBracketClose = Key{};
	Key colonEquals = Key{};
	Key colon = Key{};
	Key equalsColonEquals = Key{};
	Key andAnd = Key{};
	Scanner(Buffer buffer);
	~Scanner();

	Symtable symtable;

	void startScanner();
	Token nextToken();
	int hasTokens();
	bool isWithoutErrors();
};

#endif //SYSPROG_SCANNER_H
