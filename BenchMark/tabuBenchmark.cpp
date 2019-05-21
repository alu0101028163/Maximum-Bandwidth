#include "../TabuSearch/TabuSearch.h"
#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include <math.h>
#include <chrono>


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


  std::vector<int> label = GraphGen::readLabel(graspLabel);
  // for(int i = 0; i < label.size(); i++)
  //    std::cout << label[i] << " ";
  // std::cout << "\n";
  // std::cout << "SIZE: " << label.size() << "\n";
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../" + instancePath);


  std::ofstream graspCalculations;
  std::string fichName = std::string("./TabuCalculations/tabuCalculations_" + instanceName + ".csv");
  graspCalculations.open(fichName);
  graspCalculations << "n_iter, tabu_coef, diver_coef, inten_coef, value, time_in_milliseconds\n";


  int minTabuCoef = 3;
  int minItenCoef = 3;
  int minDiverCoef = 3;
  int maxTabuCoef = 100;
  int maxIntenCoef = 10;
  int maxDiverCoef = 4;


  for(int i = minTabuCoef; i < maxTabuCoef; i *= 1.5){
    for(int j = minIntenCoef; j < maxIntenCoef; j++){
      for(int k = minDiverCoef; k < maxDiverCoef; k++){
        TabuSearch::setTabuCoefficient(i);
        TabuSearch::setIntensificationCoefficient(j);
        TabuSearch::setDiversificationCoefficient(k);

        auto start = std::chrono::system_clock::now();
        std::vector<int> label = TabuSearch::tabuSearch(label,graph, 100);
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      }
    }
  }



}
