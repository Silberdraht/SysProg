//
// Created by Silberdraht on 11.10.2018.
//


#ifndef SYSPROG_ASTLINKEDLIST_H
#define SYSPROG_ASTLINKEDLIST_H

#include "ASTNode.h"

class ASTLinkedList {

    struct Symbol {

    	ASTNode c;
        Symbol *next;
        Symbol *prev;
    };


public:
    ASTLinkedList();

    ~ASTLinkedList();

    void addNode(ASTNode c);

    void addNodeAsLast(ASTNode c);

    ASTNode getNodeAt(int position);

    bool isEmpty();

    int listLength();

    void removeLast();

    ASTNode getLastNode();

private:
    Symbol *head;
    int countSymbol = 0;


};
#endif //SYSPROG_ASTLINKEDLIST_H
