/*
 * ASTStack.h
 *
 *  Created on: 29.07.2019
 *      Author: Einem
 */

#ifndef AST_ASTBUILD_ASTSTACK_H_
#define AST_ASTBUILD_ASTSTACK_H_

enum NodeType{
	// nichtterminale knoten
	PROG,
	DECLS,
	DECL,
	ARRAY,
	STATEMENTS,
	STATEMENT,
	EXP,
	EXP2,
	INDEX,
	OP_EXP,
	OP,

	// terminale zeichen
	 PLUSSIGN, 		//+
	 MINUSSIGN,		//-
	 STARSIGN,		//*
	 DOUBLESIGN,	//:
	 LESSSIGN,		//<
	 GREATERSIGN,	//>
	 EQUALSSIGN,	//=
	 OTHEREQUALSSIGN,//:=
	 EQUPEQUSIGN,	//=:=
	 ANDSIGN,		//&&
	 COLONSIGN,		//;
	 EXCLSIGN,		//!
	// terminale
	 IFSIGN,
	 ELSESIGN,
	 WHILESIGN,
	 READSIGN,
	 WRITESIGN,
	 INTSIGN,
	 // konstanten/ bezeichner
	 IDENTIFIER,
	 INTEGER,
	 // klammern
	 KL_OPEN,	//(
	 KL_CLOSE,
	 EKL_OPEN,	//[
	 EKL_CLOSE,
	 GKL_OPEN,	//{
	 GKL_CLOSE

	};

class ASTStack {
public:
	ASTStack();
	virtual ~ASTStack();
	NodeType getTopSign();
	int isTopLevelEmpty();
	NodeType peekTop();
	NodeType pullFromTop();
	void addNewLayer();
	void removeTopLayer();
	void addNewSign(NodeType);
private:
	const int stackSize = 30;
	const int stackDepth = 10;
	int **stack;
	int currentLevel = 0;
	int *currentLevelDepth;
};

#endif /* AST_ASTBUILD_ASTSTACK_H_ */
