#include "AntiBandwith.h"

namespace AntiBandwith{

  int objectiveFunction(Graph graph, std::vector<int> label){

    int min = std::numeric_limits<int>::max();

    int result = 0;

    for (int i = 0; i < graph.getSize(); i++){
      for (int j = i + 1; j < graph[i].size(); i++){
        if(result = (graph[i][i] * label[i] - graph[i][j]) < min)
           min = result;
      }
    }

    return min;

  }

}
