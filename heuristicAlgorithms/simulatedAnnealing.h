#ifndef TASKTWOPEA_SIMULATEDANNEALING_H
#define TASKTWOPEA_SIMULATEDANNEALING_H

#include "../tools/costMatrix.h"

class simulatedAnnealing {
public:
    void simulatedAnnealingAlgorithm(costMatrix matrix, int stopCondition);
    double computeProbability(int, int);
};


#endif //TASKTWOPEA_SIMULATEDANNEALING_H
