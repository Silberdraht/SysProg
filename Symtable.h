/*
 * Symtable.h
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_


#include "StringTable.h"
#include "lib/Link_List.h"
#include "Information.h"

struct Key{
	int key;
	int KeyNr;
};

class Symtable {


	//997
	int prime = 97;
	StringTable table;
	Link_List<Information> Listptrs[97];
	int calculateKey(char* lexem);

public:

	Symtable();
	~Symtable();
	Key insert(char* lexem);
	Information lookup(Key key);
	bool hasLexem(char* lexem);

};


#endif /* SYMTABLE_H_ */
