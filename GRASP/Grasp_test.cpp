#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include <iostream>
#include "../AntiBandwidth/catch.hpp"
#include "../GraphGenerator/GraphGenerator.h"
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

TEST_CASE("Calculate cardinality works properly"){

  int parentNode = 0;
  static const int arr[] = {3,0,0,0};
  std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );
  std::list<int> remainingLabels({1,2,4});

  int cardinality = Grasp::calculateCardinality(parentNode, remainingLabels, labeling);
  REQUIRE(cardinality == 2);

  static const int arr2[] = {3,0,0,0};
  std::vector<int> labeling2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  std::list<int> remainingLabels2({6,10,1});
  cardinality = Grasp::calculateCardinality(parentNode, remainingLabels2, labeling2);

  REQUIRE(cardinality == 7);

}


TEST_CASE("Calculate Candidate List works properly"){


  int parentNode = 0;
  static const int arr[] = {3,0,0,0};
  std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );
  std::list<int> remainingLabels({1,2,4});
  std::vector<int> RCL = Grasp::calculateCandidateList(parentNode,remainingLabels,labeling);

  REQUIRE(RCL.size() == 1);
  REQUIRE(RCL[0] == 1);


  int parentNode2 = 1;
  static const int arr2[] = {0,1,0,0};
  std::vector<int> labeling2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  std::list<int> remainingLabels2({8,7,6});
  std::vector<int> RCL2 = Grasp::calculateCandidateList(parentNode2,remainingLabels2,labeling2);

  REQUIRE(RCL2.size() == 3);
  REQUIRE(RCL2[0] == 8);
  REQUIRE(RCL2[1] == 7);
  REQUIRE(RCL2[2] == 6);



}


TEST_CASE("Calculate Label works properly"){


  int parentNode = 0;
  static const int arr[] = {3,0,0,0};
  std::vector<int> labeling(arr, arr + sizeof(arr) / sizeof(arr[0]) );
  std::list<int> remainingLabels({1,2,4});
  int label = Grasp::calculateLabel(parentNode,remainingLabels,labeling);

  REQUIRE(label == 1);

  int parentNode2 = 1;
  static const int arr2[] = {0,1,0,0};
  std::vector<int> labeling2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  std::list<int> remainingLabels2({8,7,6});
  label = Grasp::calculateLabel(parentNode2,remainingLabels2,labeling2);

  REQUIRE(label >= 6);
  REQUIRE(label <= 8);

}

TEST_CASE("Construct greedy randomized solution works properly"){

  std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
  std::vector<int> solutionElements;

  for(int i = 1; i <= graph.size(); i++){
    solutionElements.push_back(i);
  }

  std::vector<int> labeling = Grasp::constructGreedyRandomizedSolution(graph,solutionElements);
  auto it = std::unique(labeling.begin(), labeling.end());


  REQUIRE(labeling.size() == graph.size());
  REQUIRE(it == labeling.end());


}
