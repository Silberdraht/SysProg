/*
 * InformationLinkedList.h
 *
 *  Created on: 25.02.2019
 *      Author: Einem
 */

#ifndef INFORMATIONLINKEDLIST_H_
#define INFORMATIONLINKEDLIST_H_

#include"Information.h"

class InformationLinkedList {
public:
	InformationLinkedList();
	virtual ~InformationLinkedList();

	struct InfStruct {

	        Information contains;
	        InfStruct *next;


	    };

    int addInfo(Information info);

    Information getInfo(char* lexem);

    Information getInfo(int KeyNr);

    bool containsInfo(char* lexem);

    bool isEmpty();

    int listLength();
private:
    InfStruct *head;
    int countSymbol = 0;

};

#endif /* INFORMATIONLINKEDLIST_H_ */
