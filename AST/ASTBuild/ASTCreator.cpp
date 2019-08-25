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
	needsNewToken = 1;
	while (needsNewToken) {
		NodeType type = getTokenType(token);
		switch (type) {
		//Check non-terminals
		case PROG:
			stack.addNewLayer();
			buildPROG();
			break;
		case DECLS:
			stack.addNewLayer();
			buildDECLS(token);
			break;
		case DECL:
			stack.addNewLayer();
			buildDECL();
			break;
		case ARRAY:
			stack.addNewLayer();
			buildARRAY(token);
			break;
		case STATEMENTS:
			stack.addNewLayer();
			buildSTATEMENTS(token);
			break;
		case STATEMENT:
			stack.addNewLayer();
			buildSTATEMENT(token);
			break;
		case EXP:
			stack.addNewLayer();
			buildEXP();
			break;
		case EXP2:
			stack.addNewLayer();
			buildEXP2(token);
			break;
		case INDEX:
			stack.addNewLayer();
			buildINDEX(token);
			break;
		case OP_EXP:
			stack.addNewLayer();
			buildOP_EXP(token);
			break;
		case OP:
			stack.addNewLayer();
			buildOP();
			break;

			//TODO Terminale behandeln, die hier sind ALLE falsch, sind nur placeholder
			//man muss ein token einlesen und bestimmen, ob es dem Terminal entspricht
		case PLUSSIGN:	//+
			if(token.storage.lexem == "+") {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case MINUSSIGN:		//-
			if(token.storage.lexem == "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case STARSIGN:		//*
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case DOUBLESIGN:	//:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case LESSSIGN:		//<
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case GREATERSIGN:	//>
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case EQUALSSIGN:	//=
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case OTHEREQUALSSIGN:	//:=
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case EQUPEQUSIGN:	//=:=
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case ANDSIGN:	//&&
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case COLONSIGN:		//;
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case EXCLSIGN:		//!
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case IFSIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case ELSESIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case WHILESIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case READSIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case WRITESIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case INTSIGN:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case IDENTIFIER:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case INTEGER:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case KL_OPEN:	//(
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case KL_CLOSE:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case EKL_OPEN:	//[
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case EKL_CLOSE:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case GKL_OPEN:	//{
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		case GKL_CLOSE:
			if(token.storage.lexem = "+") {
							needsNewToken = 0;
							break;
						}
						error = 1;
						break;
		}

		//build new Nodes, set head if nessesairy
		//TODO: stack level überwachen!!!!!!!!!!!!
		ASTNode newNode = new ASTNode(type);
		head.addChild(newNode);
		if (stack.isTopLevelEmpty()) {
			while(stack.isTopLevelEmpty()) {
			stack.removeTopLayer();
			head = head.getParent();
			}
		} else {
			head = newNode;
		}
	}
}

NodeType ASTCreator::getTokenType(Automat::Token token) {
	return stack.pullFromTop();
}

void ASTCreator::buildPROG() {
	head = new ASTNode(PROG);
	buildNode(DECLS);
	buildNode(STATEMENTS);
}
void ASTCreator::buildDECLS(Automat::Token token) {
	//Teste, ob zeichen leer sind
	//TODO int einprogrammieren
	if (token.tokenType ==) {
		buildNode(DECL);
		buildNode(COLONSIGN);
		buildNode(DECLS);
	} else {
	}
}
void ASTCreator::buildDECL() {

	buildNode(INTSIGN);
	buildNode(ARRAY);
	buildNode(IDENTIFIER);
}
void ASTCreator::buildARRAY(Automat::Token token) {
	if (token.storage.lexem == "[") {
		buildNode(EKL_OPEN);
		buildNode(INTEGER);
		buildNode(EKL_CLOSE);
	} else {
		//elypson
	}

}
void ASTCreator::buildSTATEMENTS(Automat::Token token) {
	//Teste, ob zeichen leer sind
	//TODO wenn zeichenkette leer is tritt dieser Fall ein
	if (false) {

	} else {
		buildNode(STATEMENT);
		buildNode(COLONSIGN);
		buildNode(STATEMENTS);
	}

}
void ASTCreator::buildSTATEMENT(Automat::Token token) {
	// hier unterscheiden, wass passiert!
	if (token.tokenType == IdentifierToken) {
		buildNode(IDENTIFIER);
		buildNode(INDEX);
		buildNode(OTHEREQUALSSIGN);
		buildNode(EXP);
	} else if (token.tokenType ==) {
		buildNode(WRITESIGN);
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
	} else if (token.tokenType ==) {
		buildNode(READSIGN);
		buildNode(KL_OPEN);
		buildNode(IDENTIFIER);
		buildNode(INDEX);
		buildNode(KL_CLOSE);
	} else if (token.storage.lexem == "{") {
		buildNode(GKL_OPEN);
		buildNode(STATEMENTS);
		buildNode(GKL_CLOSE);
	} else if (token.tokenType == IfToken) {
		buildNode(IFSIGN);
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
		buildNode(STATEMENT);
		buildNode(ELSESIGN);
		buildNode(STATEMENT);
	}
}
void ASTCreator::buildEXP() {
	buildNode(EXP2);
	buildNode(OP_EXP);
}
void ASTCreator::buildEXP2(Automat::Token token) {
	if (token.storage.lexem == "(") {
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
	} else if (token.tokenType == IdentifierToken) {
		buildNode(IDENTIFIER);
		buildNode(INDEX);
	} else if (token.tokenType) {
		buildNode(INTEGER);
	} else if (token.storage.lexem == "-") {
		buildNode(MINUSSIGN);
		buildNode(EXP2);
	} else if (token.storage.lexem == "!") {
		buildNode(EXCLSIGN);
		buildNode(EXP2);
	}
	// wenns hier unten ankonnt is was schief gegangen!
}
void ASTCreator::buildINDEX(Automat::Token token) {
	if () {
		buildNode(EKL_OPEN);

		buildNode(EXP);

		buildNode(EKL_CLOSE);

	}
}
void ASTCreator::buildOP_EXP(Automat::Token token) {
	if () {
		buildNode(OP);
		buildNode(EXP);
	}
}
void ASTCreator::buildOP() {
	//TODO add different signs
	if () {
	switch(int)
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
}

void ASTCreator::buildNode(NodeType tpye) {
stack.addNewSign(tpye);
//	ASTNode newOp = new ASTNode(tpye);
//	head.addChild(newOp);
}
