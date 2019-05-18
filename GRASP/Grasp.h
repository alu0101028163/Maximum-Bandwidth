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


    /**
     * labeling is a vector representing the label value for each node,
     * knowing that labels lower or equal to zero cannot exists we check
     * if the label value in the node position is different than zero, which is
     * the value it was initialized with.
     * @param  node
     * @param  labeling 
     * @return
     */
    bool isVisited(int node, std::vector<int>& labeling);


    /**
     * It returns a random value from a vector of integers representing labels.
     * @param  labels
     * @return
     */
    int getRandomLabel(std::vector<int>& labels);

    /**
     * It returns a random value from a list of integers representing labels.
     * @param  labels
     * @return
     */
    int getRandomLabel(std::list<int>& labels);

}
