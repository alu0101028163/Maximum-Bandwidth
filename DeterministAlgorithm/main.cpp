#include "../GRAPH/GraphGenerator/GraphGenerator.h"
#include "DeterministAlgorithm.h"
#include "AntiBandwidth.h"
#include <iostream>

int main(){

  std::vector< std::vector<short int> > graph = ABM::fileToGraph("inst1.txt");
  // std::vector <std::vector<int> > permutations = DeterministAlgorithm::generateLabels(10);
  std::vector<int> label2;
  label2.push_back(1);
  label2.push_back(4);
  label2.push_back(5);
  label2.push_back(8);
  label2.push_back(3);
  int value = AntiBandwith::objectiveFunction(graph, label2);
  std::cout << value << "\n";


  // for (int i = 0; i < graph.size(); i++){
  //   for(int j = 0; j < graph[i].size(); j++){
  //     std::cout << graph[i][j];
  //   }
  //   std::cout << "\n";
  // }
  //
  // for (int i = 0; i < 1; i++){
  //   for(int j = 0; j < permutations[i].size(); j++){
  //     std::cout << permutations[i][j];
  //   }
  //   std::cout << "\n";
  // }


}
