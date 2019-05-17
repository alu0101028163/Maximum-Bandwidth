#include "TabuSearch.h"

int main(){

  //
  // std::vector<int> label;
  // label.push_back(2);
  // label.push_back(4);
  // label.push_back(6);
  // label.push_back(5);
  // label.push_back(8);

  // std::vector<std::vector<short int > > graph = GraphGen::denseFileToGraph("./inst1.txt");
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");

  // for(int i = 0; i < graph.size(); i++){
  //   for(int j = 0; j < graph[i].size(); j++){
  //     std::cout << graph[i][j] << " ";
  //   }
  //     std::cout << "\n";
  // }

  std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
  TabuSearch::tabuSearch(randomSolution,graph);

  // TabuSearch::tabuSearch(label,graph);
  // std::vector<int> randomSolution = TabuSearch::generateRandomSolution(100);
  // for(int i = 0; i < randomSolution.size(); i++){
  //   std::cout << randomSolution[i] << " ";
  // }
  //   std::cout << "\n";

}
