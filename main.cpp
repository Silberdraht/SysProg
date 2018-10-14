#include <iostream>
#include "LinkedList.h"

int main() {

    LinkedList list;

    list.addSymbol('x');
    list.addSymbol('x');
    list.addSymbol('t');
    list.addSymbol('s');
    list.addSymbol('e');
    list.addSymbol('t');








    std::cout << list.popSymbol() << std::endl;
    std::cout << list.popSymbol() << std::endl;
    std::cout << list.popSymbol() << std::endl;
    std::cout << list.popSymbol() << std::endl;

    list.~LinkedList();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}