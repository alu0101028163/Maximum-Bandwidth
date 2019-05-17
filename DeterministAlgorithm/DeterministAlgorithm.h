#pragma once
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include "../AntiBandwidth/AntiBandwidth.h"

namespace DeterministAlgorithm{
  /**
   * Generate labels formed by all possible permutations from 1 to numberOfVertexs.
   * @param numberOfVertexs
   */
  std::vector <std::vector<int> > generateLabels(int numberOfVertexs);

  /**
   * It finds the maximum value of the AntiBandwith objective function and returns
   * the label that retrieves that value.
   * @param  graph
   * @param  labels
   * @return        the label that reachs the best objective function.
   */
  std::vector<int> deterministAlgorithm(std::vector<std::vector<short int> > graph, std::vector<std::vector <int> > labels);
}
