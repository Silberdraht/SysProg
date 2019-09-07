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

//int Symtable::calculateKey(char* lexem) {
//	int size = 0;
//	int result = 0;
//	while(*(lexem + size)) {
//		result ^= (*(lexem + size)) * size;
//		size++;
//	}
//	result = result % this->prime;
//	return result;
//}

Key Symtable::insert(char* lexem)
{
	Key key;
	int size = 0;
	int result = 0;
	while(*(lexem + size)) {
		result ^= (*(lexem + size)) * (size+1);
		size++;
	}
	if(size > 0) {
		char* entry = table.insert(lexem,size);
		Information infoToAdd;
        infoToAdd.setLexem(entry);
        result = result % this->prime;
        key.key = result;
        Listptrs[result].push_back(infoToAdd);
        key.KeyNr =  Listptrs[result].size();
        return key;
	} else {
		return key;
	}

}

Information Symtable::lookup(Key key){
	auto info = Listptrs[key.key].at(key.KeyNr);
	return info;
}
