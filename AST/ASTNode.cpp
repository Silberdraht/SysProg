/*
 * ASTNode.cpp
 *
 *  Created on: 25.06.2019
 *      Author: Einem
 */

#include "ASTNode.h"



ASTNode::ASTNode(std::shared_ptr<ASTNode> parent) : parent{parent}{

}

ASTNode::ASTNode(NodeType newtype) : parent{nullptr} , type{newtype}{
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
void ASTNode::setParent(std::shared_ptr<ASTNode> newparent){
    parent = newparent;
}
void ASTNode::addChild(ASTNode child){
    children.push_front(child);
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

