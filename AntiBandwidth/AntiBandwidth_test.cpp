#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "AntiBandwidth.h"
#include "../GraphGenerator/GraphGenerator.h"


TEST_CASE("Objective Function is begin correctly performed"){

  std::vector< std::vector<short int> > graph = ABM::denseFileToGraph("inst1.txt");

  std::vector<int> label1;
  label1.push_back(2);
  label1.push_back(3);
  label1.push_back(1);
  label1.push_back(5);
  label1.push_back(4);
  REQUIRE(AntiBandwidth::objectiveFunction(graph, label1) == 1);

  std::vector<int> label2;
  label2.push_back(1);
  label2.push_back(4);
  label2.push_back(5);
  label2.push_back(8);
  label2.push_back(3);
  REQUIRE(AntiBandwidth::objectiveFunction(graph, label2) == 2);

  std::vector<int> label3;
  label3.push_back(0);
  label3.push_back(0);
  label3.push_back(0);
  label3.push_back(0);
  label3.push_back(0);
  REQUIRE(AntiBandwidth::objectiveFunction(graph, label3) == 0);

}
