//
// Created by basilio on 16/05/19.
//

#ifndef CLION_BASI2_GRASP_H
#define CLION_BASI2_GRASP_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GraphGenerator.h"

const int RCL_SIZE = 4;

namespace Grasp{

//===================================================
//              CONSTRUCTIVE PHASE
//===================================================

    std::vector<std::vector<short int>> fileRead(const std::string &filename, bool isDense);
    std::vector<short int> candidateList(std::vector<std::vector<short int>>& adjacencyMatrix);
    std::vector<short int> greedyFunction(std::vector<std::vector<short int>>& adjacencyMatrix,
                                          std::vector<short int>& candidateList, const std::string &filename );
    void candidatelistEraseElement(std::vector<short int>& auxVec, short int toDelete);

}

#endif //CLION_BASI2_GRASP_H
