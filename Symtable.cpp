/*
 * Symtable.cpp
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#include "Symtable.h"
	Symtable::Symtable() = default;
	Symtable::~Symtable() = default;

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
    Key alreadyExists = lookupLexem(lexem);
    if (alreadyExists.key != -1 && alreadyExists.KeyNr != -1) {
        return alreadyExists;
    }
	int size = 0;
	int result = 0;
	while(*(lexem + size)) {
		result ^= (*(lexem + size)) * (size+1);
		size++;
	}
	if(size > 0) {
		char* entry = table.insert(lexem,size);
		Information infoToAdd{};
        infoToAdd.setLexem(entry);
        result = result % this->prime;
        usedKeys.push_back(result); //for lookup -> runtimeoptimization
        Listptrs[result].push_back(infoToAdd);
        return Key{result, Listptrs[result].size()};
	} else {
		return Key{-1,-1}; //empty lexem
	}

}

Information Symtable::lookup(Key key){
	auto info = Listptrs[key.key].at(key.KeyNr);
	return info;
}

Key Symtable::lookupLexem(char *lexem) {

    auto keyElem =  usedKeys.getFirst();
    for (int index=1; index <= usedKeys.size(); index++) {
        int key = keyElem->getContent();
        auto element = Listptrs[key].getFirst();
        int size = Listptrs[key].size();
        for (int keyNr=1; keyNr <= size; keyNr++) {
            if (compare(element->getContent().getLexem(), lexem)) {
                return Key{key,keyNr};
            } else {
                element = element->getSuccessor();
                keyNr++;
            }
        }
        keyElem = keyElem->getSuccessor();
    }
    return Key{-1,-1};
}

bool Symtable::compare(const char *lex1, const char *lex2) {
    int index = 0;
    while (lex1[index] != '\0' && lex2[index] != '\0') {
        if (lex1[index] != lex2[index]) {
            return false;
        }
        index++;
    }
    return (lex1[index] == '\0' && lex2[index] == '\0');
}
