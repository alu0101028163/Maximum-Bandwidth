#include "Grasp.h"




namespace Grasp{

  //
  // void grasp(std::vector< std::vector<short int> >& graph, int maxIterations, int objectiveValue){
  //   srand((int)time(0));
  //
  //
  //   std::vector<int> solutionElements;
  //   for(int i = 1; i <= graph.size(); i++)
  //       solutionElements.push_back(i);
  //
  // }




  void constructGreedyRandomizedSolution(std::vector< std::vector<short int> >& graph, std::vector<int>& solutionElements){

        // std::vector<short int> visitedNodes;
        std::list<int> remainingLabels;
        std::copy(solutionElements.begin(), solutionElements.end(), std::back_inserter(remainingLabels));
        std::vector<int> labeling(graph.size());

        int label = getRandomLabel(remainingLabels);
        labeling[0] = label;

        remainingLabels.remove(label);

        constructSolution(0,graph,remainingLabels,labeling);

  }


  void constructSolution(int actualNode, std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling){
       for(int i = actualNode; i < graph.size(); i++){
         for(int j = 0; j < graph.size(); j++){
           if((graph[i][j] == 1) && (!isVisited(j, labeling))){
               labeling[j] = calculateLabel(i,remainingLabels,labeling);
               constructSolution(j,graph,remainingLabels,labeling);
           }
         }
       }
  }


  int calculateLabel(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling){

    std::vector<int> candidateList = calculateCandidateList(parentNode, remainingLabels, labeling);

    int randomCandidate = getRandomLabel(candidateList);
    remainingLabels.remove(randomCandidate);

    return randomCandidate;

  }

  std::vector<int> calculateCandidateList(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling){
    int cardinality = calculateCardinality(parentNode, remainingLabels, labeling);

    std::vector<int> candidateList;

    int result = 0;

    for (auto it = remainingLabels.begin(); it != remainingLabels.end(); it++){
        result = abs(labeling[parentNode] - *it);

        if(result >= (cardinality * PERCENTAGE)){
           candidateList.push_back(*it);
        }
      }

    return candidateList;
  }

  std::vector<int> calculateDifferences(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling){
    std::vector<int> differences;
    int result = 0;

    for (auto it = remainingLabels.begin(); it != remainingLabels.end(); it++){
        result = abs(labeling[parentNode] - *it);
        differences.push_back(result);
      }
    return differences;
  }

  int calculateCardinality(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling){
    std::vector<int> differences = calculateDifferences(parentNode, remainingLabels, labeling);
    return *std::max_element(std::begin(differences), std::end(differences));
  }

  bool isVisited(int node, std::vector<int>& labeling){
       if(labeling[node] != 0)
          return true;
       else return false;
  }

  int getRandomLabel(std::vector<int>& labels){
      int label = 0;
      if(labels.size() > 1){
        label = (rand() % (labels.size() - 1)) + 1;
      }
      return labels[label];
  }

  int getRandomLabel(std::list<int>& labels){
      int nLabel = 0;

      if(labels.size() > 1){
         nLabel = (rand() % (labels.size() - 1)) + 1;
      }

      std::list<int>::iterator it = labels.begin();
      std::advance(it, nLabel);
      return *it;
  }





}
