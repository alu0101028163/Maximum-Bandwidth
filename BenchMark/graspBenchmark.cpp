#include "../GRASP/Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../AntiBandwidth/AntiBandwidth.h"
#include <stdlib.h>
#include <chrono>

int main(int argc, char *argv[]){

    if (argc != 3){
      std::cout << "Wrong use: \nFirst argument is the path of the instance you want to test."
                << "\nSecond argument is the name of the instance you want to test";
      exit(1);
    }


    const int N_REPETITIONS = 10;

    std::string instancePath = std::string(argv[1]);
    std::string instanceName = std::string(argv[2]);

    std::ofstream graspCalculations;
    std::string fichName = std::string("./GraspCalculations/graspCalculations_" + instanceName + ".csv");
    graspCalculations.open(fichName);
    graspCalculations << "alpha,n_local_searchs,n_reps,labeling,value,neighb_structure,search_type,time_in_milliseconds\n";

    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph(instancePath);

    /* iterations equals to local searchs */
    static const int arr[] = {100};
    std::vector<int> iterations(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  for(int searchType = 0; searchType < 2; searchType++){
   for(int neighStructure = 0; neighStructure < 2; neighStructure++ ){
     float percentage = 0.10;
      while(percentage < 1){
        Grasp::setPercentage(percentage);
        Grasp::setStructure(neighStructure);
        for(int i = 0; i < iterations.size() ; i++){
          for(int repetition = 0; repetition < N_REPETITIONS; repetition++){

            auto start = std::chrono::system_clock::now();
            std::vector<int> labeling = Grasp::grasp(graph,iterations[i],searchType);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            graspCalculations << percentage << ",";
            graspCalculations << iterations[i] << ",";
            graspCalculations << N_REPETITIONS << ",";
            graspCalculations << "[ ";
            for(int j = 0; j < labeling.size(); j++){
              graspCalculations << labeling[j] << " ";
            }
            graspCalculations << "],";
            graspCalculations << AntiBandwidth::objectiveFunction(graph,labeling) << ",";

            graspCalculations << neighStructure << ",";
            graspCalculations << searchType << ",";

            graspCalculations << elapsed.count() << "\n";

          }
        }
        percentage += 0.10;
      }
    }
  }

    graspCalculations.close();

}
