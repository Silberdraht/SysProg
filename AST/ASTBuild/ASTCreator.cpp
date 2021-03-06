/*
 * ASTCreator.cpp
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#include "ASTCreator.h"
#include <iostream>
using namespace std;

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
    else if (compare(token.storage.key, scanner.colon)) {
        return 1;
    }
	else if (compare(token.storage.key, scanner.minus)) {
		return 1;
	}
	else if (compare(token.storage.key, scanner.star)) {
		return 1;
	}
	else if (compare(token.storage.key, scanner.lesser)) {
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


int ASTCreator::computeToken(Token token) {
	needsNewToken = 1;
	while (needsNewToken) {
		if (error == 1) {
            cout << "Error: Unexpected token in line " << token.line << " column " << token.column << endl;
            cout << "\t expected " << typeToString(type) << endl;
			return 1;
		}
		type = getTokenType(token);
		std::shared_ptr<ASTNode> newNode;
		if (type != PROG) {
			newNode = std::make_shared<ASTNode>(head, type);
			head->addChild(newNode);
		} else {
		    newNode = std::make_shared<ASTNode>(nullptr, type);
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
			buildDECLS(token, newNode);
			break;
		case DECL:
			head = newNode;
			stack.addNewLayer();
			buildDECL();
			break;
		case ARRAY:
			buildARRAY(token, newNode);
			break;
		case STATEMENTS:
			buildSTATEMENTS(token, newNode);
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
			buildINDEX(token, newNode);
			break;
		case OP_EXP:
			buildOP_EXP(token, newNode);
			break;
		case OP:
			head = newNode;
			stack.addNewLayer();
			buildOP(token);
			break;

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
				newNode->setKey(token.storage.key);
                break;
			}
			error = 1;
			break;
		case INTEGER:
			if (token.tokenType == 1) {
				needsNewToken = 0;
				newNode->setDigit(token.storage.number);
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
				if (head->getType() == buildHead->getType()) {
                    cout << "Error: Unexpected token in line " << token.line << " column " << token.column << endl;
				    return 1;
				} else {
                    head = head->parent;
				}
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
void ASTCreator::buildDECLS(Token token, shared_ptr<ASTNode> newNode) {
	if (token.tokenType == 7 /*int*/) {
	    head = newNode;
		stack.addNewLayer();
		buildNode(DECL);
		buildNode(COLONSIGN);
		buildNode(DECLS);
	}
}

void ASTCreator::buildDECL() {

	buildNode(INTSIGN);
	buildNode(ARRAY);
	buildNode(IDENTIFIER);
}

void ASTCreator::buildARRAY(Token token, shared_ptr<ASTNode> newNode) {
	if (compare(token.storage.key, scanner.squareBracketOpen)) {
        head = newNode;
		stack.addNewLayer();
		buildNode(EKL_OPEN);
		buildNode(INTEGER);
		buildNode(EKL_CLOSE);
	} //else epsilon

}

