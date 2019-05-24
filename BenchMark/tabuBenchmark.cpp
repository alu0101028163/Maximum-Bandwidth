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
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph(instancePath);


  std::ofstream graspCalculations;
  std::string fichName = std::string("./TabuCalculations/tabuCalculations_" + instanceName + ".csv");
  graspCalculations.open(fichName);
  graspCalculations << "n_local_search, tabu_coef, diver_coef, inten_coef, label, value, time_in_milliseconds\n";


  const int nIteraciones = 100;
  const int minTabuCoef  = 3;
  const int minIntenCoef = 3;
  const int minDiverCoef = 3;
  const int maxTabuCoef  = 100;
  const int maxIntenCoef = 10;
  const int maxDiverCoef = 4;

  std::cout << "TABU BENCHMARK RUNNING\n";
  for(int i = minTabuCoef; i < maxTabuCoef; i *= 1.5){
    for(int j = minDiverCoef; j < maxDiverCoef; j++){
      for(int k = minIntenCoef; k < maxIntenCoef; k++){

        graspCalculations << nIteraciones << ",";
        graspCalculations << i << ",";
        graspCalculations << k << ",";
        graspCalculations << j << ",";

        TabuSearch::setTabuCoefficient(i);
        TabuSearch::setDiversificationCoefficient(j);
        TabuSearch::setIntensificationCoefficient(k);

        auto start = std::chrono::system_clock::now();
        std::vector<int> labeling = TabuSearch::tabuSearch(label,graph, nIteraciones);
        auto end = std::chrono::system_clock::now();
        graspCalculations << "[ ";
        for(int j = 0; j < labeling.size(); j++){
          graspCalculations << labeling[j] << " ";
        }
        graspCalculations << "],";
        graspCalculations << AntiBandwidth::objectiveFunction(graph,labeling) << ",";
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        graspCalculations << elapsed.count() << "\n";
      }
    }
  }
  std::cout << "TABU BENCHMARK FINISHED\n";

  graspCalculations.close();


}
