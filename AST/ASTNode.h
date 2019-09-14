/*
 * ASTNode.h
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#ifndef AST_ASTNODE_H_
#define AST_ASTNODE_H_

#include "ASTBuild/ASTStack.h"
#include "../Symtable.h"
#include "../lib/Link_List.h"

class ASTNode{
public:
    ASTNode(std::shared_ptr<ASTNode> parent, NodeType newtype);
	Link_List<std::shared_ptr<ASTNode>> getSubtree();
	ASTNode getParent();
	NodeType getType();
	Key getKey();
	long getDigit();
	void setKey(Key newkey);
	void setDigit(long newdigit);
	void setType(NodeType newtype);
	void setParent(std::shared_ptr<ASTNode> newparent);
	void addChild(std::shared_ptr<ASTNode> child);
	std::shared_ptr<ASTNode> parent;
private:
	Link_List<std::shared_ptr<ASTNode>> children;
	NodeType type;
	Key key;
	long digit;
};

#endif /* AST_ASTNODE_H_ */
