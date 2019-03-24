/*
 * InformationLinkedList.cpp
 *
 *  Created on: 25.02.2019
 *      Author: Einem
 */

#include "InformationLinkedList.h"

InformationLinkedList::InformationLinkedList() {
    head = nullptr;
    this->countSymbol = 0;
    InfStruct *head = nullptr;
}

InformationLinkedList::~InformationLinkedList() {

	InfStruct *next = head;
        while (next) {

        	InfStruct *deleteSymbol = next;
            next = next->next;
            delete deleteSymbol;
        }

}

int InformationLinkedList::addInfo(Information info) {
    this->countSymbol++;
    InfStruct *s = new InfStruct();
    s->contains = info;
    s->next = head;

    head = s;
    return countSymbol;

}

Information InformationLinkedList::getInfo(char* lexem) {
    if (countSymbol > 0) {
    	InfStruct *current = head;
    	while(current != nullptr) {
    		if(!(current->contains.compareLex(lexem))) {
    		    			break;
    		    		}
    		current = current->next;

    	}
        Information toReturn = current->contains;


        return toReturn;
    }
    return head->contains;

}

bool InformationLinkedList::isEmpty() {
return countSymbol <= 0;


}

int InformationLinkedList::listLength() {
    return countSymbol;
}

bool InformationLinkedList::containsInfo(char* lexem) {
	if (countSymbol > 0) {
	    	InfStruct *current = head;
	    	while(current != nullptr) {
	    		if(!(current->contains.compareLex(lexem))) {
	    			return true;
	    		}
	    		current = current->next;
	    	}
	    }
	    return false;
}

Information InformationLinkedList::getInfo(int KeyNr) {
	int count = KeyNr;
	if (countSymbol > 0) {
	    	InfStruct *current = head;
	    	while(current != nullptr && KeyNr < countSymbol) {
	    		current = current->next;
	    		count++;

	    	}
	        Information toReturn = current->contains;
	        return toReturn;
	    }
	    return head->contains;

	}

