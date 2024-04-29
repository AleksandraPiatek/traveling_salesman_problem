#include "simulatedAnnealing.h"
#include "../tools/timeCounter.h"
#include <windows.h>
#include <iomanip>
#include <random>
#include <cmath>

int * simulatedAnnealing::simulatedAnnealingAlgorithm(costMatrix matrix, int stopCondition, float inputA){
    timeCounter timeCounter;

    minPathCost = INT_MAX;
    long long int frequency, start, elapsed;

    int *temporaryTable;
    int firstVertexValue, secondVertexValue;

    currentPath = new int[matrix.getSize()];
    minPath = new int[matrix.getSize()];

    int firstIndexToSwap, secondIndexToSwap;
    int randomSolutionCost;

    float a = inputA;
    if(inputA ==0) {
        a = 0.9999795;
        if (matrix.getSize() == 48) a = 0.99999835;
        else if (matrix.getSize() == 171) a = 0.999993;
    }

    std::vector<int>changeOfTemp;
    std::vector<long long int>timeOfChangeOfTemp;

    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = timeCounter.read_QPC();

    temporaryTable = greedyApproach.greedyApproachAlgorithm(matrix.getSize(), matrix);
    currentPathCost = temporaryTable[matrix.getSize()];
    for (int i = 0; i < matrix.getSize(); i++) {
        currentPath[i] = temporaryTable[i];
        minPath[i] = temporaryTable[i];
    }
    delete[] temporaryTable;
    temperature = 30.0*matrix.getSize();

    while(((elapsed = (timeCounter.read_QPC()-start)/frequency)<stopCondition)){
        if(temperature == 0) break;
        for(int k = 0; k<matrix.getSize(); k++) {
            int *randomPath = new int[matrix.getSize()];
            for (int i = 0; i < matrix.getSize(); i++) randomPath[i] = currentPath[i];

            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, matrix.getSize() - 1);
            firstIndexToSwap = dist(gen);
            secondIndexToSwap = dist(gen);

            while (firstIndexToSwap == secondIndexToSwap) {
                firstIndexToSwap = dist(gen);
                secondIndexToSwap = dist(gen);
            }

            firstVertexValue = randomPath[firstIndexToSwap];
            secondVertexValue = randomPath[secondIndexToSwap];
            randomPath[firstIndexToSwap] = secondVertexValue;
            randomPath[secondIndexToSwap] = firstVertexValue;

            randomSolutionCost = computeCost(randomPath, matrix);

            if (randomSolutionCost < currentPathCost) {
                currentPathCost = randomSolutionCost;
                for (int j = 0; j < matrix.getSize(); j++) currentPath[j] = randomPath[j];
                if(randomSolutionCost< minPathCost){
                    minPathCost = randomSolutionCost;
                    for (int j = 0; j < matrix.getSize(); j++) minPath[j] = randomPath[j];
                }
            } else {
                double randomNumber;
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_real_distribution<> dist(0, 1);
                randomNumber = dist(gen);
                if (randomNumber <= computeProbability(randomSolutionCost, currentPathCost)) {
                    currentPathCost = randomSolutionCost;
                    for (int j = 0; j < matrix.getSize(); j++) currentPath[j] = randomPath[j];

                } else {
                    randomSolutionCost = currentPathCost;
                    for (int j = 0; j < matrix.getSize(); j++) randomPath[j] = currentPath[j];
                }
            }
            delete[] randomPath;
        }
        temperature = a*temperature;
    }
    std::cout << "Cost: " << minPathCost << std::endl;

    std::cout << "Path: " << std::endl;
    for(int i=0; i<matrix.getSize(); i++) std:: cout << minPath[i] << " ";
    std::cout << minPath[0];
    std::cout  <<std::endl;

    delete[] currentPath;
    return minPath;
}

double simulatedAnnealing::computeProbability(int newCost, int oldCost) {
    return exp((oldCost-newCost)/temperature);
}

int simulatedAnnealing::computeCost(int* path, costMatrix matrix) {
    int cost=0;
    for(int i=0;i<matrix.getSize()-1; i++){
        cost+=(matrix.getCost(path[i], path[i+1]));
    }
    cost+=(matrix.getCost(path[matrix.getSize()-1], path[0]));
    return cost;
}
