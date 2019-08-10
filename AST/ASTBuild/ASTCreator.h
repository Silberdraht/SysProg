/*
 * ASTCreator.h
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTCREATOR_H_
#define AST_ASTCREATOR_H_
#include"Automat.h"
#include"ASTNode.h"
#include "ASTStack.h"
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
	void buildDECLS();
	void buildDECL();
	void buildARRAY();
	void buildSTATEMENTS();
	void buildSTATEMENT();
	void buildEXP();
	void buildEXP2();
	void buildINDEX();
	void buildOP_EXP();
	void buildOP();
private:
	ASTStack stack;
	ASTNode head;
	ASTNode current;
	Automat::TokenType lastType;
	state state;
	int roundBracketsCounter;
	NodeType getTokenType(Automat::Token token);
	Automat::Token getToken();
	int checkForChar(char c);
	void buildNode(NodeType tpye);

};

#endif /* AST_ASTCREATOR_H_ */
