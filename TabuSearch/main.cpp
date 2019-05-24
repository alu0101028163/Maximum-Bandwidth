#include "TabuSearch.h"
#include "../GRASP/Grasp.h"

int main(){

  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr02.mtx.rnd");
  Grasp::setPercentage(0.55);

  // std::vector<int> labeling = Grasp::grasp(graph,100,22);
  //
  // std::cout << "INITIAL SOLUTION: \n";
  // for(int i = 0 ; i < labeling.size(); i++)
  //   std::cout << labeling[i] << " ";
  // std::cout << "\n";
  //
  // BEST LABEL: [ 19 25 26 8 23 39 21 16 11 34 9 14 22 17 28 15 10 1 18 13 2 32 35 3 30 38 4 31 5 7 20 29 33 12 24 6 27 36 37 ]

  // static const int arr[] = {19,25,26,8,23,39,21,16,11,34,9,14,22,17,28,15,10,1,18,13,2,32,35,3,30,38,4,31,5,7,20,29,33,12,24,6,27,36,37};
  static const int arr[] = {10 ,7, 48, 43, 20, 27, 17, 39, 40, 46, 45, 49, 19, 8, 47, 41, 5, 38, 24, 33, 22, 31, 42, 3, 21, 9, 44, 23, 36, 18, 12, 1, 28, 35, 16, 34, 30, 6, 26, 4, 13, 2 ,37, 29, 25 ,32, 11 ,14, 15 };
// [ 3 4 7 6 10 24 29 28 26 13 5 27 23 8 11 9 32 2 31 25 1 17 30 20 12 16 18 14 21 19 15 22 ]
// static const int arr[] = {3, 4 ,7 ,6, 10, 24, 29, 28, 26, 13, 5, 27, 23, 8, 11, 9, 32, 2, 31, 25, 1, 17, 30, 20, 12, 16, 18, 14, 21, 19, 15, 22 };

  std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  std::cout << "VALUE OBTAINED: " << AntiBandwidth::objectiveFunction(graph,labeling) << "\n";


  TabuSearch::setTabuCoefficient(9);
  TabuSearch::setIntensificationCoefficient(6);
  TabuSearch::setDiversificationCoefficient(3);

  TabuSearch::tabuSearch(labeling,graph, 10000);

}
