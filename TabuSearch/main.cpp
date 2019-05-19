#include "TabuSearch.h"
#include "../GRASP/Grasp.h"

int main(){

  //
  // std::vector<int> label;
  // label.push_back(2);
  // label.push_back(4);
  // label.push_back(6);
  // label.push_back(5);
  // label.push_back(8);
  //
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
  std::vector<int> solutionElements;

  for(int i = 1; i <= graph.size(); i++){
    solutionElements.push_back(i);
  }

  std::vector<int> labeling = Grasp::grasp(graph,100,17);

  // std::vector<std::vector<short int > > graph = GraphGen::denseFileToGraph("./inst1.txt");

  // for(int i = 0; i < graph.size(); i++){
  //   for(int j = 0; j < graph[i].size(); j++){
  //     std::cout << graph[i][j] << " ";
  //   }
  //     std::cout << "\n";
  // }

  TabuSearch::tabuSearch(labeling,graph, 100000, 17);

  // TabuSearch::tabuSearch(label,graph);
  // std::vector<int> randomSolution = TabuSearch::generateRandomSolution(100);
  // for(int i = 0; i < randomSolution.size(); i++){
  //   std::cout << randomSolution[i] << " ";
  // }
  //   std::cout << "\n";

}
