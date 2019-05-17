#include "TabuSearch.h"

int main(){


  // std::vector<int> label;
  // label.push_back(2);
  // label.push_back(4);
  // label.push_back(6);
  // label.push_back(5);
  // label.push_back(8);
  //
  // std::vector<std::vector<short int > > graph = ABM::denseFileToGraph("./inst1.txt");

  // TabuSearch::tabuSearch(label,graph);
  std::vector<int> randomSolution = TabuSearch::generateRandomSolution(100);
  for(int i = 0; i < randomSolution.size(); i++){
    std::cout << randomSolution[i] << " ";
  }
    std::cout << "\n";

}
