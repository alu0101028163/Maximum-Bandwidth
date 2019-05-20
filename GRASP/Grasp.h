#pragma once
#include "../AntiBandwidth/AntiBandwidth.h"

#include <random>
#include <ctime>
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <algorithm>


namespace Grasp{

    extern float PERCENTAGE;

    void setPercentage(float percentage);
    std::vector<int> grasp(std::vector< std::vector<short int> >& graph, int maxIterations, int objectiveValue);
    void updateSolution(int& bestSolutionValue, std::vector<int>& bestSolution, std::vector<int>& currentSolution, std::vector< std::vector<short int> >& graph);
    void swap(int i, int j , std::vector<int>& label);
    int evaluateMovement(int i, int j , std::vector<int> label, std::vector< std::vector<short int> >& graph);
    void localSearch(std::vector<int>& currentSolution, std::vector< std::vector<short int> >& graph);

    /**
     * Wrapper function for the construction of a greedy randomized solution that initializes the data structures and recursive
     * depth-first search algorithm.
     * @param  graph            [description]
     * @param  solutionElements [description]
     * @return                  [description]
     */
    std::vector<int> constructGreedyRandomizedSolution(std::vector< std::vector<short int> >& graph, std::vector<int>& solutionElements);

    /**
     * Recursive function that calls itself producing as result a depth-first search throught the graph, calculating in each iteration
     * a label for each node it visits.
     * @param actualNode
     * @param graph
     * @param remainingLabels
     * @param labeling
     */
    void constructSolution(int actualNode, std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling);


    /**
     * Returns a random label from the candidate list of labels and removes the selected candidate label from the
     * remaining label list.
     * @param  parentNode
     * @param  remainingLabels
     * @param  labeling
     * @return
     */
    int calculateLabel(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);


    /**
     * Calculates a vector of labels that can be selected as new label for an specific adjacent node of parentNode.
     * @param  parentNode
     * @param  remainingLabels
     * @param  labeling
     * @return
     */
    std::vector<int> calculateCandidateList(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);



    /**
     * Calculates the largest difference between the label that belongs to parentNode and the remaining labels.
     * @param  parentNode
     * @param  remainingLabels
     * @param  labeling
     * @return
     */
     int calculateCardinality(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);



     /**
      * Calculate the differences between the label that belongs to parentNode and the remaining labels.
      * @param  parentNode
      * @param  remainingLabels
      * @param  labeling
      * @return a vector with all the differences.
      */
     std::vector<int> calculateDifferences(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling);


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
