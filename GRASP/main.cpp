#include "Grasp.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../MatrixGenerator/Matrix_generator.hpp"
#include <iostream>



int main(){

  const int N_REPETITIONS = 100;

  std::ofstream graspCalculations;
  std::string fichName = std::string("graspCalculations.csv");
  graspCalculations.open(fichName);
  graspCalculations << "alpha,n_iterations,n_reps,labeling,value\n";

  float percentage = 0.05;
  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
  std::vector<int> solutionElements;

  for(int i = 1; i <= graph.size(); i++){
    solutionElements.push_back(i);
  }

  static const int arr[] = {100, 500, 1000};
  std::vector<int> iterations(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  while(percentage < 1){
    Grasp::setPercentage(percentage);
    for(int i = 0; i < iterations.size() ; i++){
      for(int repetition = 0; repetition < N_REPETITIONS; repetition++){
        std::vector<int> labeling = Grasp::grasp(graph,iterations[i],17);
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



  // for(int iteration = 1; iteration < 10; iteration += 1){
  //   std::cout << "PERCENTAGE: " << percentage << "\n";
  //   std::vector<int> labeling = Grasp::grasp(graph,100,17);
  //
  //   for(int i = 0; i < labeling.size(); i++){
  //     std::cout << labeling[i] << " ";
  //   }
  //     std::cout << "\n";
  //     std::cout << "VALUE: " << AntiBandwidth::objectiveFunction(graph,labeling) << "\n\n\n";
  // }

}
