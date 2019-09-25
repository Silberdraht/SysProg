/*
 * ASTCreator.h
 *
 *  Created on: 26.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTCREATOR_H_
#define AST_ASTCREATOR_H_


#include "ASTStack.h"
#include "../../../Scanner/Scanner.h"
#include "../../../Scanner/Automat.h"
#include "../ASTNode.h"

class ASTCreator {
	//erstellen  von countern fuer klammern? fehlermeldung werfen, wenn klammern nicht eingehalten werden?
	//wo ueberprfen?:
	//fuer {}:
	//fuer (): die () sind um expressions, daher: wenn man expressions verlaesst muessen diese abgeschlossen sein:
	//passende delimiter sind ";"
	//runde klammern kommen vor bei: funktionsaufrufen, statements wie if(...), evtl casten
public:
	explicit ASTCreator(Scanner scanner);
	int buildTree();
	int hasError();
    void finish();
    std::shared_ptr<ASTNode> getParentNode();
    std::shared_ptr<ASTNode> buildHead;

private:
	ASTStack stack;
	std::shared_ptr<ASTNode> head;
    Scanner scanner;

    NodeType getTokenType();
	char* typeToString(NodeType nodeType);
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
	void buildNode(NodeType nodeType);
	int checkCalcSign(Token token);
    int computeToken(Token token);
	int error = 0;
	int needsNewToken{};
    NodeType type;

};

#endif /* AST_ASTCREATOR_H_ */
