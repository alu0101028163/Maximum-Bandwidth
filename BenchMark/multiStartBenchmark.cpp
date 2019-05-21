#include "../MultiStart/MultiStart.h"
#include "../GraphGenerator/GraphGenerator.h"
#include <math.h>
#include <chrono>


int main(int argc, char *argv[]){


  if (argc != 3){
    std::cout << "Wrong use: \nFirst argument is the path of the instance you want to test."
              << "\nSecond argument is the name of the instance you want to test.\n";
    exit(1);
  }


  std::string instancePath = std::string(argv[1]);
  std::string instanceName = std::string(argv[2]);

  // for(int i = 0; i < label.size(); i++)
  //    std::cout << label[i] << " ";
  // std::cout << "\n";
  // std::cout << "SIZE: " << label.size() << "\n";
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../" + instancePath);


  std::ofstream multiStartCalculations;
  std::string fichName = std::string("./MultiStartCalculations/multiStartCalculations_" + instanceName + ".csv");
  multiStartCalculations.open(fichName);
  multiStartCalculations << "n_iter, n_local_searchs , label, value, structure, time_in_milliseconds\n";


  const int nIteraciones = 100;
  const int structure  = 3;


  std::cout << "MULTISTART BENCHMARK RUNNING\n";
  for(int i = 0; i < structure; i += 1){
    for(int j = 0; j < nIteraciones; j++){
        multiStartCalculations << nIteraciones << ",";
        multiStartCalculations << nIteraciones << ",";

        auto start = std::chrono::system_clock::now();
        std::vector<int> labeling = MultiStart::multiStart(i,graph, nIteraciones);
        auto end = std::chrono::system_clock::now();
        multiStartCalculations << "[ ";
        for(int j = 0; j < labeling.size(); j++){
          multiStartCalculations << labeling[j] << " ";
        }
        multiStartCalculations << "],";
        multiStartCalculations << AntiBandwidth::objectiveFunction(graph,labeling) << ",";
        multiStartCalculations << i << ",";
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        multiStartCalculations << elapsed.count() << "\n";
      }
  }
  std::cout << "MULTISTART BENCHMARK FINISHED\n";

  multiStartCalculations.close();


}
