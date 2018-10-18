#include <iostream>

#include "Automat.h"

int main() {


    Automat automat;

    automat.checkSymbol('5');
    automat.checkSymbol('6');
    automat.checkSymbol('7');
    automat.checkSymbol('x');


    std::cout << "Hello, World!" << std::endl;
    return 0;
}