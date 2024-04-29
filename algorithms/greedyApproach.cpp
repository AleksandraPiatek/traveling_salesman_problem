#include "greedyApproach.h"
#include <random>
#include <iostream>

int* greedyApproach::greedyApproachAlgorithm(int amountOfVertices, costMatrix matrix) {
    int currentVertex, pathCost = 0;
    bool visitedVertices[amountOfVertices];
    for(int i=0; i<amountOfVertices; i++) visitedVertices[i] = false;
    int *results = new int[amountOfVertices+1];
    for(int i=0; i<amountOfVertices+1; i++) results[i] = -1;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, amountOfVertices-1);   //randomizing data in range (25,100)
    currentVertex = dist(gen);
    results[0]= currentVertex;
    std::cout << currentVertex << std::endl;
    visitedVertices[currentVertex] = true;
    int minValue, minVertex;
    for(int i=0; i<amountOfVertices-1; i++){
        minValue = INT_MAX;
        minVertex = -1;
        for(int j=0; j<amountOfVertices; j++){
            if(!visitedVertices[j] && j!=currentVertex){
                if(matrix.getCost(currentVertex, j)<minValue) {
                    minValue = matrix.getCost(currentVertex, j);
                    minVertex = j;
                }
            }
        }
        currentVertex = minVertex;
        results[i+1]=currentVertex;
        pathCost+=minValue;
        visitedVertices[minVertex] = true;
    }
    results[amountOfVertices] = pathCost;
    for(int i=0; i<amountOfVertices+1; i++) std::cout <<results[i] << " ";

    return results;
}
