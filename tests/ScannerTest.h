//
// Created by noahp on 04/09/2019.
//

#ifndef SYSPROG_SCANNERTEST_H
#define SYSPROG_SCANNERTEST_H


#include "../Scanner.h"

class ScannerTest {

    Scanner scanner;

public:

    explicit ScannerTest(const Scanner& scanner);

    void outputTokensToFile();

};


#endif //SYSPROG_SCANNERTEST_H
