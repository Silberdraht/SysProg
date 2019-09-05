/*
 * ASTNode.cpp
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#include "ASTNode.h"



ASTNode::ASTNode(ASTNode parent) : parent{parent}{

}

ASTNode::ASTNode(NodeType newtype, ASTNode parent) : parent{parent}) {
    type = newtype;
}



Link_List<ASTNode> ASTNode::getSubtree() {
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
    children.push_front(child);
}

ASTNode ASTNode::fullAddChild(NodeType newtype) {
	ASTNode newNode = ASTNode(newtype)(<#initializer#>, ASTNode(ASTNode(ASTNode())));
	children.push_front(newNode);
	newNode.parent = this;
	return newNode;
}
Key ASTNode::getKey() {
	return key;
}
long ASTNode::getDigit() {
	return digit;
}
void ASTNode::setKey(Key newkey) {
	key = newkey;
}
void ASTNode::setDigit(long newdigit) {
	digit = newdigit;
}

