#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "AvlOperations.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class FileHandler {
public:
    void handleInput(AvlOperations &records, const string &filename);

private:
    bool processLine(const string &line, AvlOperations &records, ifstream &inputFile);
};

#endif // FILEHANDLER_H