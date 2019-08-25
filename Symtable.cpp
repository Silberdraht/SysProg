/*
 * Symtable.cpp
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#include "Symtable.h"
	Symtable::Symtable() {

	    }
	Symtable::~Symtable() {

	    }

int Symtable::calculateKey(char* lexem) {
	int size = 0;
	int result = 0;
	while(*(lexem + size)) {
		result ^= (*(lexem + size)) * size;
		size++;
	}
	result = result % this->prime;
	return result;
}

Key Symtable::insert(char* lexem)
{
	Key key;
	int size = 0;
	int result = 0;
	while(*(lexem + size)) {
		result ^= (*(lexem + size)) * size;
		size++;
	}
	if(size > 0) {
		char* entry = table.insert(lexem,size);
		Information infoToAdd;
			infoToAdd.setLexem(entry);
			//int keyInt = calculateKey(entry);
			result = result % this->prime;
			key.key = result;
			key.KeyNr = Listptrs[result].addInfo(infoToAdd);
			return key;
	} else {
		return key;
	}

}

Information Symtable::lookup(Key key){
	Information info;
	info = Listptrs[key.key].getInfo(key.KeyNr);
	return info;
}
