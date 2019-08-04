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
	 PLUSSIGN,
	 MINUSSIGN,
	 STARSIGN,
	 POUBLESIGN,
	 LESSSIGN,
	 GREATERSIGN,
	 EQUALSSIGN,
	 OTHEREQUALSSIGN,
	 ANDSIGN,
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
	 KL_OPEN,
	 KL_CLOSE,
	 EKL_OPEN,
	 EKL_CLOSE,
	 GKL_OPEN,
	 GKL_CLOSE

	};

class ASTStack {
public:
	ASTStack();
	virtual ~ASTStack();
	NodeType getTopSign();
	int isTopLevelEmpty();
	NodeType peekTop();
	int putOnTop();
	int pullFromTop();
	void addNewLayer();
	void addNewSign(NodeType);
};

#endif /* AST_ASTBUILD_ASTSTACK_H_ */
