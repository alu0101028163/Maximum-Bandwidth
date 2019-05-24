
#ifndef CLION_MULTISTART_MULTISTART_H
#define CLION_MULTISTART_MULTISTART_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../AntiBandwidth/AntiBandwidth.h"

namespace MultiStart{

    /**
    * Generates a random solution.
    * @param numVertex Indicates the size of the vector that will be filled with random values.
    */
    AntiBandwidth::solutionT randomVector(int numVertex);


    void swap(int i, int j , std::vector<int>& label);
    int evaluateMovement(int i, int j , std::vector<int> label, const std::vector< std::vector<short int> >& graph);
    void doubleExchange(std::vector<int>&  currentSolution, const std::vector<std::vector<short int>>& graph);
    void simpleExchange(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph);
    void cyclicAdjExchange(std::vector<int>& currentSolution,const std::vector<std::vector<short int>>& graph);

    /**
    * It's a switch to carry out the neighborhood structure that is passed by parameter.
    * @param Is the value that determines in the switch the structure that has been selected.
    * @currentSolution It's the vector that contains the random solution calculated in the "randomVector" function.
    * @adjMatrix Disperse matrix that constains the graph of the instance.
    */
    void calculateNeighborhood(int structureNum, std::vector<int>& curretSolution, std::vector<std::vector<short int> >& adjMatrix);


    /**
    * Function that contains the Multi Star procedure.
    * @param structure Is the same parameter as "structureNum" in calculateNeighborhood function.
    * @param adjMatrix Disperse matrix that constains the graph of the instance.
    * @param repetitions Number of iterations for the internal buble of the function.
    */
    std::vector<int> multiStart(int structure, std::vector<std::vector<short int>>& adjMatrix, int repetitions);
}

#endif //CLION_MULTISTART_MULTISTART_H
