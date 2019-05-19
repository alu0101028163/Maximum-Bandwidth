#include "TabuSearch.h"
#include "../GRASP/Grasp.h"

int main(){

  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/ibm32.mtx.rnd");
  std::vector<int> solutionElements;

  for(int i = 1; i <= graph.size(); i++){
    solutionElements.push_back(i);
  }

  std::vector<int> labeling = Grasp::grasp(graph,100,17);

  TabuSearch::tabuSearch(labeling,graph, 1000, 17);

}
