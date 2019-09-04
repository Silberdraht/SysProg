/*
 * ASTNode.cpp
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#include "ASTNode.h"

ASTNode::ASTNode() {
	// TODO Auto-generated constructor stub

}

ASTNode::ASTNode(NodeType newtype){
    type = newtype;
}

ASTNode::~ASTNode() {
	// TODO Auto-generated destructor stub
}


ASTLinkedList<ASTNode> ASTNode::getSubtree() {
    return children;
}
ASTNode ASTNode::getParent() {
    return *parent;
}
NodeType ASTNode::getType(){
    return type;
}
void ASTNode::setType(NodeType newtype){
    type = newtype;
}
void ASTNode::setParent(ASTNode* newparent){
    parent = newparent;
}
void ASTNode::addChild(ASTNode child){
    children.addNode(child);
}

ASTNode* ASTNode::fullAddChild(NodeType newtype) {
	ASTNode *newNode = new ASTNode(newtype);
	children.addNode(*newNode);
	newNode ->parent = this;
	return newNode;
}

