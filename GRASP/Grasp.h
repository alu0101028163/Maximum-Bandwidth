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
    extern int STRUCTURE;

    /**
     * Sets the alpha that modifies the behaviour of the greedy's randomized solution
     * generation.
     * @param percentage [description]
     */
    void setPercentage(float percentage);

    /**
     * Sets the neighbourhood solution that's going to be used.
     * @param mode  it's actually the structure to be used.
     */
    void setStructure(int mode);

    /**
     * Grasp algorithm, encapsulates the generation of the greedy randomized solution,
     * the local search and the update of the best solution.
     * This process is repeated maxItearions times and eager indicates if the generation
     * of the solution is going to be eager or greedy.
     * @param  graph
     * @param  maxIterations
     * @param  eager
     * @return
     */
    std::vector<int> grasp(const std::vector< std::vector<short int> >& graph, int maxIterations, bool eager);


    /**
     * If the current Solution value is better than the best known value at the moment it is updated and
     * set as the best solution. The best value is also updated.
     * @param  bestSolutionValue
     * @param  bestSolution
     * @param  currentSolution
     * @param  graph
     * @return
     */
    bool updateSolution(int& bestSolutionValue, std::vector<int>& bestSolution, std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph);

    /**
     * Swaps two elements with indexed i,j in a label.
     * @param i
     * @param j
     * @param label
     */
    void swap(int i, int j , std::vector<int>& label);

    /**
     * Movement i,j is evaluated in a label, object function value obtained by the movement is returned.
     * @param  i
     * @param  j
     * @param  label
     * @param  graph
     * @return
     */
    int evaluateMovement(int i, int j , std::vector<int> label, const std::vector< std::vector<short int> >& graph);

    /**
     * Method that applies to the current solution the movement previously defined using setStructure.
     * @see   setStructure
     * @param currentSolution
     * @param graph
     */
    void localSearch(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph);


    /**
     * Simple exchange swap movement for local search
     * @param currentSolution that will suffer the movement
     * @param graph
     */
    void simpleExchange(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph);


    /**
     * Double exchange swap movement for local search
     * @param currentSolution that will suffer the movement
     * @param graph
     */
    void doubleExchange(std::vector<int>&  currentSolution, const std::vector<std::vector<short int>>& graph);


    /**
     * Cyclic adjacent swap movement for local search.
     * @param currentSolution that will suffer the movement
     * @param graph
     */
    void cyclicAdjExchange(std::vector<int>& currentSolution, const std::vector<std::vector<short int>>& graph);

    /**
     * Wrapper function for the construction of a greedy randomized solution that initializes the data structures and recursive
     * depth-first search algorithm.
     * @param  graph            [description]
     * @param  solutionElements [description]
     * @return                  [description]
     */
    std::vector<int> constructGreedyRandomizedSolution(const std::vector< std::vector<short int> >& graph, std::vector<int>& solutionElements);

    /**
     * Recursive function that calls itself producing as result a depth-first search throught the graph, calculating in each iteration
     * a label for each node it visits.
     * @param actualNode
     * @param graph
     * @param remainingLabels
     * @param labeling
     */
    void constructSolution(int actualNode, const std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling);


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
