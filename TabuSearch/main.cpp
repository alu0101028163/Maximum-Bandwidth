#include "TabuSearch.h"
#include "../GRASP/Grasp.h"

int main(){

  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/Grid_Graphs/mesh9_9.txt");
  Grasp::setPercentage(0.55);
  std::vector<int> labeling = Grasp::grasp(graph,100,22);

  std::cout << "INITIAL SOLUTION: \n";
  for(int i = 0 ; i < labeling.size(); i++)
    std::cout << labeling[i] << " ";
  std::cout << "\n";

  std::cout << "VALUE OBTAINED: " << AntiBandwidth::objectiveFunction(graph,labeling) << "\n";

  TabuSearch::tabuSearch(labeling,graph, 100, 17);

}
