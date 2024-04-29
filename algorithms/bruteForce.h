#ifndef ZAD1_BRUTEFORCE_H
#define ZAD1_BRUTEFORCE_H
#include "../tools/costMatrix.h"

class bruteForce {
    int minCost, temporaryMinPathCost;
    int *path, *temporaryPath;
    int pathSize, temporaryPathSize;
    bool *visitedVertices;
    int matrixSize;
public:
    void bruteForceAlgorithm(costMatrix);
    void atsp(int vertex, costMatrix);
};


#endif //ZAD1_BRUTEFORCE_H
