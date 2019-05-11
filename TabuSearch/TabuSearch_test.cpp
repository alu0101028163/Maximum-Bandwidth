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

TEST_CASE("Move function works properly"){

  std::vector<int> label;
  label.push_back(2);
  label.push_back(4);
  label.push_back(6);
  label.push_back(5);
  label.push_back(8);

  std::vector<int> expectedLabel;
  expectedLabel.push_back(2);
  expectedLabel.push_back(6);
  expectedLabel.push_back(4);
  expectedLabel.push_back(5);
  expectedLabel.push_back(8);

  std::vector<int> result = TabuSearch::move(1,2,label);
  REQUIRE(result == expectedLabel);
}


// void evaluateMovements(int edge, std::vector<std::vector<int> >& movementsMatrix,
     // std::vector< std::vector<short int> > graph, std::vector<int> actualSolution);
TEST_CASE("Evaluate movement works properly"){


  std::vector<std::vector<int> > movementMatrix = TabuSearch::initializeDataStructure(5);

  std::vector<int> label;
  label.push_back(2);
  label.push_back(4);
  label.push_back(6);
  label.push_back(5);
  label.push_back(8);

  std::vector<std::vector<short int > > graph = ABM::denseFileToGraph("./inst1.txt");

  std::vector<std::vector<int> > movementMatrixExpected = file_to_matrix("./inst2.txt");

  TabuSearch::evaluateMovements(0,movementMatrix,graph,label);

  for(int i = 0; i < graph.size(); i++){
    for(int j = 0; j < graph[i].size(); j++){
      std::cout << movementMatrix[i][j] << " ";
    }
    std::cout << "\n";
  }

  for(int i = 0; i < movementMatrix.size(); i++){
    REQUIRE(movementMatrix[0][i] == movementMatrixExpected[0][i]);
  }

}
