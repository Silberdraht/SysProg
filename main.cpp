#include <iostream>

#include "Automat.h"

int main() {


    Automat automat;

    automat.checkSymbol('5');
    automat.checkSymbol('6');
    automat.checkSymbol('7');
    automat.checkSymbol('x');

    automat.checkSymbol(' ');
    automat.checkSymbol('a');
    automat.checkSymbol('b');
    automat.checkSymbol('c');
    automat.checkSymbol('7');
    automat.checkSymbol(' ');

    automat.checkSymbol('5');
    automat.checkSymbol('6');
    automat.checkSymbol('7');
    automat.checkSymbol('=');





    std::cout << "Hello, World!" << std::endl;
    return 0;
}