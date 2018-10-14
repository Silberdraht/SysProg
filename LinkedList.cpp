//
// Created by Silberdraht on 11.10.2018.
//

#include "LinkedList.h"

LinkedList::LinkedList() {

}

LinkedList::~LinkedList() {

    //TO FIX
  /*
        Symbol *next = head;
        while (next) {

            Symbol *deleteSymbol = next;
            next = next->next;
            delete deleteSymbol;
        }
    */
}

void LinkedList::addSymbol(char c) {
    Symbol *s = new Symbol();
    s->c = c;
    s->next = head;

    head = s;

}

char LinkedList::popSymbol() {

    Symbol *s = head;
    char c = s->c;

    head = head->next;
    delete s;

    return c;

}