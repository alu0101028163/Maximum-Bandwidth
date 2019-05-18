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


// TEST_CASE("Calculate cardinality works properly"){
//
//   std::list<int> label({1,2,3,4});
//   REQUIRE(Grasp::calculateCardinality(label) == 4);
//
//   std::list<int> label2({1,20,3,4});
//   REQUIRE(Grasp::calculateCardinality(label2) == 20);
//
//   std::list<int> label3({40,20,3,4});
//   REQUIRE(Grasp::calculateCardinality(label3) == 40);
//
//
// }

TEST_CASE("Calculate Differences works properly"){

  int parentNode = 0;
  static const int arr[] = {3,0,0,0};
  std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );
  std::list<int> remainingLabels({1,2,4});
  std::vector<int> differences = Grasp::calculateDifferences(parentNode, remainingLabels, labeling);
  REQUIRE(differences[0] == 2);
  REQUIRE(differences[1] == 1);
  REQUIRE(differences[2] == 1);


  static const int arr2[] = {3,0,0,0};
  std::vector<int> labeling2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  std::list<int> remainingLabels2({6,10,1});
  std::vector<int> differences2 = Grasp::calculateDifferences(parentNode, remainingLabels2, labeling2);
  REQUIRE(differences2[0] == 3);
  REQUIRE(differences2[1] == 7);
  REQUIRE(differences2[2] == 2);

}


// TEST_CASE("Calculate Candidate List works properly"){
//
//
//   int parentNode = 0;
//   static const int arr[] = {3,0,0,0};
//   std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );
//   std::list<int> remainingLabels({1,2,4});
//   std::vector<int> RCL = Grasp::calculateCandidateList(parentNode,remainingLabels,labeling);
//
//   REQUIRE(RCL.size() == 1);
//   REQUIRE(RCL[0] == 1);
//
//
// }
