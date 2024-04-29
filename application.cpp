#include <iostream>
#include "heuristicAlgorithms/geneticAlgorithm.h"
#include "tools/bigFilesReader.h"
#include "heuristicAlgorithms/simulatedAnnealing.h"
#include "algorithms/bruteForce.h"
#include "algorithms/dynamicProgramming.h"
#include "tools/smallFilesReader.h"

costMatrix matrix;

void bruteForceHandler(){
    smallFilesReader reader;
    bruteForce bruteForce;
    char choice = -1;
    std::string fileName;

    while(choice!='0'){
        char cities = -1;
        while(fileName.empty()) {
            system("cls");
            std::cout << "Please choose amount of cities: " << std::endl;
            std::cout << "1. 4 " << std::endl;
            std::cout << "2. 6 " << std::endl;
            std::cout << "3. 10 " << std::endl;
            std::cout << "4. 12 " << std::endl;
            std::cout << "5. 13" << std::endl;
            std::cin >> cities;
            switch (cities) {
                case '1':
                    fileName = "tsp_4.txt";
                    break;
                case '2':
                    fileName = "tsp_6.txt";
                    break;
                case '3':
                    fileName = "tsp_10.txt";
                    break;
                case '4':
                    fileName = "tsp_12.txt";
                    break;
                case '5':
                    fileName = "tsp_13.txt";
                    break;
            }
        }
        matrix = reader.read(fileName);
        fileName = "";
        std::cout << "Matrix: " << std::endl;
        matrix.print();

        bruteForce.bruteForceAlgorithm(matrix);
        system("PAUSE");

        system("cls");

        std::cout << "Press any key and ENTER to execute algorithm again or 0 to exit" << std::endl;
        std::cin >> choice;
    }
}

void dynamicProgrammingHandler(){
    smallFilesReader reader;
    dynamicProgramming dynamicProgramming;
    char choice = -1;
    std::string fileName;

    while(choice!='0'){
        char cities = -1;
        while(fileName.empty()) {
            system("cls");
            std::cout << "Please choose amount of cities: " << std::endl;
            std::cout << "1. 10 " << std::endl;
            std::cout << "2. 12 " << std::endl;
            std::cout << "3. 13" << std::endl;
            std::cout << "4. 14" << std::endl;
            std::cout << "5. 15" << std::endl;
            std::cout << "6. 17" << std::endl;
            std::cout << "7. 18" << std::endl;
            std::cout << "8. 19" << std::endl;
            std::cout << "9. 20" << std::endl;
            std::cin >> cities;
            switch (cities) {
                case '1':
                    fileName = "tsp_10.txt";
                    break;
                case '2':
                    fileName = "tsp_12.txt";
                    break;
                case '3':
                    fileName = "tsp_13.txt";
                    break;
                case '4':
                    fileName = "tsp_14.txt";
                    break;
                case '5':
                    fileName = "tsp_15.txt";
                    break;
                case '6':
                    fileName = "tsp_17.txt";
                    break;
                case '7':
                    fileName = "tsp_18.txt";
                    break;
                case '8':
                    fileName = "tsp_19.txt";
                    break;
                case '9':
                    fileName = "tsp_20.txt";
                    break;
            }
        }
        matrix = reader.read(fileName);
        fileName = "";
        std::cout << "Matrix: " << std::endl;
        matrix.print();

        dynamicProgramming.dynamicProgrammingAlgorithm(matrix);
        system("PAUSE");

        system("cls");

        std::cout << "Press any key and ENTER to execute algorithm again or 0 to exit" << std::endl;
        std::cin >> choice;
    }
}

