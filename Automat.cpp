//
// Created by Silberdraht on 09.10.2018.
//


#include "Automat.h"

LinkedList list;


Automat::Automat() {

}
Automat::~Automat() {

}



void Automat::checkSymbol(char c) {


    switch (stateActive) {
        case init:
            if (isDigit(c)) {
                stateActive = digistate;
                list.addSymbol(c);
            }
            break;

        case digistate:
            if (isDigit(c)) {

                list.addSymbol(c);
            } else {
                stateActive = error;
                //create int token
                createTokenDigit();
                list.addSymbol(c);
            }
            break;


    }
}

    void Automat::createTokenDigit() {
        tokenDigit test;
        int ca[list.listLength()];
        int counter = list.listLength();
        int counter2 = counter;
        while (!list.isEmpty()) {

            //Fügt Inhalte der Verkettenen Liste in ein Char Array
            ca[counter-1] = convertChartoInt(list.popSymbol());

            //std::cout << ca[counter] << std::endl;

            counter--;


        }
        //std::cout << "Anzahl Counter nach while: " << std::endl;
        //std::cout << counter2 << std::endl;
        //std::cout << ca[0] << std::endl;
        //std::cout << ca[1] << std::endl;
        //std::cout << ca[2] << std::endl;


        int digitValue = 0;
        int power = 1;

        while (counter2 > 0) {

            digitValue += ((ca[counter2-1]) * power);


            power *= 10;
            counter2--;
        }



        std::cout << "Int value of Token: " << std::endl;
        std::cout << digitValue << std::endl;




    }

    bool Automat::isDigit(char c) {

        switch(c) {

            case '0':
                return true;
            case '1':
                return true;
            case '2':
                return true;
            case '3':
                return true;
            case '4':
                return true;
            case '5':
                return true;
            case '6':
                return true;
            case '7':
                return true;
            case '8':
                return true;
            case '9':
                return true;

            default:
                return false;

        }

    }

int Automat::convertChartoInt(char c) {

    switch(c) {

        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;

        default:;
    }

}







    //if (c != '\n' && c != ' ' && c != '/t') {

    //  if (isDigit(c)) {


    //  }

    //List is empty



    //list.addSymbol(c);


    //  }


