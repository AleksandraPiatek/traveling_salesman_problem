#ifndef TRAVELING_SALESMAN_PROBLEM_SMALLFILESREADER_H
#define TRAVELING_SALESMAN_PROBLEM_SMALLFILESREADER_H

#include <string>
#include "costMatrix.h"
using namespace std;

class smallFilesReader {
public:
    costMatrix read(const std::string& fileName);
};


#endif //TRAVELING_SALESMAN_PROBLEM_SMALLFILESREADER_H
