#include "../GraphGenerator/GraphGenerator.h"
#include "DeterministAlgorithm.h"
#include "../Antibandwidth/AntiBandwidth.h"
#include <iostream>

int main(){

  // std::vector< std::vector<short int> > graph = ABM::disperseFileToGraph("../Literature_Instances/caterpillars/caterpillars/caterpillar_5_4.txt");
  std::vector< std::vector<short int> > graph = ABM::denseFileToGraph("./inst1.txt");
  std::vector <std::vector<int> > labels = DeterministAlgorithm::generateLabels(graph.size());
  std::vector <int> solution = DeterministAlgorithm::deterministAlgorithm(graph, labels);

  for(int i = 0; i < solution.size(); i++){
    std::cout << solution[i] << " ";
  }
    std::cout << "\n";

  //
  // for (int i = 0; i < graph.size(); i++){
  //   for(int j = 0; j < graph[i].size(); j++){
  //     std::cout << graph[i][j];
  //   }
  //   std::cout << "\n";
  // }



}
