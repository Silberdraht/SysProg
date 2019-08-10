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
	switch (getTokenType(token)) {
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

NodeType ASTCreator getTokenType(Automat::Token token){

};

void ASTCreator::buildPROG() {
	head = new ASTNode(PROG);
	stack.addNewSign(DECLS);
	ASTNode newDecls = new ASTNode(DECLS);
	head.addChild(newDecls);
	stack.addNewSign(STATEMENTS);
	ASTNode newDecls = new ASTNode(DECLS);
	head.addChild(newDecls);
}
void ASTCreator::buildDECLS() {
	//Teste, ob zeichen leer sind
	if () {
		// epsylon
	} else {
		ASTNode newDecl = new ASTNode(DECL);
		head.addChild(newDecl);
		stack.addNewSign(DECL);
		ASTNode newNode = new ASTNode(COLONSIGN);
		head.addChild(newNode);

		stack.addNewSign(DECLS);
		ASTNode newDecls = new ASTNode(DECLS);
		head.addChild(newDecls);
	}
}
void ASTCreator::buildDECL() {

	ASTNode newInt = new ASTNode(INTSIGN);
	head.addChild(newInt);
	// teste, ob ein ";" hier vorhanden ist!
	ASTNode newNode = new ASTNode(ARRAY);
	head.addChild(newNode);

	ASTNode newId = new ASTNode(IDENTIFIER);
	head.addChild(newId);
}
void ASTCreator::buildARRAY() {
	if () {
		ASTNode open = new ASTNode(EKL_OPEN);
		head.addChild(open);

		ASTNode newInt = new ASTNode(INTEGER);
		head.addChild(newInt);

		ASTNode close = new ASTNode(EKL_CLOSE);
		head.addChild(close);
	} else {
		//elypson
	}

}
void ASTCreator::buildSTATEMENTS() {
	//Teste, ob zeichen leer sind
	if () {

	} else {
		stack.addNewSign(STATEMENT);
		ASTNode open = new ASTNode(STATEMENT);
		head.addChild(open);

		ASTNode newNode = new ASTNode(COLONSIGN);
		head.addChild(newNode);

		stack.addNewSign(STATEMENTS);
		ASTNode open = new ASTNode(STATEMENTS);
		head.addChild(open);
	}

}
void ASTCreator::buildSTATEMENT() {
	// hier unterscheiden, wass passiert!
	if () {
		ASTNode newNode = new ASTNode(IDENTIFIER);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(INDEX);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(OTHEREQUALSSIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(WRITESIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_OPEN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_CLOSE);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(READSIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_OPEN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(IDENTIFIER);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(INDEX);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_CLOSE);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(GKL_OPEN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(STATEMENTS);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(GKL_CLOSE);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(IFSIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_OPEN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_CLOSE);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(STATEMENT);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(ELSESIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(STATEMENT);
		head.addChild(newNode);
	}
}
void ASTCreator::buildEXP() {
	stack.addNewSign(EXP2);
	ASTNode newEXP = new ASTNode(EXP2);
	head.addChild(newEXP);
	stack.addNewSign(OP_EXP);
	ASTNode newOp = new ASTNode(OP_EXP);
	head.addChild(newOp);
}
void ASTCreator::buildEXP2() {
	if () {
		ASTNode newNode = new ASTNode(KL_OPEN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(KL_CLOSE);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(IDENTIFIER);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(INDEX);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(INTEGER);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(MINUSSIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP2);
		head.addChild(newNode);
	} else if () {
		ASTNode newNode = new ASTNode(EXCLSIGN);
		head.addChild(newNode);
		ASTNode newNode = new ASTNode(EXP2);
		head.addChild(newNode);
	}
	// wenns hier unten ankonnt is was schief gegangen!
}
void ASTCreator::buildINDEX() {
	if () {
		ASTNode open = new ASTNode(EKL_OPEN);
		head.addChild(open);

		ASTNode newInt = new ASTNode(EXP);
		head.addChild(newInt);

		ASTNode close = new ASTNode(EKL_CLOSE);
		head.addChild(close);

	}
}
void ASTCreator::buildOP_EXP() {
	if () {
		stack.addNewSign(OP);
		ASTNode newOp = new ASTNode(OP);
				head.addChild(newOp);
		stack.addNewSign(EXP);
		ASTNode newInt = new ASTNode(EXP);
				head.addChild(newInt);
	}
}
void ASTCreator::buildOP() {
	//TODO add different signs
	sitch(int)
					case:
					case:
					case:
					case:
					case:
					case:
					case:
					case:
					case:
					case default:
}
