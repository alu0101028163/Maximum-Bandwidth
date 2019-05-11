#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include "AntiBandwidth.h"

namespace DeterministAlgorithm{
  std::vector< std::vector<int> > generateLabels(int numberOfVertexs);
  std::vector<int> deterministAlgorithm(std::vector<std::vector<short int> > graph, std::vector<std::vector <int> > labels);
}
