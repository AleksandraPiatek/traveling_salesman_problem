#include <iostream>
#include <climits>
#include "bruteForce.h"

void bruteForce::bruteForceAlgorithm(costMatrix matrix){
    matrixSize = matrix.getSize();

    minCost = INT_MAX;
    temporaryMinPathCost = 0;

    temporaryPath = new int[matrixSize];
    path = new int[matrixSize];

    visitedVertices = new bool[matrixSize];
    for(int i=0; i<matrixSize; i++) visitedVertices[i]=false;

    pathSize = 0;
    temporaryPathSize = 0;

    atsp(0, matrix);

    if(pathSize<matrixSize){
        std::cout << "No path" << std::endl;
    }
    else {
        std::cout << minCost << std::endl;
        for(int i=0; i<pathSize; i++){
            std::cout << path[i] << " -> ";
        }
        std::cout << "0" <<std::endl;
    }

    delete []path;
    delete []temporaryPath;
    delete []visitedVertices;

}

void bruteForce::atsp(int vertex, costMatrix matrix) {
    temporaryPath[temporaryPathSize] = vertex;
    temporaryPathSize++;

    if(temporaryPathSize==matrixSize){
        if(matrix.getCost(vertex, 0) != -1) {
            temporaryMinPathCost += matrix.getCost(vertex, 0);
            if (temporaryMinPathCost < minCost) {
                minCost = temporaryMinPathCost;
                for(int j = 0; j<temporaryPathSize; j++){
                    path[j] = temporaryPath[j];
                }
                pathSize = temporaryPathSize;
            }
            temporaryMinPathCost -= matrix.getCost(vertex, 0);
        }
    }
    else{
        visitedVertices[vertex] = true;
        for(int i = 0; i<matrixSize; i++) {
            if (matrix.getCost(vertex, i) != -1) {
                if (!visitedVertices[i]) {
                    temporaryMinPathCost += matrix.getCost(vertex, i);
                    if(temporaryMinPathCost < minCost) atsp(i, matrix);
                    temporaryMinPathCost -= matrix.getCost(vertex, i);
                }
            }
        }
        visitedVertices[vertex] = false;
    }
    temporaryPathSize--;
    temporaryPath[temporaryPathSize] = -1;
}