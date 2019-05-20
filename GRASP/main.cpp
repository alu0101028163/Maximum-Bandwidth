#include "Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../MatrixGenerator/Matrix_generator.hpp"
#include <iostream>



int main(){

  const std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
  std::vector<int> labeling = Grasp::grasp(graph,100,0);
}
