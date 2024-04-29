#include "bigFilesReader.h"
#include <fstream>

costMatrix bigFilesReader::readMatrixFile(std::string fileName) {
    std::string pathName = "../files/" + fileName;
    std::fstream file(pathName);
    if(file.is_open()) {
        int size, data;
        std::string temporary;
        int max = 9;
        if( fileName == "rbg403.atsp") max = 10;
        for(int i =0; i<max; i++) file >> temporary;

        file >> size;
        costMatrix newMatrix(size);

        for(int i=0; i<5; i++) file >> temporary;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> data;
                newMatrix.add(i, j, data); // filling newMatrix with data from the file
            }
        }
        file.close();
        return newMatrix;
    }
    return *new costMatrix;
}
