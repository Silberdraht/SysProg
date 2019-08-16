/*
 * Information.cpp
 *
 *  Created on: 26.02.2019
 *      Author: Einem
 */


#include "information.h"

bool Information::compareLex(char* lexem2) {
	bool identicalCharacters = true;
	int index = 0;
	while (lexem[index] != '\0' || lexem2[index] != '\0') {
		if (lexem[index] != lexem2[index]) {
			identicalCharacters = false;
		}
		index++;
	}

	return (identicalCharacters & lexem[index] == '\0' & lexem2[index] == '\0');
}

char* Information::getLexem() {
	return this->lexem;
}

void Information::setLexem(char* lexem) {
	this->lexem = lexem;
}

