//
// Created by Silberdraht on 11.10.2018.
//

#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;

}

LinkedList::~LinkedList() {



        Symbol *next = head;
        while (next) {

            Symbol *deleteSymbol = next;
            next = next->next;
            delete deleteSymbol;
        }

}

void LinkedList::addSymbol(char c) {
    countSymbol++;
    Symbol *s = new Symbol();
    s->c = c;
    s->next = head;

    head = s;

}

//Fix else
char LinkedList::popSymbol() {
    if (countSymbol > 0) {

        countSymbol--;

        Symbol *s = head;
        char c = s->c;

        head = head->next;
        delete s;

        return c;
    }
    return ' ';

}

bool LinkedList::isEmpty() {
return countSymbol <= 0;


}

int LinkedList::listLength() {

    return countSymbol;
}
