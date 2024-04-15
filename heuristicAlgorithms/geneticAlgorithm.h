#ifndef ZAD3_GENETICALGORITHM_H
#define ZAD3_GENETICALGORITHM_H

#include <iostream>
#include "../tools/costMatrix.h"

class geneticAlgorithm {
public:
    void geneticAlgorithmExecution(int stopCondition, costMatrix matrix, float crossoverFactor, float mutationFactor, char mutationMethod, std::string fileName);
    void populationRandomizer(int matrixSize, costMatrix);
    void selectFromPopulation(int, costMatrix);
    int calculateCost(int, costMatrix);
    int calculateCostFromPath(int *, costMatrix);
    int findBestFromPopulation(costMatrix);
    void orderCrossover(int*, int*, costMatrix);
    void mutate(int, char mutationMethod, float mutationFactor);
    void inversionMutation(int matrixSize, float mutationFactor);
    void swapMutation(int matrixSize, float mutationFactor);
    int generateRandomInt(int, int);
};


#endif //ZAD3_GENETICALGORITHM_H

