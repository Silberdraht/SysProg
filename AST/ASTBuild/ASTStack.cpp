/*
 * ASTStack.cpp
 *
 *  Created on: 29.07.2019
 *      Author: Einem
 */

#include "ASTStack.h"

ASTStack::ASTStack() {
	//stack = new int[stackSize][stackDepth];
	currentLevelDepth = new int[stackSize];
	currentLevelDepthfront = new int[stackSize];
	stack = new int*[stackSize];

	for(int i = 0;i < stackSize;i++) {
    stack[i] = new int[stackDepth];
    currentLevelDepth[0] = 0;
    currentLevelDepthfront[0] = 0;
    currentLevel = 0;
	}
	addNewSign(PROG);

}

ASTStack::~ASTStack() {
	// TODO Auto-generated destructor stub
}

NodeType ASTStack::getTopSign() {
	return (NodeType)stack[currentLevel][currentLevelDepth[currentLevel]];
	currentLevelDepth[currentLevel]--;
}
int ASTStack::isTopLevelEmpty() {
	return currentLevelDepth[currentLevel] <= currentLevelDepthfront[currentLevel];
}
NodeType ASTStack::peekTop() {
	return (NodeType) stack[currentLevel][currentLevelDepthfront[currentLevel]];
}

NodeType ASTStack::pullFromTop() {
	int depth = currentLevelDepthfront[currentLevel];
	NodeType toReturn = (NodeType)stack[currentLevel][depth+1];
		currentLevelDepthfront[currentLevel]++;
		return toReturn;

}
void ASTStack::addNewLayer() {
	currentLevel++;
	currentLevelDepth[currentLevel] = 0;
	currentLevelDepthfront[currentLevel] = 0;
}
void ASTStack::removeTopLayer() {
	currentLevel--;
}
int ASTStack::hasLayers() {
	return currentLevel > 0;
}
void ASTStack::addNewSign(NodeType add) {
	currentLevelDepth[currentLevel]++;
	int cld = currentLevelDepth[currentLevel];
	stack[currentLevel][cld] = add;
}

