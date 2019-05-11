#include "DeterministAlgorithm.h"

namespace DeterministAlgorithm{

  /**
   * Generates all possible labels (permutations) with numberOfVertexs size.
   * @param numberOfVertexs
   */
  std::vector< std::vector<int> > generateLabels(int numberOfVertexs){

    std::vector< std::vector<int> > labels;

    std::vector<int> initialLabel;
    for (int i = 1; i <= numberOfVertexs; i++){
      initialLabel.push_back(i);
    }
    labels.push_back(initialLabel);

    std::vector<int> permutation;
    while(std::next_permutation(std::begin(initialLabel),std::end(initialLabel))){
      labels.push_back(initialLabel);
    }

    return labels;
  }

  std::vector<int> deterministAlgorithm(std::vector<std::vector<short int> > graph, std::vector<std::vector <int> > labels){


    int max = std::numeric_limits<int>::min();
    std::vector<int> bestLabel;

    int result = 0;

    for (int i = 0; i < labels.size(); i++){
      if((result = AntiBandwith::objectiveFunction(graph, labels[i])) > max){
          max = result;
          bestLabel = labels[i];
      }
    }

    return bestLabel;

  }

}
