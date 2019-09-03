//
// Created by Nil on 01.09.2019.
//

#include <iostream>
#include "Link_List_Test.h"

int main(){
    Link_List<int> test;
    std::cout << test.size() << std::endl;
    test.push_back(1);
    test.push_back(2);
    std::cout << test.size() << std::endl;
    test.push_front(3);
    test.push_front(2);
    std::cout << test.size() << std::endl;
    std::cout << test.front() << std::endl;
    std::cout << test.back() << std::endl;
    std::cout << test.pop_front() << std::endl;
    std::cout << test.pop_back() << std::endl;


}