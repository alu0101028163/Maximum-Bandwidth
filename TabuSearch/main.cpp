#include "TabuSearch.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../GraphGenerator/Matrix_generator.hpp"

int main(){


  std::vector<int> label;
  label.push_back(2);
  label.push_back(4);
  label.push_back(6);
  label.push_back(5);
  label.push_back(8);

  std::vector<std::vector<short int > > graph = ABM::denseFileToGraph("./inst1.txt");

  TabuSearch::tabuSearch(label,graph);

}
