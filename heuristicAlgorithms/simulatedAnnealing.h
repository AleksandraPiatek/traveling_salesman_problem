#ifndef TASKTWOPEA_SIMULATEDANNEALING_H
#define TASKTWOPEA_SIMULATEDANNEALING_H

#include "../tools/costMatrix.h"
#include "../algorithms/greedyApproach.h"

class simulatedAnnealing {
    greedyApproach greedyApproach;
    int *currentPath, *minPath;
    int currentPathCost, minPathCost = INT_MAX;
    float temperature;
public:
    int * simulatedAnnealingAlgorithm(costMatrix matrix, int stopCondition, float inputA);
    double computeProbability(int, int);
    int computeCost(int *path, costMatrix matrix);
};


#endif //TASKTWOPEA_SIMULATEDANNEALING_H
