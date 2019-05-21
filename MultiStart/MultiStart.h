
#ifndef CLION_MULTISTART_MULTISTART_H
#define CLION_MULTISTART_MULTISTART_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../AntiBandwidth/AntiBandwidth.h"

namespace MultiStart{
    AntiBandwidth::solutionT randomVector(int numVertex);
    void calculateNeighborhood(int structureNum, std::vector<int>& curretSolution, std::vector<std::vector<short int> >& adjMatrix);
    void swap(int i, int j , std::vector<int>& label);
    int evaluateMovement(int i, int j , std::vector<int> label, const std::vector< std::vector<short int> >& graph);
    void doubleExchange(std::vector<int>&  currentSolution, const std::vector<std::vector<short int>>& graph);
    void simpleExchange(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph);
    void cyclicAdjExchange(std::vector<int>& currentSolution,const std::vector<std::vector<short int>>& graph);

    std::vector<int> multiStart(int structure, std::vector<std::vector<short int>>& adjMatrix, int repetitions);
}

#endif //CLION_MULTISTART_MULTISTART_H
