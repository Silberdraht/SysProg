/*
 * StringTable.cpp
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#include "StringTable.h"

    StringTable::StringTable() {
    	table = new char[size];
    	freeP = table;
    	freeSpace = size;
    }
    StringTable::~StringTable() = default;

void memcpy(char* dest, char* lexeme, int size) {
	int i;
	for (i = 0;i < size; i++) {
		*(dest + i) = *(lexeme + i);
	}
}

void StringTable::resize() {
	int newSize = size*2;
	char* resized = new char[newSize];
	unsigned long i;
	for(i = 0;i<size-freeSpace;i++) {
		resized[i] = table[i];
	}
	freeSpace = freeSpace + size;
	size = newSize;
	freeP = resized +(freeP - table);
	table = resized;
}

char* StringTable::insert(char* lexeme, int lexemeSize)
{

	while (lexemeSize >= this->freeSpace)
	{
		resize();
	}
    char* tmp = this->freeP;
		memcpy(this->freeP,lexeme,lexemeSize+1);
				this->freeP[lexemeSize] = '\0';
				this->freeP += lexemeSize+1;
				this->freeSpace -= lexemeSize+1;
	return tmp;
}


