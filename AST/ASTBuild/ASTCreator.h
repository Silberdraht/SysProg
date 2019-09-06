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
	//erstellen  von countern fuer klammern? fehlermeldung werfen, wenn klammern nicht eingehalten werden?
	//wo ueberprfen?:
	//fuer {}:
	//fuer (): die () sind um expressions, daher: wenn man expressions verlaesst muessen diese abgeschlossen sein:
	//passende delimiter sind ";"
	//runde klammern kommen vor bei: funktionsaufrufen, statements wie if(...), evtl casten
public:
	explicit ASTCreator(Scanner scanner);
	int computeToken(Token token);
	void init();
	void buildPROG();
	void buildDECLS(Token token, std::shared_ptr<ASTNode> newNode);
	void buildDECL();
	void buildARRAY(Token token, std::shared_ptr<ASTNode> newNode);
	void buildSTATEMENTS(Token token, std::shared_ptr<ASTNode> newNode);
	void buildSTATEMENT(Token token);
	void buildEXP();
	void buildEXP2(Token token);
	void buildINDEX(Token token, std::shared_ptr<ASTNode> newNode);
	void buildOP_EXP(Token token, std::shared_ptr<ASTNode> newNode);
	void buildOP(Token token);
	int hasError();
	void setScanner(Scanner newscanner);
	void finish();

    std::shared_ptr<ASTNode> getParentNode();
    std::shared_ptr<ASTNode> buildHead;

private:
	ASTStack stack;
	std::shared_ptr<ASTNode> head;
    std::shared_ptr<ASTNode> current;
	TokenType lastType;
	Scanner scanner;
	Symtable table;
	state state;
	int roundBracketsCounter{};
	NodeType getTokenType(Token token);
	Token getToken();
	int checkForChar(char c);
	void buildNode(NodeType type);
	int checkCalcSign(Token token);
	int error = 0;
	int needsNewToken{};

};

#endif /* AST_ASTCREATOR_H_ */
