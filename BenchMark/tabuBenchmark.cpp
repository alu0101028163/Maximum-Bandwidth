#include "../TabuSearch/TabuSearch.h"
#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"

int main(){

  std::vector<int> label = GraphGen::readLabel("./GraspCalculations/temp_label.txt");
  for(int i = 0; i < label.size(); i++)
     std::cout << label[i] << " ";
  std::cout << "\n";
  std::cout << "SIZE: " << label.size() << "\n";
}
