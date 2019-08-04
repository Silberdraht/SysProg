//
// Created by Silberdraht on 11.10.2018.
//

#include "ASTLinkedList.h"


ASTLinkedList::ASTLinkedList() {
    head = nullptr;

}

ASTLinkedList::~ASTLinkedList() {

        Symbol *next = head;
        while (next) {

            Symbol *deleteSymbol = next;
            next = next->next;
            delete deleteSymbol;
        }

}

void ASTLinkedList::addNode(ASTNode c) {
    countSymbol++;
    Symbol *s = new Symbol();
    s->c = c;
    s->next = head;
    head -> prev -> next = s;
    head -> prev = s;
    head = s;
}

//needed to use as list as "Last In Last Out" (add at end, pop at front)
void ASTLinkedList::addNodeAsLast(ASTNode c) {
    if (head == nullptr) {
        head = new Symbol();
        head->c = c;
        head -> next = head;
        head -> prev = head;

    }
    else {
        Symbol *s = head->prev;

        Symbol *toAdd = new Symbol();
        head->prev->next = toAdd;
        toAdd ->prev = head -> prev;
        head -> prev = toAdd;
        toAdd ->next = head;

    }
    countSymbol++;

}


ASTNode ASTLinkedList::getNodeAt(int position) {
    if (countSymbol > 0) {
    	Symbol *s = head;
    	while(position > 0) {
    		position--;
    		s = s->next;
    	}
    	ASTNode c = s->c;
        return c;
    }
    return nullptr;

}

ASTNode ASTLinkedList::getLastNode() {
    return head -> prev;

}

