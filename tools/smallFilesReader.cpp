#include "smallFilesReader.h"
#include <fstream>

costMatrix smallFilesReader::read(const std::string& fileName) {
    string filePath = "../files/" + fileName;
    std::fstream file(filePath);
    if(file.is_open()) {
        int size;
        file >> size;                                // reading the first line with amount of cities
        costMatrix newMatrix(size);
        int data;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> data;
                newMatrix.add(i, j, data); // filling newMatrix with data from the file
            }
        }
        file.close();
        return newMatrix;
    }

    std::cout << "There is no such file"<< std::endl;
    return *new costMatrix ;
}