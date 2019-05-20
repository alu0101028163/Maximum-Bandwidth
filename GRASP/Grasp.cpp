#include "Grasp.h"




namespace Grasp{

  float PERCENTAGE = 0.5;

  std::vector<int> grasp(const std::vector< std::vector<short int> >& graph, int maxIterations, int objectiveValue){
    srand((int)std::time(0));


    std::vector<int> currentSolution;
    for(int i = 1; i <= graph.size(); i++)
        currentSolution.push_back(i);


    int currentValue = AntiBandwidth::objectiveFunction(graph,currentSolution);

    std::vector<int> bestSolution = currentSolution;
    int bestSolutionValue = currentValue;


    int i = 0;
    while((i < maxIterations) && (currentValue < objectiveValue)){
      currentSolution = constructGreedyRandomizedSolution(graph, currentSolution);
      localSearch(currentSolution, graph);
      updateSolution(bestSolutionValue, bestSolution, currentSolution, graph);
      i++;
    }

    return bestSolution;

  }


  void updateSolution(int& bestSolutionValue, std::vector<int>& bestSolution, std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){
      int currentValue = AntiBandwidth::objectiveFunction(graph,currentSolution);
      if(currentValue  > bestSolutionValue){
         bestSolution = currentSolution;
         bestSolutionValue = currentValue;
      }
  }

  void localSearch(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){

       int bestI = -1;
       int bestJ = -1;
       int bestValue = AntiBandwidth::objectiveFunction(graph,currentSolution);

       for(int i = 0; i < currentSolution.size(); i++){
         for(int j = 0; j < currentSolution.size(); j++){
           int actualValue;
           if((actualValue = evaluateMovement(i,j,currentSolution,graph)) > bestValue){
             bestI = i;
             bestJ = j;
             bestValue = actualValue;
           }
         }
       }

       if((bestI != -1) && (bestJ != -1)){
         swap(bestI,bestJ,currentSolution);
       }

  }


  void swap(int i, int j , std::vector<int>& label){
    int temp = label[i];
    label[i] = label[j];
    label[j] = temp;
  }

  int evaluateMovement(int i, int j , std::vector<int> label, const std::vector< std::vector<short int> >& graph){
    swap(i,j,label);
    return AntiBandwidth::objectiveFunction(graph,label);
  }


  std::vector<int> constructGreedyRandomizedSolution(const std::vector< std::vector<short int> >& graph, std::vector<int>& solutionElements){

        std::list<int> remainingLabels;
        std::copy(solutionElements.begin(), solutionElements.end(), std::back_inserter(remainingLabels));
        std::vector<int> labeling(graph.size());

        int label = getRandomLabel(remainingLabels);
        labeling[0] = label;

        remainingLabels.remove(label);

        constructSolution(0,graph,remainingLabels,labeling);

        return labeling;

  }

  /*
    TODO: The statement if(remainingLabels.size() <= 0) break; is saving the program
    of a segmentation fault, but i think it shouldn't be necessary because of the (!isVisited(j, labeling) condition.
    Track the problem down.
   */
  void constructSolution(int actualNode, const std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling){

      // std::cout << "ACTUAL NODE: " << actualNode << "\n";

       for(int i = actualNode; i < graph.size(); i++){
         // std::cout << "ACTUAL NODE: " << i << "\n";
         for(int j = 0; j < graph.size(); j++){
           if((graph[i][j] == 1) && (!isVisited(j, labeling))){
              // std::cout << "ACTUAL j: " << j << "\n";
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

  /* TODO: Here I'm getting a segmentation fault because the differences vector is empty,
           I'm guessing returning 0 will solve the problem but this needs check out */
  int calculateCardinality(int parentNode, std::list<int>& remainingLabels, std::vector<int>& labeling){
    std::vector<int> differences = calculateDifferences(parentNode, remainingLabels, labeling);
    // if(differences.size() == 0) return 0;

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

  void setPercentage(float percentage){
    PERCENTAGE = percentage;
  }




}
