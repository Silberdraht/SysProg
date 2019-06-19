//
// Created by Silberdraht on 25.10.2018.
//

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "TestAutomat.h"
#include "Automat.h"
#include "Buffer.h"


TestAutomat::TestAutomat() {

}

TestAutomat::~TestAutomat() {

}
void TestAutomat::test() {

    Automat automat;


    std::ifstream is("C:\\Users\\Silberdraht\\Desktop\\beispieltest.txt");   // open file

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




//    Automat automat;
//    Buffer buffer;
//
//    std::ifstream is("F:\\Studium\\Compilerbau2019\\SysProg\\beispieltest.txt");   // open file

//    char c = ' ';
//    int count = 0;
//    while (c != '\0') {                 // loop getting single characters
//        c = buffer.getChar();
//        automat.checkSymbol(c);
//        count++;
//        //std::cout << c << " count: " << ++count << std::endl;
//    }
//    automat.endAutomat();

}