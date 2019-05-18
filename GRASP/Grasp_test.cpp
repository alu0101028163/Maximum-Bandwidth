#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include <iostream>
#include "../AntiBandwidth/catch.hpp"
#include "Grasp.h"

TEST_CASE("Get random label from vector works properly"){
  srand((int)time(0));
  static const int arr[] = {1,2,3,4};
  std::vector<int> label(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  int label1 = Grasp::getRandomLabel(label);
  REQUIRE(label1 >= 1);
  REQUIRE(label1 <= 4);

  int label2 = Grasp::getRandomLabel(label);
  REQUIRE(label2 >= 1);
  REQUIRE(label2 <= 4);

}

TEST_CASE("Get random label from list works properly"){

  std::list<int> label({1,2,3,4});
  int label1 = Grasp::getRandomLabel(label);
  REQUIRE(label1 >= 1);
  REQUIRE(label1 <= 4);

  int label2 = Grasp::getRandomLabel(label);
  REQUIRE(label2 >= 1);
  REQUIRE(label2 <= 4);
}


TEST_CASE("Is visited works properly"){

  static const int arr[] = {1,0,0,3};
  std::vector<int> label(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  REQUIRE(Grasp::isVisited(0,label) == true);
  REQUIRE(Grasp::isVisited(1,label) == false);
  REQUIRE(Grasp::isVisited(2,label) == false);
  REQUIRE(Grasp::isVisited(3,label) == true);


}


TEST_CASE("Calculate cardinality"){

  std::list<int> label({1,2,3,4});
  REQUIRE(Grasp::calculateCardinality(label) == 4);

  std::list<int> label2({1,20,3,4});
  REQUIRE(Grasp::calculateCardinality(label2) == 20);

  std::list<int> label3({40,20,3,4});
  REQUIRE(Grasp::calculateCardinality(label3) == 40);


}
