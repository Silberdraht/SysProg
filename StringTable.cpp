/*
 * StringTable.cpp
 *
 *  Created on: 25.02.2019
 *      Author: Konstantin Krause
 */

#include "StringTable.h"

    StringTable::StringTable() {
//    	size = 64*4;
    	table = new char[size];
    	freeP = table;
    	freeSpace = size;
    }
    StringTable::~StringTable() {
    	delete table;
    }

void memcpy(char* dest,char* lexem, int size) {
	int i;
	for (i = 0;i < size; i++) {
		*(dest + i) = *lexem + i;
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

char* StringTable::insert(char* lexem, int size)
{
	char* tmp = this->freeP;
	if (size < this->freeSpace)
	{
		memcpy(this->freeP,lexem,size+1);
		this->freeP[size] = '\0';
		this->freeP += size+1;
		this->freeSpace -= size+1;
	} else
	{
		resize();
	}
	return tmp;
}


