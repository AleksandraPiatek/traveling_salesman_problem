#include "greedyApproach.h"
#include <iostream>

int* greedyApproach::greedyApproachAlgorithm(int amountOfVertices, costMatrix matrix) {
    int currentVertex, pathCost = 0;
    bool visitedVertices[amountOfVertices];
    for(int i=0; i<amountOfVertices; i++) visitedVertices[i] = false;
    int *results = new int[amountOfVertices+1];
    for(int i=0; i<amountOfVertices+1; i++) results[i] = -1;

    currentVertex = 0;
    results[0]= currentVertex;
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

    pathCost+=matrix.getCost(currentVertex, results[0]);
    results[amountOfVertices] = pathCost;
    return results;
}
