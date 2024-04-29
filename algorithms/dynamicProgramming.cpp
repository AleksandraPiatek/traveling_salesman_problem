#include "dynamicProgramming.h"
#include <climits>
#include "dynamicProgramming.h"
#include "iostream"

void dynamicProgramming::dynamicProgrammingAlgorithm(costMatrix matrix) {
    mSize = matrix.getSize();
    nextVertexMatrix = new int*[mSize];          //allocating memory space for nextVertexMatrix and atspResults
    atspResults = new int*[mSize];
    for(int i=0; i<mSize; i++){
        nextVertexMatrix[i] = new int[(1 << mSize)];
        atspResults[i] = new int [(1 << mSize)];
        for(int j = 0; j<(1<<mSize); j++){
            nextVertexMatrix[i][j] = -1;
            atspResults[i][j]= -1;
        }
    }

    std::cout <<  atsp(0, 1, matrix) <<std::endl;

    int* path = new int[mSize];
    int pathSize = 0, currentVertex = 0, currentMask = 1;
    do {                                       //retracing the minimum cost path
        path[pathSize] = currentVertex;
        pathSize = pathSize + 1;
        currentVertex = nextVertexMatrix[currentVertex][currentMask];
        currentMask = currentMask | (1 << currentVertex);
    } while(currentVertex != -1);

    for(int i=0; i<mSize; i++) {              //printing the minimum cost path
        std::cout << path[i] << " -> ";
    }
    std::cout << "0" << std::endl;

    delete []path;                            //deleting used structures
    for(int i=0; i<mSize; i++){
        delete []nextVertexMatrix[i];
        delete []atspResults[i];
    }
    delete []atspResults;
    delete []nextVertexMatrix;
}

int dynamicProgramming::atsp(int vertex, int mask, costMatrix matrix) {
    if(mask==((1<<mSize)-1)){                           //checking if all the vertices had been visited
        return matrix.getCost(vertex, 0);
    }
    if(atspResults[vertex][mask] != -1){                //checking if there has been a result already computed for current vertex and mask
        return atspResults[vertex][mask];
    }
    int minCost=INT_MAX;
    for(int i=0; i<mSize; i++) {
        if ((mask & (1 << i)) == 0 ) {                  //checking if vertex i had already been visited
            int newMinCost = matrix.getCost(vertex, i) + atsp(i, mask | (1<<i), matrix);
            if(newMinCost<minCost){
                nextVertexMatrix[vertex][mask] = i;
                minCost = newMinCost;
            }
        }
    }
    atspResults[vertex][mask]= minCost;
    return minCost;
}
