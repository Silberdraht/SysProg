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
#include "../lib/Link_List.h"

class ASTNode{


public:
    explicit ASTNode(ASTNode parent);
	ASTNode(NodeType newtype, ASTNode parent);
	Link_List<ASTNode> getSubtree();
	ASTNode getParent();
	NodeType getType();
	Key getKey();
	long getDigit();
	void setKey(Key newkey);
	void setDigit(long newdigit);
	void setType(NodeType newtype);
	void setParent(ASTNode* newparent);
	void addChild(ASTNode child);
	ASTNode fullAddChild(NodeType newtype);
	ASTNode parent;
private:
	Link_List<ASTNode> children;
	NodeType type;
	Key key;
	long digit;
};

#endif /* AST_ASTNODE_H_ */
