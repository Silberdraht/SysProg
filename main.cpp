#include "TestAutomat.h"
#include "Scanner.h"


int main() {

    std::ofstream ofs {"out.txt",std::ios_base::binary};

    /*
    std::ofstream ofs {"out.txt",std::ios_base::binary};
    ofs << "Test lolz" << std::endl;
    ofs << "Test lolz2" << std::endl;
    ofs << "Test lolz3" << std::endl;
*/
    Scanner scanner;
    scanner.startScanner();

    while (scanner.hasTokens()) {
        std::cout << scanner.nextToken().tokenType << std::endl;
    }

    return 0;
}