/*
 * Symtable.h
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_



#include "InformationLinkedList.h"
#include "StringTable.h"


struct Key{
	int key;
	int KeyNr;
};

class Symtable {

	int prime = 997;
	StringTable table;
	InformationLinkedList Listptrs[997];
	int calculateKey(char* lexem);
public:
	Symtable();
	~Symtable();
	Key insert(char* lexem);
	Information lookup(Key key);
	bool hasLexem(char* lexem);

};


#endif /* SYMTABLE_H_ */