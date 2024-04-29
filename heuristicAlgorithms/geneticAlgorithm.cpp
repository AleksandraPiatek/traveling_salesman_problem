#include <ntdef.h>
#include <profileapi.h>
#include "geneticAlgorithm.h"
#include "../tools/timeCounter.h"
#include <iostream>
#include <random>
#include <climits>

void geneticAlgorithm::geneticAlgorithmExecution(int stopCondition, costMatrix matrix, float crossoverFactor, float mutationFactor, char mutationMethod, std::string fileName) {
    long long int frequency, start;
    timeCounter timeCounter;
    minCost = INT_MAX;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = timeCounter.read_QPC();
    tempMinPath = new int[matrix.getSize()];
    tempMinPath[0] = -1;

    populationSize = 10*matrix.getSize();
    populationRandomizer(matrix.getSize(), matrix);

    parentsIndexes = new int[2];
    parentsIndexes[0]=-1;
    parentsIndexes[1]=-1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    while (((timeCounter.read_QPC() - start) / frequency) < stopCondition) {
        int** newPopulation = new int*[populationSize];
        for(int i = 0; i<populationSize; i++) newPopulation[i] = new int[matrix.getSize()];
        int bestIndex = findBestFromPopulation(matrix);
        for(int i = 0; i< matrix.getSize(); i++) {
            newPopulation[0][i] = population[bestIndex][i];
        }

        int index;
        for (index = 1; index <crossoverFactor*populationSize; index++) {
            //selection
            parentsIndexes[0] = -1;
            parentsIndexes[1] = -1;
            selectFromPopulation(0, matrix);
            selectFromPopulation(1, matrix);

            orderCrossover(population[parentsIndexes[0]], population[parentsIndexes[1]], matrix);
            orderCrossover(population[parentsIndexes[1]], population[parentsIndexes[0]], matrix);
            for (int i = 0; i < matrix.getSize(); i++) {
                newPopulation[index][i] = tempMinPath[i];
            }
        }
        //filling newPopulation
        for (int j = index; j < populationSize; j++) {
            int pathToAdd = generateRandomInt(1, populationSize - 1);
            for (int i = 0; i < matrix.getSize(); i++) {
                newPopulation[j][i] = population[pathToAdd][i];
            }
        }
        for( int i = 0; i< populationSize; i++){
            delete[] population[i];

        }
        delete[] population;
        population = newPopulation;
        //mutation
        mutate(matrix.getSize(), mutationMethod, mutationFactor);
        if (calculateCost(findBestFromPopulation(matrix), matrix) < minCost) {
            minCost = calculateCost(findBestFromPopulation(matrix), matrix);
            minCostFoundTime = 1000 * (timeCounter.read_QPC() - start) / frequency;
        }
    }
    std::cout << "Result: " << minCost  << std::endl;
    std::cout << "Path: "  << std::endl;
    int index = findBestFromPopulation(matrix);
    for(int i = 0; i< matrix.getSize(); i++){
        std::cout << population[index][i] << " ";
    }
    std::cout << std::endl;

    delete[] parentsIndexes;
    for( int i = 0; i< populationSize; i++){
        delete[] population[i];
    }
    delete[] population;
    delete[] tempMinPath;
}

void geneticAlgorithm::populationRandomizer(int matrixSize, costMatrix matrix) {
    population = new int*[populationSize];
    for(int i = 0; i<populationSize; i++) population[i] = new int[matrixSize];

    for(int i = 0; i<populationSize; i++) {
        bool taken[matrixSize];
        for (int k = 0; k < matrixSize; k++) taken[k] = false;

        for(int j = 0; j<matrixSize; j++){
            int randomNumber;
            do{
                randomNumber = generateRandomInt(0, matrixSize - 1);
            }
            while(taken[randomNumber]);
            taken[randomNumber] = true;
            population[i][j] = randomNumber;
        }
    }
}

void geneticAlgorithm::selectFromPopulation(int index, costMatrix matrix){
    //tournament selection
    int k = 3;
    int selectedChromosomesIndexes[k];  //random chromosomes
    int randomNumber;
    for(int i = 0; i<k; i++) {
        randomNumber = generateRandomInt(0,populationSize-1);
        if(parentsIndexes[0]!=-1){
            while(randomNumber==parentsIndexes[0]) randomNumber = generateRandomInt(0,populationSize-1);
        }
        selectedChromosomesIndexes[i]=randomNumber;
    }

    //tournament
    int minIndex = selectedChromosomesIndexes[0];
    int tempMinPathCost = calculateCost(selectedChromosomesIndexes[0], matrix);
    for(int i = 1; i<k; i++){
        int tempCost = calculateCost(selectedChromosomesIndexes[i], matrix);
        if(tempCost<tempMinPathCost){
            minIndex = selectedChromosomesIndexes[i];
            tempMinPathCost=tempCost;
        }
    }
    parentsIndexes[index]= minIndex;
}

