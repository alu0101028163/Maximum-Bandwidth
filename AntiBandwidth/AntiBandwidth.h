#pragma once

#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include <vector>

namespace AntiBandwidth {


  typedef std::vector<int> solutionT; // If any modification was to be made to the datatype,
									                    // change would be easy and clean

  /**
   * It's the objective function of the AntiBandwidth maximization problem which seeks
   * to find the minimum distance between nodes of a graph.
   * @param  graph
   * @param  label
   * @return       the minimum distance between all the nodes of the graph.
   */
  int objectiveFunction(std::vector< std::vector<short int> > graph, std::vector<int> label);

}
