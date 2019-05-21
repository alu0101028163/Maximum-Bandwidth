#include "../TabuSearch/TabuSearch.h"
#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"

int main(int argc, char *argv[]){


  if (argc != 4){
    std::cout << "Wrong use: \nFirst argument is the path of the instance you want to test."
              << "\nSecond argument is the name of the instance you want to test."
              << "\nThird argument is the file that contains best GRASP label.";
    exit(1);
  }


  std::string instancePath = std::string(argv[1]);
  std::string instanceName = std::string(argv[2]);
  std::string graspLabel = std::string(argv[3]);


  // std::cout << "instancePath " << instancePath << "\n";
  // std::cout << "instanceName " << instanceName << "\n";
  // std::cout << "graspLabel " << graspLabel;


  std::vector<int> label = GraphGen::readLabel(graspLabel);
  for(int i = 0; i < label.size(); i++)
     std::cout << label[i] << " ";
  std::cout << "\n";
  std::cout << "SIZE: " << label.size() << "\n";
}
