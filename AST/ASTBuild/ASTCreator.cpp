/*
 * ASTCreator.cpp
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#include "ASTCreator.h"
#include <iostream>
using namespace std;
void debugPrint(char* msg, NodeType tpye) {
	cout << msg;
	switch (tpye) {
	// nichtterminale knoten
	case PROG:
		cout << "PROG" << endl;
		break;
	case DECLS:
		cout << "DECLS" << endl;
		break;
	case DECL:
		cout << "DECL" << endl;
		break;
	case ARRAY:
		cout << "ARRAY" << endl;
		break;
	case STATEMENTS:
		cout << "STATEMENTS" << endl;
		break;
	case STATEMENT:
		cout << "TATEMENT" << endl;
		break;
	case EXP:
		cout << "EXP" << endl;
		break;
	case EXP2:
		cout << "EXP2" << endl;
		break;
	case INDEX:
		cout << "INDEX" << endl;
		break;
	case OP_EXP:
		cout << "OP_EXP" << endl;
		break;
	case OP:
		cout << "OP" << endl;
		break;
		// terminale
	case IFSIGN:
		cout << "IFSIGN" << endl;
		break;
	case ELSESIGN:
		cout << "ELSESIGN" << endl;
		break;
	case WHILESIGN:
		cout << "WHILESIGN" << endl;
		break;
	case READSIGN:
		cout << "READSIGN" << endl;
		break;
	case WRITESIGN:
		cout << "WRITESIGN" << endl;
		break;
	case INTSIGN:
		cout << "INTSIGN" << endl;
		break;
		// konstanten/ bezeichner
	case IDENTIFIER:
		cout << "IDENTIFIER" << endl;
		break;
	case INTEGER:
		cout << "INTEGER" << endl;
		break;
	default:
		cout << "SIGNTERMINAL" << endl;
		break;
	}
}
int compare(Key lex, Key comp) {
	if (lex.key != comp.key) {
		return 0;
	}
	if (lex.KeyNr != comp.KeyNr) {
		return 0;
	}
	return 1;
}

int ASTCreator::checkCalcSign(Token token) {
	if (compare(token.storage.key, scanner.plus)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.minus)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.star)) {
		return 1;
	} else if (compare(token.storage.key, scanner.lesser)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.greater)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.equals)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.colonEquals)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.equalsColonEquals)) {
		return 1;
	}

	else if (compare(token.storage.key, scanner.andAnd)) {
		return 1;
	}
	return 0;
}

void ASTCreator::setScanner(Scanner newscanner) {
	scanner = newscanner;
	table = scanner.symtable;
}

ASTCreator::ASTCreator() : head(ASTNode()), current(ASTNode()), buildHead(ASTNode()) {
	// TODO Auto-generated constructor stub

}

ASTCreator::~ASTCreator() {
	// TODO Auto-generated destructor stub
}

int ASTCreator::computeToken(Token token) {
	needsNewToken = 1;
	while (needsNewToken) {
		if (error == 1) {
			return 1;
		}
		NodeType type = getTokenType(token);
//		ASTNode *newNode = new ASTNode(type);
		ASTNode newNode(ASTNode());
		debugPrint("BUILDNODE: ", type);
		if (type != PROG) {
//			head->addChild(*newNode);
//			*newNode->parent = *head;
			newNode = head.fullAddChild(type);

		} else {
			//*head = *newNode; //TODO ???
		}
		switch (type) {
		//Check non-terminals
		case PROG:
			head = newNode;
            buildHead = newNode;
			stack.addNewLayer();
			buildPROG();
			break;
		case DECLS:
			head = newNode;
			buildDECLS(token);
			break;
		case DECL:
			head = newNode;
			stack.addNewLayer();
			buildDECL();
			break;
		case ARRAY:
			head = newNode;
			buildARRAY(token);
			break;
		case STATEMENTS:
			head = newNode;
			stack.addNewLayer();
			buildSTATEMENTS(token);
			break;
		case STATEMENT:
			head = newNode;
			stack.addNewLayer();
			buildSTATEMENT(token);
			break;
		case EXP:
			head = newNode;
			stack.addNewLayer();
			buildEXP();
			break;
		case EXP2:
			head = newNode;
			stack.addNewLayer();
			buildEXP2(token);
			break;
		case INDEX:
			head = newNode;
			buildINDEX(token);
			break;
		case OP_EXP:
			head = newNode;
			stack.addNewLayer();
			buildOP_EXP(token);
			break;
		case OP:
			head = newNode;
			stack.addNewLayer();
			buildOP(token);
			break;

			//TODO Terminale behandeln, die hier sind ALLE falsch, sind nur placeholder
			//man muss ein token einlesen und bestimmen, ob es dem Terminal entspricht
		case PLUSSIGN:	//+
			if (compare(token.storage.key, scanner.plus)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case MINUSSIGN:		//-
			if (compare(token.storage.key, scanner.minus)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case STARSIGN:		//*
			if (compare(token.storage.key, scanner.star)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case DOUBLESIGN:	//:
			if (compare(token.storage.key, scanner.colon)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case LESSSIGN:		//<
			if (compare(token.storage.key, scanner.lesser)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GREATERSIGN:	//>
			if (compare(token.storage.key, scanner.greater)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EQUALSSIGN:	//=
			if (compare(token.storage.key, scanner.equals)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case OTHEREQUALSSIGN:	//:=
			if (compare(token.storage.key, scanner.colonEquals)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EQUPEQUSIGN:	//=:=
			if (compare(token.storage.key, scanner.equalsColonEquals)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case ANDSIGN:	//&&
			if (compare(token.storage.key, scanner.andAnd)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case COLONSIGN:		//;
			if (compare(token.storage.key, scanner.semicolon)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EXCLSIGN:		//!
			if (compare(token.storage.key, scanner.exclamationMark)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case IFSIGN:
			if (token.tokenType == 4) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case ELSESIGN:
			if (token.tokenType == 6) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case WHILESIGN:
			if (token.tokenType == 5) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case READSIGN:
			if (token.tokenType == 8) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case WRITESIGN:
			if (token.tokenType == 9) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case INTSIGN:
			if (token.tokenType == 7) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case IDENTIFIER:
			if (token.tokenType == 2) {
				needsNewToken = 0;
				newNode.setKey(token.storage.key);
                break;
			}
			error = 1;
			break;
		case INTEGER:
			if (token.tokenType == 1) {
				needsNewToken = 0;
				newNode.setDigit(token.storage.number);
                break;
			}
			error = 1;
			break;
		case KL_OPEN:	//(
			if (compare(token.storage.key, scanner.bracketOpen)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case KL_CLOSE:
			if (compare(token.storage.key, scanner.bracketClose)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EKL_OPEN:	//[
			if (compare(token.storage.key, scanner.squareBracketOpen)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EKL_CLOSE:
			if (compare(token.storage.key, scanner.squareBracketClose)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GKL_OPEN:	//{
			if (compare(token.storage.key, scanner.curlyBracketOpen)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GKL_CLOSE:
			if (compare(token.storage.key, scanner.curlyBracketClose)) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		default:
			error = 1;
		}
		if (stack.isTopLevelEmpty()) {
			if (!stack.hasLayers() && !scanner.hasTokens()) {
				return 0;
			}
			while (stack.isTopLevelEmpty()) {
				stack.removeTopLayer();
				head = head.parent;
			}
		}
	}
	return 0;
}

NodeType ASTCreator::getTokenType(Token token) {
	return stack.pullFromTop();
}

void ASTCreator::buildPROG() {
	buildNode(DECLS);
	buildNode(STATEMENTS);
}
void ASTCreator::buildDECLS(Token token) {
	//Teste, ob zeichen leer sind
	//TODO int einprogrammieren
	if (token.tokenType == 7 /*int*/) {
		stack.addNewLayer();
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
void ASTCreator::buildARRAY(Token token) {
	if (compare(token.storage.key, scanner.squareBracketClose)) {
		stack.addNewLayer();
		buildNode(EKL_OPEN);
		buildNode(INTEGER);
		buildNode(EKL_CLOSE);
	} else {
		//elypson
	}

}
void ASTCreator::buildSTATEMENTS(Token token) {
	//Teste, ob zeichen leer sind
	//TODO wenn zeichenkette leer is tritt dieser Fall ein
	if (token.tokenType == 3) {
		return;
	} else {
		buildNode(STATEMENT);
		buildNode(COLONSIGN);
		buildNode(STATEMENTS);
	}

}
void ASTCreator::buildSTATEMENT(Token token) {
	// hier unterscheiden, wass passiert!
	if (token.tokenType == 2/*IdentifierToken*/) {
		buildNode(IDENTIFIER);
		buildNode(INDEX);
		buildNode(OTHEREQUALSSIGN);
		buildNode(EXP);
	} else if (token.tokenType == 9 /*writetoken*/) {
		buildNode(WRITESIGN);
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
	} else if (token.tokenType == 8/*readToken*/) {
		buildNode(READSIGN);
		buildNode(KL_OPEN);
		buildNode(IDENTIFIER);
		buildNode(INDEX);
		buildNode(KL_CLOSE);
	} else if (compare(token.storage.key, scanner.curlyBracketOpen)) {
		buildNode(GKL_OPEN);
		buildNode(STATEMENTS);
		buildNode(GKL_CLOSE);
	} else if (token.tokenType == 4/*IfToken*/) {
		buildNode(IFSIGN);
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
		buildNode(STATEMENT);
		buildNode(ELSESIGN);
		buildNode(STATEMENT);
	} else {
		error = 1;
	}
}
void ASTCreator::buildEXP() {
	buildNode(EXP2);
	buildNode(OP_EXP);
}
void ASTCreator::buildEXP2(Token token) {
	if (compare(token.storage.key, scanner.bracketOpen)) {
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
	} else if (token.tokenType == 2/*IdentifierToken*/) {
		buildNode(IDENTIFIER);
		buildNode(INDEX);
	} else if (token.tokenType == 1 /*digitToken*/) {
		buildNode(INTEGER);
	} else if (compare(token.storage.key, scanner.minus)) {
		buildNode(MINUSSIGN);
		buildNode(EXP2);
	} else if (compare(token.storage.key, scanner.exclamationMark)) {
		buildNode(EXCLSIGN);
		buildNode(EXP2);
	} else {
		// wenns hier unten ankonnt is was schief gegangen!
		error = 1;
	}
}
void ASTCreator::buildINDEX(Token token) {
	if (compare(token.storage.key, scanner.squareBracketOpen)) {
		stack.addNewLayer();
		buildNode(EKL_OPEN);
		buildNode(EXP);
		buildNode(EKL_CLOSE);
	}
}
void ASTCreator::buildOP_EXP(Token token) {
	if (checkCalcSign(token)/*OP*/) {
		stack.addNewLayer();
		buildNode(OP);
		buildNode(EXP);
	}
}
void ASTCreator::buildOP(Token token) {
	//TODO add different signs

	if (compare(token.storage.key, scanner.plus)) {
		buildNode(PLUSSIGN);
	}

	else if (compare(token.storage.key, scanner.minus)) {
		buildNode(MINUSSIGN);
	}

	else if (compare(token.storage.key, scanner.star)) {
		buildNode(STARSIGN);
	}

	else if (compare(token.storage.key, scanner.colon)) {
		buildNode(DOUBLESIGN);
	} else if (compare(token.storage.key, scanner.lesser)) {
		buildNode(LESSSIGN);
	}

	else if (compare(token.storage.key, scanner.greater)) {
		buildNode(GREATERSIGN);
	}

	else if (compare(token.storage.key, scanner.equals)) {
		buildNode(EQUALSSIGN);
	}

	else if (compare(token.storage.key, scanner.colonEquals)) {
		buildNode(OTHEREQUALSSIGN);
	}

	else if (compare(token.storage.key, scanner.equalsColonEquals)) {
		buildNode(EQUPEQUSIGN);
	}

	else if (compare(token.storage.key, scanner.andAnd)) {
		buildNode(ANDSIGN);
	}

	else if (compare(token.storage.key, scanner.semicolon)) {
		buildNode(COLONSIGN);
	}

	else if (compare(token.storage.key, scanner.exclamationMark)) {
		buildNode(EXCLSIGN);
	} else {
		error = 1;
	}

}

void ASTCreator::buildNode(NodeType tpye) {
	stack.addNewSign(tpye);
//	ASTNode newOp = new ASTNode(tpye);
//	head.addChild(newOp);
	debugPrint("stack: ", tpye);
}

void ASTCreator::finish() {
	while (stack.hasLayers() && error == 0) {
		Token *ptoken = new Token();
		ptoken ->tokenType = TokenType::ErrorToken;
		NodeType type = stack.pullFromTop();
		Token token = *ptoken;
		ASTNode newNode(ASTNode());
		debugPrint("BUILDNODE: ", type);
		newNode = head.fullAddChild(type);
		switch (type) {
		case DECLS:
			head = newNode;
			buildDECLS(token);
			break;
		case ARRAY:
			head = newNode;
			buildARRAY(token);
			break;
		case STATEMENTS:
			head = newNode;
			stack.addNewLayer();
			buildSTATEMENTS(token);
			break;
		case INDEX:
			head = newNode;
			buildINDEX(token);
			break;
		case OP_EXP:
			head = newNode;
			stack.addNewLayer();
			buildOP_EXP(token);
			break;
		default:
			error = 1;
			return;
	}
	return;
	}

}
int ASTCreator::hasError() {
	return error == 1;
}

ASTNode ASTCreator::getParentNode() {
    //TODO return top level node (sollte wahrscheinlich vom typ PROG sein)
    return buildHead;
}
