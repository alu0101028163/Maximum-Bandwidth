#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../AntiBandwidth/AntiBandwidth.h"
#include <stdlib.h>

int main(int argc, char *argv[]){

    if (argc != 4){
      std::cout << "Wrong use: \nFirst argument is the path of the instance you want to test."
                << "\nSecond argument is the name of the instance you want to test"
                 << "\nThird argument is the best value for that instance.\n";
      exit(1);
    }


    const int N_REPETITIONS = 100;

    std::string instancePath = std::string(argv[1]);
    std::string instanceName = std::string(argv[2]);
    int bestValue = atoi(argv[3]);

    std::ofstream graspCalculations;
    std::string fichName = std::string("graspCalculations_" + instanceName + ".csv");
    graspCalculations.open(fichName);
    graspCalculations << "alpha,n_local_searchs,n_reps,labeling,value\n";

    float percentage = 0.05;
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../" + instancePath);
    std::vector<int> solutionElements;

    for(int i = 1; i <= graph.size(); i++){
      solutionElements.push_back(i);
    }

    /* iterations equals to local searchs */
    static const int arr[] = {10, 50, 100};
    std::vector<int> iterations(arr, arr + sizeof(arr) / sizeof(arr[0]) );

    while(percentage < 1){
      Grasp::setPercentage(percentage);
      for(int i = 0; i < iterations.size() ; i++){
        for(int repetition = 0; repetition < N_REPETITIONS; repetition++){
          std::vector<int> labeling = Grasp::grasp(graph,iterations[i],bestValue, true);
          graspCalculations << percentage << ",";
          graspCalculations << iterations[i] << ",";
          graspCalculations << N_REPETITIONS << ",";
          graspCalculations << "[ ";
          for(int j = 0; j < labeling.size(); j++){
            graspCalculations << labeling[j] << " ";
          }
          graspCalculations << "],";
          graspCalculations << AntiBandwidth::objectiveFunction(graph,labeling) << "\n";

        }
      }
      percentage += 0.05;
    }

    graspCalculations.close();

}
