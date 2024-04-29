#ifndef TRAVELING_SALESMAN_PROBLEM_BIGFILESREADER_H
#define TRAVELING_SALESMAN_PROBLEM_BIGFILESREADER_H

#include <string>
#include "costMatrix.h"

class bigFilesReader {
    costMatrix readMatrixFile(std::string fileName);

};


#endif //TRAVELING_SALESMAN_PROBLEM_BIGFILESREADER_H
