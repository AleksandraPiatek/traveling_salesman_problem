#ifndef TASKTWOPEA_SIMULATEDANNEALING_H
#define TASKTWOPEA_SIMULATEDANNEALING_H

#include "../tools/costMatrix.h"
#include "../algorithms/greedyApproach.h"

class simulatedAnnealing {
    greedyApproach greedyApproach;
    int *minPath;
    int minPathCost;
    double temperature;
public:
    void simulatedAnnealingAlgorithm(costMatrix matrix, int stopCondition);
    double computeProbability(int, int);
};


#endif //TASKTWOPEA_SIMULATEDANNEALING_H
