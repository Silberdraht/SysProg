/*
 * ASTNode.h
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTNODE_H_
#define AST_ASTNODE_H_

#include "ASTBuild/ASTStack.h"
#include "ASTLinkedList.h"

class ASTNode{


public:
	ASTNode();
	ASTNode(NodeType newtype);
	virtual ~ASTNode();
	ASTLinkedList<ASTNode> getSubtree();
	ASTNode getParent();
	NodeType getType();
	void setType(NodeType newtype);
	void setParent(ASTNode newparent);
	void addChild(ASTNode child);
private:
    ASTNode* parent;
	ASTLinkedList<ASTNode> children;
	NodeType type;
};

#endif /* AST_ASTNODE_H_ */
