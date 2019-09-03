/*
 * ASTCreator.cpp
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#include "ASTCreator.h"


int compare(char* lex, char* comp) {
	return lex == comp;
}

ASTCreator::ASTCreator() {
	// TODO Auto-generated constructor stub

}

ASTCreator::~ASTCreator() {
	// TODO Auto-generated destructor stub
}

int ASTCreator::computeToken(Automat::Token token) {
	needsNewToken = 1;
	while (needsNewToken) {
		if(error == 1) {
			return 1;
		}
		NodeType type = getTokenType(token);
		switch (stack.pullFromTop()) {
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
			buildOP(token);
			break;

			//TODO Terminale behandeln, die hier sind ALLE falsch, sind nur placeholder
			//man muss ein token einlesen und bestimmen, ob es dem Terminal entspricht
		case PLUSSIGN:	//+
			if (compare(token.storage.lexem, table.lookup(scanner.plus).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case MINUSSIGN:		//-
			if (compare(token.storage.lexem, table.lookup(scanner.minus).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case STARSIGN:		//*
			if (compare(token.storage.lexem, table.lookup(scanner.star).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case DOUBLESIGN:	//:
			if (compare(token.storage.lexem,  table.lookup(scanner.colon).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case LESSSIGN:		//<
			if (compare(token.storage.lexem,  table.lookup(scanner.lesser).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GREATERSIGN:	//>
			if (compare(token.storage.lexem,  table.lookup(scanner.greater).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EQUALSSIGN:	//=
			if (compare(token.storage.lexem,  table.lookup(scanner.equals).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case OTHEREQUALSSIGN:	//:=
			if (compare(token.storage.lexem,  table.lookup(scanner.colonEquals).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EQUPEQUSIGN:	//=:=
			if (compare(token.storage.lexem,  table.lookup(scanner.equalsColonEquals).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case ANDSIGN:	//&&
			if (compare(token.storage.lexem,  table.lookup(scanner.andAnd).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case COLONSIGN:		//;
			if (compare(token.storage.lexem,  table.lookup(scanner.semicolon).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EXCLSIGN:		//!
			if (compare(token.storage.lexem,  table.lookup(scanner.exclamationMark).getLexem())) {
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
				break;
			}
			error = 1;
			break;
		case INTEGER:
			if (token.tokenType == 1) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case KL_OPEN:	//(
			if (compare(token.storage.lexem,  table.lookup(scanner.bracketOpen).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case KL_CLOSE:
			if (compare(token.storage.lexem,  table.lookup(scanner.bracketClose).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EKL_OPEN:	//[
			if (compare(token.storage.lexem,  table.lookup(scanner.squareBracketOpen).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case EKL_CLOSE:
			if (compare(token.storage.lexem,  table.lookup(scanner.squareBracketClose).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GKL_OPEN:	//{
			if (compare(token.storage.lexem, table.lookup(scanner.curlyBracketOpen).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		case GKL_CLOSE:
			if (compare(token.storage.lexem, table.lookup(scanner.curlyBracketClose).getLexem())) {
				needsNewToken = 0;
				break;
			}
			error = 1;
			break;
		default:
			error = 1;
		}
		//build new Nodes, set head if nessesairy
		//TODO: stack level überwachen!!!!!!!!!!!!
		ASTNode *newNode = new ASTNode(type);
		head.addChild(*newNode);
		if (stack.isTopLevelEmpty()) {
			while (stack.isTopLevelEmpty()) {
				stack.removeTopLayer();
				head = head.getParent();
			}
		} else {
			head = *newNode;
		}
	}
	return 0;
}

NodeType ASTCreator::getTokenType(Automat::Token token) {
	return stack.pullFromTop();
}

void ASTCreator::buildPROG() {
    ASTNode *test =new ASTNode(PROG);
	head = *test;
	buildNode(DECLS);
	buildNode(STATEMENTS);
}
void ASTCreator::buildDECLS(Automat::Token token) {
	//Teste, ob zeichen leer sind
	//TODO int einprogrammieren
	if (token.tokenType == 7 /*int*/) {
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
	if (compare(token.storage.lexem, "[")) {
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
	} else if (compare(token.storage.lexem, "{")) {
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
void ASTCreator::buildEXP2(Automat::Token token) {
	if (compare(token.storage.lexem, "(")) {
		buildNode(KL_OPEN);
		buildNode(EXP);
		buildNode(KL_CLOSE);
	} else if (token.tokenType == 2/*IdentifierToken*/) {
		buildNode(IDENTIFIER);
		buildNode(INDEX);
	} else if (token.tokenType) {
		buildNode(INTEGER);
	} else if (compare(token.storage.lexem, "-")) {
		buildNode(MINUSSIGN);
		buildNode(EXP2);
	} else if (compare(token.storage.lexem, "!")) {
		buildNode(EXCLSIGN);
		buildNode(EXP2);
	} else {
	// wenns hier unten ankonnt is was schief gegangen!
	error = 1;
	}
}
void ASTCreator::buildINDEX(Automat::Token token) {
	if (compare(token.storage.lexem, "[")) {
		buildNode(EKL_OPEN);
		buildNode(EXP);
		buildNode(EKL_CLOSE);
	}
}
void ASTCreator::buildOP_EXP(Automat::Token token) {
	buildNode(OP);
	buildNode(EXP);
}
void ASTCreator::buildOP(Automat::Token token) {
	//TODO add different signs

	if (compare(token.storage.lexem, "+")) {
		buildNode(PLUSSIGN);
	}

	else if (compare(token.storage.lexem, "-")) {
		buildNode(MINUSSIGN);
	}

	else if (compare(token.storage.lexem, "*")) {
		buildNode(STARSIGN);
	}

	else if (compare(token.storage.lexem, ":")) {
		buildNode(DOUBLESIGN);
	}
	else if (compare(token.storage.lexem, "<")) {
		buildNode(LESSSIGN);
	}

	else if (compare(token.storage.lexem, ">")) {
		buildNode(GREATERSIGN);
	}

	else if (compare(token.storage.lexem, "=")) {
		buildNode(EQUALSSIGN);
	}

	else if (compare(token.storage.lexem, ":=")) {
		buildNode(OTHEREQUALSSIGN);
	}

	else if (compare(token.storage.lexem, "=:=")) {
		buildNode(EQUPEQUSIGN);
	}

	else if (compare(token.storage.lexem, "&&")) {
		buildNode(ANDSIGN);
	}

	else if (compare(token.storage.lexem, ";")) {
		buildNode(COLONSIGN);
	}

	else if (compare(token.storage.lexem, "!")) {
		buildNode(EXCLSIGN);
	} else {
	error = 1;
	}

}

void ASTCreator::buildNode(NodeType tpye) {
	stack.addNewSign(tpye);
//	ASTNode newOp = new ASTNode(tpye);
//	head.addChild(newOp);
}

void ASTCreator::setScanner(Scanner newscanner) {
	scanner = newscanner;
}

