#include <iostream>
#include "costMatrix.h"

void costMatrix::initialize(int size){
    if(amountOfVertexes!=0){
        for(int i=0; i<amountOfVertexes; i++){
            delete matrix[i];
        }
        delete []matrix;
    }

    amountOfVertexes = size;
    matrix = new int*[amountOfVertexes];
    for(int i=0; i<amountOfVertexes; i++){
        matrix[i]= new int[amountOfVertexes];   //allocating memory space for new matrix
    }
}

void costMatrix::add(int column, int row, int data) {
    matrix[column][row] = data;
}

void costMatrix::print() {
    for (int i = 0; i < amountOfVertexes; i++) {
        for (int j = 0; j < amountOfVertexes; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int costMatrix::getSize() {
    return amountOfVertexes;
}

int costMatrix::getCost(int column, int row) {
    return matrix[column][row];
}