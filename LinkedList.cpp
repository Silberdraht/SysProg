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

void LinkedList::push_front(char c) {
    countSymbol++;
    Symbol *s = new Symbol();
    s->c = c;
    s->next = head;

    head = s;

}

//needed to use as list as "Last In Last Out" (add at end, pop at front)
void LinkedList::push_back(char c) {
    if (head == nullptr) {
        head = new Symbol();
        head->c = c;
    }
    else {
        Symbol *s = head;
        while (s->next != nullptr) {
            s = s->next;
        }
        Symbol *toAdd = new Symbol();
        toAdd->c = c;
        s->next = toAdd;
    }
    countSymbol++;

}


//Fix else
char LinkedList::pop_front() {
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

bool LinkedList::empty() {
    return countSymbol <= 0;
}

int LinkedList::size() {

    return countSymbol;
}
