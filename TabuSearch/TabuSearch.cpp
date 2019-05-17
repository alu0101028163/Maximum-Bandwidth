#include "TabuSearch.h"

namespace TabuSearch{

  void tabuSearch(std::vector<int> initialSolution, std::vector< std::vector<short int> > graph){


    // Stores frequency of movements in the inferior diagonal and
    // recency of movements in the superior diagonal.
    std::vector<std::vector<int> > recencyFrequencyMatrix = TabuSearch::initializeDataStructure(graph.size());

    // Stores the possible movements and their associated benefit.
    std::vector<std::vector<int> > movementsMatrix = TabuSearch::initializeDataStructure(graph.size());

    for(int i = 0; i < movementsMatrix.size(); i++)
        evaluateMovements(i, movementsMatrix, graph, initialSolution);

    for(int i = 0; i < movementsMatrix.size(); i++){
      for(int j = 0; j < movementsMatrix[i].size(); j++){
        std::cout << movementsMatrix[i][j] << " ";
      }
        std::cout << "\n";
    }

  }


  void evaluateMovements(int edge, std::vector<std::vector<int> >& movementsMatrix,
                        std::vector< std::vector<short int> > graph, std::vector<int> actualSolution){
    for (int i = edge + 1; i < movementsMatrix.size(); i++){
      movementsMatrix[edge][i] = AntiBandwidth::objectiveFunction(graph, move(edge,i,actualSolution));
    }
  }

  std::vector<int> move(int edge1, int edge2, std::vector<int> actualSolution){
    int temp = actualSolution[edge1];
    actualSolution[edge1] = actualSolution[edge2];
    actualSolution[edge2] = temp;
    return actualSolution;
  }

  std::vector<std::vector<int> > initializeDataStructure(int dimension){
    std::vector<std::vector<int> > dataStructure;
    for (int i = 0; i < dimension; i++){
        dataStructure.push_back(std::vector<int>(dimension));
    }
    return dataStructure;
  }
}
