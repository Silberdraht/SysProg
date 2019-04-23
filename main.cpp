#include "TestAutomat.h"
#include "Scanner.h"


int main() {


    Scanner scanner;
    scanner.startScanner();

    while (scanner.hasTokens()) {
        std::cout << scanner.nextToken().tokenType << std::endl;
    }

    return 0;
}