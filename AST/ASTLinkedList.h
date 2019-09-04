//
// Created by Silberdraht on 11.10.2018.
//


#ifndef SYSPROG_ASTLINKEDLIST_H
#define SYSPROG_ASTLINKEDLIST_H

template <typename T>
class ASTLinkedList {

    struct Symbol {

    	T c;
        Symbol *next;
        Symbol *prev;
    };


public:
    ASTLinkedList();
    ~ASTLinkedList();
    void addNode(T c);
    void addNodeAsLast(T c);
    T getNodeAt(int position);
    bool isEmpty();
    int listLength();
    void removeLast();
    T getLastNode();

private:
    Symbol *head;
    int countSymbol = 0;


};
template <class T>
ASTLinkedList<T>::ASTLinkedList() {
    head = nullptr;

}
template <class T>
ASTLinkedList<T>::~ASTLinkedList() {

        Symbol *next = head;
        while (next) {

            Symbol *deleteSymbol = next;
            next = next->next;
            delete deleteSymbol;
        }

}

template <class T>
void ASTLinkedList<T>::addNode(T c) {
    countSymbol++;
    Symbol *s = new Symbol();
    s->c = c;
    if(countSymbol == 0) {
    s->next = head;
    head -> prev = s;
    head -> prev -> next = s;
    head = s;
    } else {
    	head = s;
    	head -> next = s;
    	head -> prev = s;
    }
    countSymbol++;
}

//needed to use as list as "Last In Last Out" (add at end, pop at front)
template <class T>
void ASTLinkedList<T>::addNodeAsLast(T c) {
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


template <class T>
T ASTLinkedList<T>::getNodeAt(int position) {
    if (countSymbol > 0) {
    	Symbol *s = head;
    	while(position > 0) {
    		position--;
    		s = s->next;
    	}
    	T c = s->c;
        return c;
    }
    return new T();

}

template <class T>
T ASTLinkedList<T>::getLastNode() {
    return head -> prev->c;

}
#endif //SYSPROG_ASTLINKEDLIST_H
