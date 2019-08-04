/*
 * ASTCreator.cpp
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#include "ASTCreator.h"

ASTCreator::ASTCreator() {
	// TODO Auto-generated constructor stub

}

ASTCreator::~ASTCreator() {
	// TODO Auto-generated destructor stub
}

int ASTCreator::computeToken(Automat::Token token) {
	switch (getTokenType()) {
	case PROG:
		buildPROG();
		break;
	case DECLS:
		buildDECLS();
		break;
	case DECL:
		buildDECL();
		break;
	case ARRAY:
		buildARRAY();
		break;
	case STATEMENTS:
		buildSTATEMENTS();
		break;
	case STATEMENT:
		buildSTATEMENT();
		break;
	case EXP:
		buildEXP();
		break;
	case EXP2:
		buildEXP2();
		break;
	case INDEX:
		buildINDEX();
		break;
	case OP_EXP:
		buildOP_EXP();
		break;
	case OP:
		buildOP();
		break;
	}
}

void ASTCreator::buildPROG() {
	stack.addNewSign(DECLS);
	stack.addNewSign(STATEMENTS);
}
void ASTCreator::buildDECLS() {
	//Teste, ob zeichen leer sind
	if () {

	} else {
		stack.addNewSign(DECL);
		// teste, ob ein ";" hier vorhanden ist!
		stack.addNewSign(DECLS);
	}
}
void ASTCreator::buildDECL() {

	// zeichen zum baum hinzufügen
}
void ASTCreator::buildARRAY() {
	if () {
		// build array
	} else {

	}

}
void ASTCreator::buildSTATEMENTS() {
	//Teste, ob zeichen leer sind
	if () {

	} else {
		stack.addNewSign(STATEMENT);
		// teste, ob ein ";" hier vorhanden ist!
		stack.addNewSign(STATEMENTS);
	}

}
void ASTCreator::buildSTATEMENT() {
	// hier unterscheiden, wass passiert!
	identifierINDEX :=EXP
	write(EXP )
	read(identifierINDEX)
	{	STATEMENTS}
	if(EXP)STATEMENTelseSTATEMENT
	while(EXP)STATEMENT
}
void ASTCreator::buildEXP() {
	stack.addNewSign(EXP2);
	stack.addNewSign(OP_EXP);
}
void ASTCreator::buildEXP2() {
	if() {
		(EXP)
	} else if() {
	identifier	INDEX
	} else if() {
			integer
	} else if() {
			-EXP2
	} else if() {
			!EXP2
	}
	// wenns hier unten ankonnt is was schief gegangen!
}
void ASTCreator::buildINDEX() {
	if() {
		// check for []

	}
}
void ASTCreator::buildOP_EXP() {
	if() {
		stack.addNewSign(OP);
		stack.addNewSign(EXP);
	}
}
void ASTCreator::buildOP() {
	// sign
}
