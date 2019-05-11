#include "AntiBandwidth.h"

namespace AntiBandwith{

  int objectiveFunction( std::vector< std::vector<short int> > graph, std::vector<int> label){

    int min = std::numeric_limits<int>::max();

    int result = 0;

    // For every node in the graph
    for (int i = 0; i < graph.size(); i++){
      // For every neighbour in the graph
      for (int j = i + 1; j < graph[i].size(); j++){
        if(graph[i][j] == 1)
          if((result = abs(label[i] - label[j])) < min)
              min = result;
      }
    }

    return min;

  }

}
