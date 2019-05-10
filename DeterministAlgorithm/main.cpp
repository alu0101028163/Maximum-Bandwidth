#include "../GRAPH/GraphGenerator/Graph.h"
#include "DeterministAlgorithm.h"
#include <iostream>

int main(){

  std::vector <std::vector<int> > permutations = DeterministAlgorithm::generateLabels(5);
  for (int i = 0; i < permutations.size(); i++){
    for(int j = 0; j < permutations[i].size(); j++){
      std::cout << permutations[i][j];
    }
    std::cout << "\n";
  }

}
