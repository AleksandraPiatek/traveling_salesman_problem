#include <iostream>
#ifndef ZAD1_COSTMATRIX_H
#define ZAD1_COSTMATRIX_H

class costMatrix {
    int amountOfVertexes=0;
    int** matrix;
public:
    void initialize(int size);
    void add(int column, int row, int data);
    void print();
    int getSize();
    int getCost(int column, int row);

    costMatrix(){

    }
    explicit costMatrix(int newAmount){
        initialize(newAmount);
    }
    ~costMatrix() {
    }
};


#endif //ZAD1_COSTMATRIX_H