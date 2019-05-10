#include "Graph.h"

Graph::Graph(const std::string & instance){
  std::ifstream infile(instance);

  int nVertexs;
  infile >> nVertexs;

  int value;
  short int temp;

  for(int i = 0; i < nVertexs; i++){
    adjacencyMatrix_.push_back(std::vector<short int>());
    for (int j = 0; j < nVertexs; j++){
      infile >> temp;
      adjacencyMatrix_[i].push_back(temp);
    }
  }

  infile.close();
}

void Graph::printGraph(){
  ABM::traceGeneratedMatrix(adjacencyMatrix_);
}

Graph::~Graph(){
}
