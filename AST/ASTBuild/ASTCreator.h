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
	//erstellen  von countern f�r klammern? fehlermeldung werfen, wenn klammern nicht eingehalten werden?
	//wo �berprfen?:
	//f�r {}:
	//f�r (): die () sind um expressions, daher: wenn man expressions verl�sst m�ssen diese abgeschlossen sein:
	//passende delimiter sind ";"
	//runde klammern kommen vor bei: funktionsaufrufen, statements wie if(...), evtl casten
public:
	ASTCreator();
	virtual ~ASTCreator();
	int computeToken(Token token);
	void init();
	void buildPROG();
	void buildDECLS(Token token);
	void buildDECL();
	void buildARRAY(Token token);
	void buildSTATEMENTS(Token token);
	void buildSTATEMENT(Token token);
	void buildEXP();
	void buildEXP2(Token token);
	void buildINDEX(Token token);
	void buildOP_EXP(Token token);
	void buildOP(Token token);
	int hasError();
	void setScanner(Scanner newscanner);
	void finish();
private:
	ASTStack stack;
	ASTNode *head;
	ASTNode current;
	TokenType lastType;
	Scanner scanner;
	Symtable table;
	state state;
	int roundBracketsCounter;
	NodeType getTokenType(Token token);
	Token getToken();
	int checkForChar(char c);
	void buildNode(NodeType tpye);
	int checkCalcSign(Token token);
	int error = 0;
	int needsNewToken;

};

#endif /* AST_ASTCREATOR_H_ */
