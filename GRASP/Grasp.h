#pragma once
#include <vector>
#include <list>
#include <stdlib.h>
#include <algorithm>




namespace Grasp{

    const float PERCENTAGE = 0.6;

    void constructGreedyRandomizedSolution(std::vector< std::vector<short int> >& graph, std::vector<int>& solutionElements);
    void constructSolution(int actualNode, std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling);
    int calculateLabel(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);
    std::vector<int>& calculateCandidateList(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);
    int calculateCardinality(std::list<int>& remainingLabels);
    bool isVisited(int node, std::vector<int>& labeling);
    int getRandomLabel(std::vector<int>& labels);
    int getRandomLabel(std::list<int>& labels);

}
