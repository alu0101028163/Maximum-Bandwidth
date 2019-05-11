#include <vector>
#include "../AntiBandwidth/AntiBandwidth.h"
namespace TabuSearch{

  void tabuSearch(std::vector<int> initialSolution, std::vector< std::vector<short int> > graph);

  /**
   * Initializes empty 2D-vector with dimensions equal to : dimension x dimension.
   * @param dimension
   */
  std::vector<std::vector<int> > initializeDataStructure(int dimension);
  std::vector<int> move(int edge1, int edge2, std::vector<int> actualSolution);
  void evaluateMovements(int edge, std::vector<std::vector<int> >& movementsMatrix,
       std::vector< std::vector<short int> > graph, std::vector<int> actualSolution);
}
