//
// Created by Silberdraht on 11.10.2018.
//


#ifndef SYSPROG_LINKEDLIST_H
#define SYSPROG_LINKEDLIST_H


#endif //SYSPROG_LINKEDLIST_H

class LinkedList {

    struct Symbol {

        char c;
        Symbol *next;
    };


public:
    LinkedList();

    ~LinkedList();

    void addSymbol(char c);

    void addSymbolAsLast(char c);

    char popSymbol();

    bool isEmpty();

    int listLength();

private:
    Symbol *head;
    int countSymbol = 0;


};