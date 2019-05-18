#include "AntiBandwidth.h"


namespace AntiBandwidth{

  int objectiveFunction( std::vector< std::vector<short int> > graph, std::vector<int> label){

    int min = std::numeric_limits<int>::max();

    int result = 0;

    // For every node in the graph
    for (int i = 0; i < graph.size(); i++){
      // For every neighbour of that node.
      for (int j = i + 1; j < graph[i].size(); j++){
        // If there's a connection
        if(graph[i][j] == 1)
          // Measure the distance and if it's minimum update
          // the minimum value of the objective function.
          if((result = abs(label[i] - label[j])) < min)
              min = result;
      }
    }

    return min;

  }

}
