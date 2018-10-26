#include <iostream>

#include "Automat.h"
#include "TestAutomat.h"

#include <fstream>      // std::ifstream

int main() {


    Automat automat;


    std::ifstream is("C:\\Users\\Silberdraht\\Desktop\\beispiel.txt");   // open file

    char c;
    while (is.get(c))                  // loop getting single characters
       automat.checkSymbol(c);
    std::cout << c << std::endl;

    if (is.eof())                      // check for EOF
        std::cout << "[EoF reached]\n";
    else
        std::cout << "[error reading]\n";

    is.close();

    automat.endAutomat();




    std::cout << "Hello, World!" << std::endl;


    return 0;
}