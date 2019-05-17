#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "TabuSearch.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../GraphGenerator/Matrix_generator.hpp"



TEST_CASE("Data structure initializer works properly"){
  std::vector<std::vector<int> > v;
  v = TabuSearch::initializeDataStructure(5);
  REQUIRE(v.size() == 5);

  for(int i = 0; i < v.size(); i++){
    for(int j = 0; j < v[i].size(); j++){
      REQUIRE(v[i][j] == 0);
    }
  }
}


TEST_CASE("Swap function works properly"){

  static const int arr[] = {1,2,3,4};
  std::vector<int> label(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  TabuSearch::swap(0,1,label);
  REQUIRE(label[0] == 2);
  REQUIRE(label[1] == 1);
  REQUIRE(label[2] == 3);
  REQUIRE(label[3] == 4);

}


TEST_CASE("Update best Solution works properly"){

  static const int arr[] = {1,2,3,4};
  std::vector<int> bestSolution(arr, arr + sizeof(arr) / sizeof(arr[0]) );
  int bestValue = 10;

  static const int arr2[] = {2,4,6,8};
  std::vector<int> currentSolution(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  int currentValue = 20;

  static const int arr3[] = {4,8,12,16};
  std::vector<int> currentSolution2(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
  int currentValue2 = 5;

  TabuSearch::updateBestSolution(bestSolution, bestValue, currentSolution, currentValue);

  REQUIRE(bestSolution[0] == 2);
  REQUIRE(bestSolution[1] == 4);
  REQUIRE(bestSolution[2] == 6);
  REQUIRE(bestSolution[3] == 8);

  TabuSearch::updateBestSolution(bestSolution, bestValue, currentSolution2, currentValue2);

  REQUIRE(bestSolution[0] == 2);
  REQUIRE(bestSolution[1] == 4);
  REQUIRE(bestSolution[2] == 6);
  REQUIRE(bestSolution[3] == 8);

}


TEST_CASE(" Is tabu works properly"){


  std::vector<std::vector<int> > recencyFrequencyMatrix = file_to_matrix("./recFreqMatrix.txt");
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 1) == true);
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 2) == false);


}
