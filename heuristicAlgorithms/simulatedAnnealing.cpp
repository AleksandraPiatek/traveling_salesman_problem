#include "simulatedAnnealing.h"
#include "../tools/timeCounter.h"
#include <windows.h>
#include <iomanip>
#include <random>

void simulatedAnnealing::simulatedAnnealingAlgorithm(costMatrix matrix, int stopCondition){
    timeCounter timeCounter;
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = timeCounter.read_QPC();
    int *temporaryTable;
    temporaryTable = greedyApproach.greedyApproachAlgorithm(matrix.getSize(), matrix);
    minPathCost = temporaryTable[matrix.getSize()];
    minPath = new int[matrix.getSize()];
    for (int i = 0; i < matrix.getSize(); i++) minPath[i] = temporaryTable[i];
    delete[] temporaryTable;
    temperature = 45.0*matrix.getSize();
    float a = 0.99;

    while(((elapsed = (timeCounter.read_QPC()-start)/frequency)<stopCondition) || temperature==0)  {
        //generate random solution
        int randomSolutionCost= INT_MAX;
        int* randomPath = new int[matrix.getSize()];
        for(int i=0; i<matrix.getSize(); i++) randomPath[i]=-1;

        if(randomSolutionCost < minPathCost){
            minPathCost = randomSolutionCost;
            minPath = randomPath;
        }
        else{
            double randomNumber;
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<> dist(0, 1);
            randomNumber = dist(gen);
            if(randomNumber<=computeProbability(randomSolutionCost, minPathCost)){
                minPathCost = randomSolutionCost;
                minPath = randomPath;
            }
        }
        temperature = a*temperature;
        delete[] randomPath;
    }

    std::cout << "Time [s] = " << std::fixed << std::setprecision(3) << (float)elapsed << std::endl;
    std::cout << "Time [ms] = " << std::setprecision(0) << (1000.0 * elapsed)  << std::endl;
    std::cout << "Time [us] = " << std::setprecision(0) << (1000000.0 * elapsed) << std::endl;

}

double simulatedAnnealing::computeProbability(int newCost, int oldCost ) {
    return exp(-(newCost-oldCost)/temperature);
}
