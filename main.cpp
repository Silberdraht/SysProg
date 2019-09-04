
#include "Scanner.h"
#include "tests/ScannerTest.h"


int main() {

    Scanner scanner;
    scanner.initializeSymtable();
    scanner.startScanner();

    //Output to check correctness of generated tokens
    ScannerTest test(scanner);

    return 0;
}