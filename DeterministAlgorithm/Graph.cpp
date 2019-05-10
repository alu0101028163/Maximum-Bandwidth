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

Graph::~Graph(){}


void Graph::printGraph(){
  for (int i = 0; i < adjacencyMatrix_.size(); i++) {
    for (int j = 0; j < adjacencyMatrix_[i].size(); j++) {
      std::cout << adjacencyMatrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Graph::getSize(){
  return adjacencyMatrix_.size();
}

std::vector<short int>& Graph::operator[] (int x){
  return adjacencyMatrix_[x];
}
