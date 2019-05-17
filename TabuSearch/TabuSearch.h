#pragma once
#include <vector>
#include "../AntiBandwidth/AntiBandwidth.h"
#include "../MatrixGenerator/Matrix_generator.hpp"
#include "../GraphGenerator/GraphGenerator.h"

namespace TabuSearch{

  void tabuSearch(std::vector<int> initialSolution, std::vector< std::vector<short int> > graph);

  /**
   * Initializes empty 2D-vector with dimensions equal to : dimension x dimension.
   * @param dimension
   */
  std::vector<std::vector<int> > initializeDataStructure(int dimension);


  /**
   * Checks if a movement is tabu.
   * @param  recencyFrequencyMatrix
   * @param  i
   * @param  j
   * @return
   */
  bool isTabu(std::vector<std::vector<int> > recencyFrequencyMatrix, int i, int j);

  /**
   * Updates the state of the Recency-Frequency matrix decrementing the tabu time
   * of the tabu movements.
   * @param recencyFrequencyMatrix [description]
   */
  void updateRecFreqMatrix(std::vector<std::vector<int> >& recencyFrequencyMatrix);

  /**
   * Adds a movement as tabu movement and increments the frequency of that movement.
   * @param recencyFrequencyMatrix
   * @param period the movement must be tabu.
   * @param i
   * @param j
   */
  void addTabu(std::vector<std::vector<int> >& recencyFrequencyMatrix, int period, int i, int j);


  /**
   * Generates a very simple random solution.
   * @param  numberOfVertexs size of the solution.
   * @return                 the solution.
   */
  std::vector<int> generateRandomSolution(int numberOfVertexs);

  /**
   * Changes the label i position value for the j position value and viceversa.
   * @param i
   * @param j
   * @param label
   */
  void swap(int i, int j , std::vector<int>& label);

  /**
   * Evaluates how swapping positions i and j affects the current labeling produced value.
   * @param  i
   * @param  j
   * @param  label
   * @param  graph
   * @return the value of the ObjectiveFunction obtained if you swap i and j.
   */
  int evaluateMovement(int i, int j , std::vector<int> label, std::vector< std::vector<short int> > graph);

  /**
   * Checks if the current solution is better than the best solution, updating the best solution
   * in that case.
   * @param bestSolution
   * @param bestValue
   * @param currentSolution
   * @param currentValue
   */
  void updateBestSolution(std::vector<int>& bestSolution, int& bestValue, std::vector<int>& currentSolution, int& currentValue);
}
