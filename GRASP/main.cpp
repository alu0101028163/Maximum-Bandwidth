#include "Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include <iostream>


int main(){

  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
  std::vector<int> solutionElements;

  for(int i = 1; i <= graph.size(); i++){
    solutionElements.push_back(i);
  }

  std::vector<int> labeling = Grasp::grasp(graph,100,17);

  for(int i = 0; i < labeling.size(); i++){
    std::cout << labeling[i] << " ";
  }
    std::cout << "\n";
    std::cout << "VALUE: " << AntiBandwidth::objectiveFunction(graph,labeling) << "\n";
}
