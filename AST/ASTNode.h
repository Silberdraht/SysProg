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
#include "../Symtable.h"

class ASTNode{


public:
	ASTNode();
	ASTNode(NodeType newtype);
	virtual ~ASTNode();
	ASTLinkedList<ASTNode> getSubtree();
	ASTNode getParent();
	NodeType getType();
	Key getKey();
	long getDigit();
	void setKey(Key newkey);
	void setDigit(long newdigit);
	void setType(NodeType newtype);
	void setParent(ASTNode* newparent);
	void addChild(ASTNode child);
	ASTNode* fullAddChild(NodeType newtype);
	ASTNode* parent;
private:
	ASTLinkedList<ASTNode> children;
	NodeType type;
	Key key;
	long digit;
};

#endif /* AST_ASTNODE_H_ */
