/*
 * ASTNode.h
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTNODE_H_
#define AST_ASTNODE_H_

#include "ASTLinkedList.h"
#include "ASTStack.h"


class ASTNode{

private:
	ASTLinkedList children;
public:
	ASTNode();
	virtual ~ASTNode();
	ASTLinkedList getSubtree();
	ASTNode getParent();
	NodeType getType();
	void setType(NodeType type);
	void setParent(ASTNode parent);

};

#endif /* AST_ASTNODE_H_ */
