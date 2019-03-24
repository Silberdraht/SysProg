/*
 * StringTable.h
 *
 *  Created on: 25.02.2019
 *      Author: Einem
 */

#ifndef STRINGTABLE_H_
#define STRINGTABLE_H_





#endif /* STRINGTABLE_H_ */

class StringTable{
	char* freeP;
	int freeSpace;
	int size = 64*4;
	char* table; //set to size
	void resize();
public:
	StringTable();
	~StringTable();
	char* insert(char*lexem ,int size);
};