void ASTCreator::buildSTATEMENTS(Token token, std::shared_ptr<ASTNode> newNode) {
	//Teste, ob zeichen leer sind
	if (token.tokenType == 2 || token.tokenType == 9 || token.tokenType == 8 || token.tokenType == 4 || token.tokenType == 5 || compare(token.storage.key, scanner.curlyBracketOpen)) {
        head = newNode;
	    stack.addNewLayer();
	    buildNode(STATEMENT);
        buildNode(COLONSIGN);
        buildNode(STATEMENTS);
		return;
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
	} else if (token.tokenType == 5) {
	    buildNode(WHILESIGN);
        buildNode(KL_OPEN);
        buildNode(EXP);
        buildNode(KL_CLOSE);
        buildNode(STATEMENT);
	}
	else {
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
        error = 1;
	}
}
void ASTCreator::buildINDEX(Token token, shared_ptr<ASTNode> newNode) {
	if (compare(token.storage.key, scanner.squareBracketOpen)) {
	    head = newNode;
		stack.addNewLayer();
		buildNode(EKL_OPEN);
		buildNode(EXP);
		buildNode(EKL_CLOSE);
	}
}
void ASTCreator::buildOP_EXP(Token token, shared_ptr<ASTNode> newNode) {
	if (checkCalcSign(token)/*OP*/) {
	    head = newNode;
		stack.addNewLayer();
		buildNode(OP);
		buildNode(EXP);
	}
}
void ASTCreator::buildOP(Token token) {
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
	}
	else if (compare(token.storage.key, scanner.lesser)) {
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

void ASTCreator::buildNode(NodeType type) {
	stack.addNewSign(type);
}

void ASTCreator::finish() {
	while (stack.hasLayers() && error == 0) {
		Token *ptoken = new Token();
		ptoken ->tokenType = TokenType::ErrorToken;
		NodeType type = stack.pullFromTop();
		Token token = *ptoken;
        std::shared_ptr<ASTNode> newNode = std::make_shared<ASTNode>(head, type);
        head->addChild(newNode);
		switch (type) {
            case DECLS:
                buildDECLS(token, newNode);
                break;
            case ARRAY:
                buildARRAY(token, head);
                break;
            case STATEMENTS:
                buildSTATEMENTS(token, newNode);
                break;
            case INDEX:
                buildINDEX(token, newNode);
                break;
            case OP_EXP:
                stack.addNewLayer();
                buildOP_EXP(token, newNode);
                break;
            default:
                error = 1;
                return;
        }
        //return;
	}
}
int ASTCreator::hasError() {
	return error == 1;
}

shared_ptr<ASTNode> ASTCreator::getParentNode() {
    return buildHead;
}


//STNode::ASTNode(std::shared_ptr<ASTNode> parent, NodeType newtype) : parent{parent}, type{newtype}{
//
//}
ASTCreator::ASTCreator(Scanner scanner) : scanner{scanner} {
    table = scanner.symtable;
}

int ASTCreator::buildTree() {
    cout << "Parser started..." << endl;
    while (scanner.hasTokens()) {
        if (computeToken(scanner.nextToken())) {
            cout << "Test failed. Parser did not complete" << endl;
            return 1;
        }

    }
    //finish();
    if (!hasError()) {
     cout << "Parser completed without error" << endl;
    } else {
        cout << "Parser completed with error" << endl;
    }

}

char *ASTCreator::typeToString(NodeType type) {
    switch(type) {
        case PROG: return (char*) "program";
        case DECLS: return (char*) "declarations";
        case DECL: return (char*) "declaration";
        case ARRAY: return (char*) "array";
        case STATEMENTS: return (char*) "statements";
        case STATEMENT: return (char*) "statement";
        case EXP: return (char*) "expression";
        case EXP2: return (char*) "expression";
        case INDEX: return (char*) "index";
        case OP_EXP: return (char*) "operand expression";
        case OP: return (char*) "operand";
        // terminale zeichen
        case PLUSSIGN: return (char*) "+";
        case MINUSSIGN: return (char*) "-";
        case STARSIGN: return (char*) "*";
        case DOUBLESIGN: return (char*) ":";
        case LESSSIGN: return (char*) "<";
        case GREATERSIGN: return (char*) ">";
        case EQUALSSIGN: return (char*) "=";
        case OTHEREQUALSSIGN: return (char*) ":=";
        case EQUPEQUSIGN: return (char*) "=:=";
        case ANDSIGN: return (char*) "&&";
        case COLONSIGN: return (char*) ";";
        case EXCLSIGN: return (char*) "!";
        // terminale
        case IFSIGN: return (char*) "if";
        case ELSESIGN: return (char*) "else";
        case WHILESIGN: return (char*) "while";
        case READSIGN: return (char*) "read";
        case WRITESIGN: return (char*) "write";
        case INTSIGN: return (char*) "int";
        // konstanten/ bezeichner
        case IDENTIFIER: return (char*) "identifier";
        case INTEGER: return (char*) "integer";
        // klammern
        case KL_OPEN: return (char*) "(";
        case KL_CLOSE: return (char*) ")";
        case EKL_OPEN: return (char*) "[";
        case EKL_CLOSE: return (char*) "]";
        case GKL_OPEN: return (char*) "{";
        case GKL_CLOSE: return (char*) "}";
        default: return (char*) " ";
    }
}
