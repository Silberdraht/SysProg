/*
 * ASTStack.cpp
 *
 *  Created on: 29.07.2019
 *      Author: Einem
 */

#include "ASTStack.h"

ASTStack::ASTStack() {
	// TODO Auto-generated constructor stub

}

ASTStack::~ASTStack() {
	// TODO Auto-generated destructor stub
}

NodeType ASTStack::getTopSign() {
	return stack[currentLevel][currentLevelDepth[currentLevel]];
	currentLevelDepth[currentLevel]--;
}
int ASTStack::isTopLevelEmpty() {
	return !currentLevelDepth[currentLevel];
}
NodeType ASTStack::peekTop() {
	return stack[currentLevel][currentLevelDepth[currentLevel]];
}
NodeType ASTStack::putOnTop() {
	//TODO ???????????????????????????????ß
	currentLevelDepth[currentLevel]++;
	stack[currentLevel][currentLevelDepth[currentLevel]] =
}
NodeType ASTStack::pullFromTop() {
	return stack[currentLevel][currentLevelDepth[currentLevel]];
		currentLevelDepth[currentLevel]--;

}
void ASTStack::addNewLayer() {
	currentLevel++;
	currentLevelDepth[currentLevel] = 0;
}
void ASTStack::removeTopLayer() {
	currentLevel--
}
void ASTStack::addNewSign(NodeType add) {
	currentLevelDepth[currentLevel]++;
	stack[currentLevel][currentLevelDepth[currentLevel]] = add;
}

