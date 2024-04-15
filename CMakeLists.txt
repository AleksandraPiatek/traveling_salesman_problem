cmake_minimum_required(VERSION 3.26)
project(traveling_salesman_problem)

set(CMAKE_CXX_STANDARD 17)

add_executable(traveling_salesman_problem application.cpp
        tools/fileReader.cpp
        tools/fileReader.h
        tools/costMatrix.cpp
        tools/costMatrix.h
        algorithms/greedyApproach.cpp
        algorithms/greedyApproach.h
        algorithms/bruteForce.cpp
        algorithms/bruteForce.h
        algorithms/dynamicProgramming.cpp
        algorithms/dynamicProgramming.h
        heuristicAlgorithms/simulatedAnnealing.cpp
        heuristicAlgorithms/simulatedAnnealing.h
        heuristicAlgorithms/geneticAlgorithm.cpp
        heuristicAlgorithms/geneticAlgorithm.h)