void geneticAlgorithmHandler(){
    int stopCondition=120;
    bigFilesReader fileHandler;
    geneticAlgorithm geneticAlgorithm;
    char choice = -1, methodOfMutation, cities;
    std::string fileName;
    float crossoverFactor=0.8, mutationFactor = 0.01 ;
    int  bestResult;

    while(choice!='0'){
        while(fileName.empty()) {
            system("cls");
            std::cout << "Please choose amount of cities: " << std::endl;
            std::cout << "1. 47 " << std::endl;
            std::cout << "2. 170 " << std::endl;
            std::cout << "3. 403 " << std::endl;
            std::cin >> cities;
            switch (cities) {
                case '1':
                    fileName = "ftv47.atsp";
                    bestResult = 1776;
                    break;
                case '2':
                    fileName = "ftv170.atsp";
                    bestResult = 2755;
                    break;
                case '3':
                    fileName = "ftv47.atsp";
                    bestResult = 2465;
                    break;
            }
        }
        matrix = fileHandler.readMatrixFile(fileName);
        fileName = "";

        std::cout << "Please enter stop condition in seconds: (recommended 120, min 15 to see results)" << std::endl;
        std::cin>>stopCondition;

        bool validInput = false;
        while (!validInput) {
            cout << "Please enter mutation factor: (between 0 and 1, recommended 0.01) " << endl;
            if (!(cin >> mutationFactor)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid floating-point number." << endl;
            } else if (mutationFactor <= 0 || mutationFactor >= 1) {
                cout << "Please enter a number between 0 and 1." << endl;
            } else {
                validInput = true;
            }
        }

        validInput = false;
        while (!validInput) {
            cout << "Please enter crossover factor: (between 0 and 1, recommended 0.8) " << endl;
            if (!(cin >> crossoverFactor)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid floating-point number." << endl;
            } else if (crossoverFactor <= 0 || crossoverFactor >= 1) {
                cout << "Please enter a number between 0 and 1." << endl;
            } else {
                validInput = true;
            }
        }

        while(methodOfMutation != '1' && methodOfMutation != '2') {
            std::cout << "Please choose method of mutation:" << std::endl;
            std::cout << "1. Inversion mutation" << std::endl;
            std::cout << "2. Swap mutation" << std::endl;
            std::cin >> methodOfMutation;
            if (methodOfMutation != '1' && methodOfMutation != '2') {
                methodOfMutation = '1';
                std::cout << "Chosen default method (inversion mutation)" << " ";
            }
        }
        std::cout << "The best known result: " << bestResult << std::endl;

        geneticAlgorithm.geneticAlgorithmExecution(stopCondition, matrix, crossoverFactor, mutationFactor, methodOfMutation, "file");
        system("PAUSE");

        methodOfMutation = '0';

        system("cls");
        std::cout << "Press any key and ENTER to execute algorithm again or 0 to exit" << std::endl;
        std::cin >> choice;
    }
}

void simulatedAnnealingHandler(){
    bigFilesReader reader;
    int stopCondition, bestResult;
    simulatedAnnealing simulatedAnnealing;
    char choice = -1;
    char cities;
    std::string fileName;
    float temperatureChangeFactor=-1;

    while(choice!='0'){
        while(fileName.empty()) {
            system("cls");
            std::cout << "Please choose amount of cities: " << std::endl;
            std::cout << "1. 47 " << std::endl;
            std::cout << "2. 170 " << std::endl;
            std::cout << "3. 403 " << std::endl;
            std::cin >> cities;
            switch (cities) {
                case '1':
                    fileName = "ftv47.atsp";
                    bestResult = 1776;
                    break;
                case '2':
                    fileName = "ftv170.atsp";
                    bestResult = 2755;
                    break;
                case '3':
                    fileName = "ftv47.atsp";
                    bestResult = 2465;
                    break;
            }
        }
        matrix = reader.readMatrixFile(fileName);
        fileName = "";

        std::cout << "Please enter stop condition in seconds (recommended 120)" << std::endl;
        std::cin>>stopCondition;

        bool validInput = false;
        while (!validInput) {
            cout << "Please enter temperature change factor: (between 0 and 1, recommended 0.99999835) " << endl;
            if (!(cin >> temperatureChangeFactor)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid floating-point number." << endl;
            } else if (temperatureChangeFactor <= 0 || temperatureChangeFactor >= 1) {
                cout << "Please enter a number between 0 and 1." << endl;
            } else {
                validInput = true;
            }
        }
        std::cout << "The best known result: " << bestResult << std::endl;

        simulatedAnnealing.simulatedAnnealingAlgorithm(matrix, stopCondition, temperatureChangeFactor);
        system("PAUSE");

        temperatureChangeFactor = -1;

        system("cls");

        std::cout << "Press any key and ENTER to execute algorithm again or 0 to exit" << std::endl;
        std::cin >> choice;
    }
}

int main() {
   char choice = -1;
   while(choice!='0'){
       system("cls");
       std::cout << "Please choose an algorithm:" << std::endl;
       std::cout << "1. Brute force" << std::endl;
       std::cout << "2. Dynamic programming" << std::endl;
       std::cout << "3. Genetic algorithm" << std::endl;
       std::cout << "4. Simulated annealing" << std::endl;
       std::cout << "0. Exit" << std::endl;
       std::cin >> choice;
       switch (choice) {
           case '1':
               bruteForceHandler();
               break;
           case '2':
               dynamicProgrammingHandler();
               break;
           case '3':
               geneticAlgorithmHandler();
               break;
           case '4':
               simulatedAnnealingHandler();
               break;
           case '0':
               break;
       }
   }
    return 0;
}
