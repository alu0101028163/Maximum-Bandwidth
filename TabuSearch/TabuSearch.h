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

  bool isTabu(std::vector<std::vector<int> > recencyFrequencyMatrix, int i, int j);
  void updateRecFreqMatrix(std::vector<std::vector<int> >& recencyFrequencyMatrix);
  void addTabu(std::vector<std::vector<int> >& recencyFrequencyMatrix, int period, int i, int j);

  std::vector<int> generateRandomSolution(int numberOfVertexs);

  /**
   * Changes the label i position value for the j position value and viceversa.
   * @param i
   * @param j
   * @param label
   */
  void swap(int i, int j , std::vector<int>& label);
  int evaluateMovement(int i, int j , std::vector<int> label, std::vector< std::vector<short int> > graph);
  void updateBestSolution(std::vector<int>& bestSolution, int& bestValue, std::vector<int>& currentSolution, int& currentValue);
}
