#include "Scanner.h"
#include "../tests/ScannerTest.h"
#include <iostream>
#include <chrono>

using namespace std;


int main(int argc, char* argv[]) {

    char* file;
    if (argc > 1) {
        file = argv[1];
    } else {
        file = (char *) R"(../input_code.txt)";
    }
    auto starttime = chrono::steady_clock::now();
    Scanner scanner = Scanner(Buffer(file));
	scanner.startScanner();

    //Output to check correctness of generated tokens
    ScannerTest test(scanner);

    if (!scanner.isWithoutErrors()) {
        return 1;
    } else {
        cout << "Scanner finished without error" << endl;
    }

    auto endtime = chrono::steady_clock::now();
    std::cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(endtime - starttime).count() << std::endl;
    std::cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(endtime - starttime).count() << std::endl;

    return 0;
}




