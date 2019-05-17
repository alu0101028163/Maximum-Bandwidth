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
