#include "FileHandler.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "give valid line // "<< argv[0] <<" r/c filename \n";
        return 1;
    }

    char keyType = argv[1][0];
    if (keyType != 'r' && keyType != 'c') {
        cerr << "Invalid key type. Use 'r' or 'c'.\n";
        return 1;
    }

    AvlOperations records(keyType == 'c');
    FileHandler fileHandler;
    fileHandler.handleInput(records, argv[2]);

    int num;
    return 0;
}