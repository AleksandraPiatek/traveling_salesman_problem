#include "bigFilesReader.h"
#include <fstream>

costMatrix bigFilesReader::readMatrixFile(std::string fileName) {
    int maxLinesToSkip = 9;
    if(fileName == "rbg403.atsp") maxLinesToSkip = 10;
    std::fstream file(fileName);
    if(file.is_open()) {
        int size, data;
        std::string temporary;
        for(int i = 0; i < maxLinesToSkip; i++)
            std::getline(file, temporary);

        file >> size;
        costMatrix newMatrix(size);

        for(int i = 0; i < 5; i++)
            file >> temporary;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> data;
                newMatrix.add(i, j, data); // filling newMatrix with data from the file
            }
        }
        file.close();
        return newMatrix;
    }
    return costMatrix();
}
