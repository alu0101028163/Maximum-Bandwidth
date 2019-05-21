#include "Grasp.h"




namespace Grasp{

  float PERCENTAGE = 0.5;
  int STRUCTURE = 0;

  std::vector<int> grasp(const std::vector< std::vector<short int> >& graph, int maxIterations, bool eager){
    srand((int)std::time(0));


    std::vector<int> currentSolution;
    for(int i = 1; i <= graph.size(); i++)
        currentSolution.push_back(i);


    int currentValue = AntiBandwidth::objectiveFunction(graph,currentSolution);

    std::vector<int> bestSolution = currentSolution;
    int bestSolutionValue = currentValue;


    int i = 0;
    while((i < maxIterations)){
      currentSolution = constructGreedyRandomizedSolution(graph, currentSolution);
      localSearch(currentSolution, graph);
      bool isBetter = updateSolution(bestSolutionValue, bestSolution, currentSolution, graph);
      if(isBetter && eager){
         return bestSolution;
      }
      i++;
    }

    return bestSolution;

  }


  bool updateSolution(int& bestSolutionValue, std::vector<int>& bestSolution, std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){
      int currentValue = AntiBandwidth::objectiveFunction(graph,currentSolution);
      if(currentValue  > bestSolutionValue){
         bestSolution = currentSolution;
         bestSolutionValue = currentValue;
         return true;
      }
         return false;
  }

  void localSearch(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){


    switch(STRUCTURE){
      case 0:
      simpleExchange(currentSolution,graph);
      break;

      case 1:
      cyclicAdjExchange(currentSolution, graph);
      break;

      case 2:
      doubleExchange(currentSolution, graph);
      break;
    }
  }

  void doubleExchange(std::vector<int>&  currentSolution, const std::vector<std::vector<short int>>& graph) {
    int nextObjFunction;
    int oldObjFunction = AntiBandwidth::objectiveFunction(graph, currentSolution);

    for (int i = 0; i < currentSolution.size() - 1; i++) {
      for (int j = i + 1; j < currentSolution.size(); j++) {
        std::swap(currentSolution[i], currentSolution[j]);

        for (int k = 0; k < currentSolution.size() - 1; k++) {
          for (int z = k + 1; z < currentSolution.size(); z++) {
            // Only perform second swap if indexes are different 2 on 2
            if ((k != i || z != j) || (k != j || z != i)) {
              std::swap(currentSolution[k], currentSolution[z]);

              nextObjFunction = AntiBandwidth::objectiveFunction(graph, currentSolution);
              if (nextObjFunction > oldObjFunction){
                return;
              }
              // reverse second swap
              std::swap(currentSolution[k], currentSolution[z]);
            }
          }
        }

        // reverse first swap
        std::swap(currentSolution[i], currentSolution[j]);
      }
    }

    return;

  }

  void simpleExchange(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){
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

  void cyclicAdjExchange(std::vector<int>& currentSolution,const std::vector<std::vector<short int>>& graph) {
  	std::vector<int> currentSolutioncpy = currentSolution;
  	int nextObjFunction;
  	int oldObjFunction = AntiBandwidth::objectiveFunction(graph, currentSolution);

  	for (int i = 0; i < currentSolution.size(); i++) {

  		for (int j = i - 1; j > 0; j--) {
  			std::swap(currentSolution[j], currentSolution[j + 1]);

  			nextObjFunction = AntiBandwidth::objectiveFunction(graph, currentSolution);
  			if (nextObjFunction > oldObjFunction)
  				return;
  		}

  		currentSolution = currentSolutioncpy;		// Resets are performed in-between consecutive swaps procedures

  		for (int j = i + 1; j < currentSolution.size(); j++) {
  			std::swap(currentSolution[j], currentSolution[j - 1]);

  			nextObjFunction = AntiBandwidth::objectiveFunction(graph, currentSolution);
  			if (nextObjFunction > oldObjFunction)
  				return;
  		}
  	}
  	return;
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

  void constructSolution(int actualNode, const std::vector< std::vector<short int> >& graph, std::list<int>& remainingLabels, std::vector<int>& labeling){

         for(int j = 0; j < graph.size(); j++){
           if((graph[actualNode][j] == 1) && (!isVisited(j, labeling))){
               labeling[j] = calculateLabel(actualNode,remainingLabels,labeling);
               constructSolution(j,graph,remainingLabels,labeling);
           }
         }
  }

  //TODO: calculateLabelElement
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

  void setPercentage(float percentage){
    PERCENTAGE = percentage;
  }

  void setStructure(int structure){
    STRUCTURE = structure;
  }




}