int geneticAlgorithm::calculateCost(int pathIndex, costMatrix matrix) {
    int cost=0;
    for(int i=0;i<matrix.getSize()-1; i++){
        cost+=(matrix.getCost(population[pathIndex][i], population[pathIndex][i+1]));
    }
    cost+=(matrix.getCost(population[pathIndex][matrix.getSize()-1], population[pathIndex][0]));
    return cost;
}

void geneticAlgorithm::orderCrossover(int* firstParent, int* secondParent, costMatrix matrix) {
    int* child = new int[matrix.getSize()];
    int startOfSection = generateRandomInt(0,matrix.getSize()-2);
    int endOfSection = generateRandomInt(startOfSection,matrix.getSize()-1);
    bool takenVertices[matrix.getSize()];

    for(int i = 0; i<matrix.getSize(); i++) {
        if( i >= startOfSection && i<=(endOfSection)){
            child[i] = firstParent[i];
        }
        else{
            child[i] = -1;
        }
    }

    for(int i = 0; i<matrix.getSize(); i++) takenVertices[i] = false;
    for(int j = startOfSection; j<=endOfSection; j++) takenVertices[firstParent[j]] = true;

    int j = (endOfSection+1)%matrix.getSize();
    for(int i = (endOfSection+1)%matrix.getSize(); i!= endOfSection; i= (i+1)%matrix.getSize()){
        if(!takenVertices[secondParent[i]]){
            while(true){
                if(child[j] == -1){
                    child[j]=secondParent[i];
                    j= (j+1)%matrix.getSize();
                    break;
                }
            }
        }
    }
    if(!takenVertices[secondParent[endOfSection]]){
        while(true){
            if(child[j] == -1){
                child[j]=secondParent[endOfSection];
                break;
            }
        }
    }

    if(tempMinPath[0] != -1) {
        if (calculateCostFromPath(child, matrix) < calculateCostFromPath(tempMinPath, matrix)) {
            for (int i = 0; i < matrix.getSize(); i++) {
                tempMinPath[i] = child[i];
            }
        }
    }
    else{
        for (int i = 0; i < matrix.getSize(); i++) {
            tempMinPath[i] = child[i];
        }
    }

    delete[] child;
}

void geneticAlgorithm::mutate(int matrixSize, char mutationMethod, float mutationFactor) {
    if(mutationMethod == '1'){
        inversionMutation(matrixSize, mutationFactor);
    }else{
        swapMutation(matrixSize, mutationFactor);
    }
}

int geneticAlgorithm::generateRandomInt(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(gen);
}

int geneticAlgorithm::calculateCostFromPath(int* path, costMatrix matrix) {
    int cost=0;
    for(int i=0;i<matrix.getSize()-1; i++){
        cost+=(matrix.getCost(path[i], path[i+1]));
    }
    cost+=(matrix.getCost(path[matrix.getSize()-1], path[0]));
    return cost;
}

int geneticAlgorithm::findBestFromPopulation(costMatrix matrix){
    int tempMinPathCost = calculateCost(0, matrix);
    int tempMinPathCostIndex = 0;
    for(int i = 1; i<populationSize; i++) {
        int tempCost = calculateCost(i,matrix);
        if (tempCost < tempMinPathCost) {
            tempMinPathCost = tempCost;
            tempMinPathCostIndex = i;
        }
    }
    return tempMinPathCostIndex;
}

void geneticAlgorithm::inversionMutation(int matrixSize, float mutationFactor) {
    for(int i = 0; i< populationSize*mutationFactor; i++) {
        int pathToMutateIndex = generateRandomInt(1, populationSize-1);
        int beginning = generateRandomInt(0, matrixSize-2);
        int end = generateRandomInt(beginning+1, matrixSize-1);
        int counter = end;
        int temp;

        for(int j = beginning; j<=beginning+((end-beginning)/2); j++){
            temp = population[pathToMutateIndex][counter];
            population[pathToMutateIndex][counter] = population[pathToMutateIndex][j];
            population[pathToMutateIndex][j] = temp;
            counter--;
        }
    }
}

void geneticAlgorithm::swapMutation(int matrixSize, float mutationFactor) {
    for (int i = 0; i < populationSize * mutationFactor; i++) {
        int pathToMutateIndex = generateRandomInt(1, populationSize - 1);

        int firstVertexIndex = generateRandomInt(0, matrixSize - 2);
        int secondVertexIndex = generateRandomInt(firstVertexIndex + 1, matrixSize - 1);

        int firstVertexValue = population[pathToMutateIndex][firstVertexIndex];
        int secondVertexValue = population[pathToMutateIndex][secondVertexIndex];

        population[pathToMutateIndex][firstVertexIndex] = secondVertexValue;
        population[pathToMutateIndex][secondVertexIndex] = firstVertexValue;
    }
}