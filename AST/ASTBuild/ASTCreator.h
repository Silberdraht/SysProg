/*
 * ASTCreator.h
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTCREATOR_H_
#define AST_ASTCREATOR_H_


#include "ASTStack.h"
#include "../../Scanner.h"
#include "../../Symtable.h"
#include "../../Automat.h"
#include "../ASTNode.h"
enum state{
	initStatement,
	statementExpectingOperand,
	initExpression,
	expressionExceptingOperand,
	expressionExceptingSecond
};

class ASTCreator {
	//erstellen  von countern für klammern? fehlermeldung werfen, wenn klammern nicht eingehalten werden?
	//wo überprfen?:
	//für {}:
	//für (): die () sind um expressions, daher: wenn man expressions verlässt müssen diese abgeschlossen sein:
	//passende delimiter sind ";"
	//runde klammern kommen vor bei: funktionsaufrufen, statements wie if(...), evtl casten
public:
	ASTCreator();
	virtual ~ASTCreator();
	int computeToken(Automat::Token token);
	void init();
	void buildPROG();
	void buildDECLS(Automat::Token token);
	void buildDECL();
	void buildARRAY(Automat::Token token);
	void buildSTATEMENTS(Automat::Token token);
	void buildSTATEMENT(Automat::Token token);
	void buildEXP();
	void buildEXP2(Automat::Token token);
	void buildINDEX(Automat::Token token);
	void buildOP_EXP(Automat::Token token);
	void buildOP(Automat::Token token);
	void hasError();
	void setScanner(Scanner newscanner);
private:
	ASTStack stack;
	ASTNode *head;
	ASTNode current;
	Automat::TokenType lastType;
	Scanner scanner;
	Symtable table;
	state state;
	int roundBracketsCounter;
	NodeType getTokenType(Automat::Token token);
	Automat::Token getToken();
	int checkForChar(char c);
	void buildNode(NodeType tpye);
	int checkCalcSign(Automat::Token token);
	int error;
	int needsNewToken;

};

#endif /* AST_ASTCREATOR_H_ */
