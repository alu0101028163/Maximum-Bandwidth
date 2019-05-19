#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "TabuSearch.h"
#include "../GraphGenerator/GraphGenerator.h"
#include "../MatrixGenerator/Matrix_generator.hpp"


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


TEST_CASE("Is tabu works properly"){

  std::vector<std::vector<int> > recencyFrequencyMatrix = MatrixGenerator::file_to_matrix("./recFreqMatrix.txt");
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 1) == true);
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 2) == false);

}


TEST_CASE("Add tabu works properly"){


  std::vector<std::vector<int> > recencyFrequencyMatrix = MatrixGenerator::file_to_matrix("./recFreqMatrix.txt");

  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 2) == false);
  TabuSearch::addTabu(recencyFrequencyMatrix, 3, 0, 2);
  REQUIRE(recencyFrequencyMatrix[0][2] == 3);
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 2) == true);

  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 1) == true);
  REQUIRE(recencyFrequencyMatrix[0][1] == 2);
  TabuSearch::addTabu(recencyFrequencyMatrix, 3, 0, 1);
  REQUIRE(recencyFrequencyMatrix[0][1] == 3);
  REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, 1) == true);

}

TEST_CASE("Update recency-frequency matrix works properly"){
  std::vector<std::vector<int> > recencyFrequencyMatrix = MatrixGenerator::file_to_matrix("./recFreqMatrix.txt");
  TabuSearch::addTabu(recencyFrequencyMatrix, 3, 0, 1);
  TabuSearch::addTabu(recencyFrequencyMatrix, 3, 0, 2);
  TabuSearch::addTabu(recencyFrequencyMatrix, 3, 0, 3);

  for(int i = 0; i < 3; i++){
    REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, i + 1) == true);
    REQUIRE(recencyFrequencyMatrix[0][i + 1] == 3);
  }

  for(int i = 0; i < 3; i++){
    REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, i + 1) == true);
    REQUIRE(recencyFrequencyMatrix[0][i + 1] == 3 - i);
    TabuSearch::updateRecFreqMatrix(recencyFrequencyMatrix);
  }

  TabuSearch::updateRecFreqMatrix(recencyFrequencyMatrix);
  for(int i = 0; i < 3; i++){
    REQUIRE(TabuSearch::isTabu(recencyFrequencyMatrix, 0, i + 1) == false);
    REQUIRE(recencyFrequencyMatrix[0][i + 1] == 0);
  }

}

TEST_CASE("Evaluate movement works properly"){


  std::vector<std::vector<short int> > graph = GraphGen::denseFileToGraph("./inst1.txt");
  static const int arr[] = {2,4,6,5,8};
  std::vector<int> label(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  REQUIRE(AntiBandwidth::objectiveFunction(graph,label) == 1);

  int movementValue = TabuSearch::evaluateMovement(2,3,label,graph);
  REQUIRE(label[0] == 2);
  REQUIRE(label[1] == 4);
  REQUIRE(label[2] == 6);
  REQUIRE(label[3] == 5);
  REQUIRE(label[4] == 8);
  REQUIRE(movementValue == 2);

}


TEST_CASE("Tabu search solves bcspwr01"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr01.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,17);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 17);
}

TEST_CASE("Tabu search solves bcspwr02"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcspwr02.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,21);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 21);
}

TEST_CASE("Tabu search solves ibm32"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/ibm32.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,9);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 9);
}

TEST_CASE("Tabu search solves pores_1"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/pores_1.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,6);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 6);
}

TEST_CASE("Tabu search solves curtis54"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/curtis54.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,12);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 12);
}

TEST_CASE("Tabu search solves will57"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/will57.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,13);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 13);
}

TEST_CASE("Tabu search solves bcsstk01"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/bcsstk01.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,8);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 8);
}

TEST_CASE("Tabu search solves dwt__234"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/dwt__234.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,51);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 51);
}

TEST_CASE("Tabu search solves ash85"){
    std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../Literature_Instances/hb/ash85.mtx.rnd");
    std::vector<int> randomSolution = TabuSearch::generateRandomSolution(graph.size());
    std::vector<int> bestSolution = TabuSearch::tabuSearch(randomSolution,graph,10000,22);

    for(int i = 0; i < bestSolution.size(); i++){
      for(int j = i + 1; j < bestSolution.size(); j++){
        REQUIRE(bestSolution[i] != bestSolution[j]);
      }
    }

    REQUIRE(AntiBandwidth::objectiveFunction(graph,bestSolution) >= 22);
}
