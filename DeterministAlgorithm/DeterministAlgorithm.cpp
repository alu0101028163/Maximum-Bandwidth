#include "DeterministAlgorithm.h"

namespace DeterministAlgorithm{

  std::vector< std::vector<int> > generateLabels(int numberOfVertexs){

    // Vector where labels will be stored.
    std::vector< std::vector<int> > labels;

    // We initialize the labels vector inserting a label
    // with values from 1 to numberOfVertexs
    std::vector<int> initialLabel;
    for (int i = 1; i <= numberOfVertexs; i++){
      initialLabel.push_back(i);
    }
    labels.push_back(initialLabel);


    // We calculate all possible permutations of that initial label and
    // insert them in the labels vector.
    std::vector<int> permutation;
    while(std::next_permutation(std::begin(initialLabel),std::end(initialLabel))){
      labels.push_back(initialLabel);
    }

    return labels;
  }

  std::vector<int> deterministAlgorithm(std::vector<std::vector<short int> > graph, std::vector<std::vector <int> > labels){


    // Variable that stores the maximum objetive function value reached.
    int max = std::numeric_limits<int>::min();
    std::vector<int> bestLabel;

    int result = 0;

    // For every label
    for (int i = 0; i < labels.size(); i++){
      // It that label objective function value is bigger than the current maximum
      // then that label is the best label currently visited.
      if((result = AntiBandwidth::objectiveFunction(graph, labels[i])) > max){
          max = result;
          bestLabel = labels[i];
      }
    }

    std::cout << max << "\n";
    return bestLabel;

  }

}
