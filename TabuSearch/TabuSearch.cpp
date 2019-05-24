#include "TabuSearch.h"

namespace TabuSearch{

  int intensificationCoefficient = 10;
  int diversificationCoefficient = 3;
  int tabuCoefficient = 3;


  void setTabuCoefficient(int tabuCoef){
    tabuCoefficient = tabuCoef;
  }

  void setIntensificationCoefficient(int intensifCoef){
    intensificationCoefficient = intensifCoef;
  }

  void setDiversificationCoefficient(int diversifCoef){
    diversificationCoefficient = diversifCoef;
  }

  std::vector<int> tabuSearch(std::vector<int> initialSolution, std::vector< std::vector<short int> > graph, int maxIterations){


      // Evaluating the initial solution we get the best objective function value for our problem.
      int bestValue = AntiBandwidth::objectiveFunction(graph,initialSolution);

      // We transform the initial solution into the actual solution
      // And also into the best solution
      std::vector<int> currentSolution = initialSolution;
      std::vector<int> bestSolution = initialSolution;


      // Stores frequency of movements in the inferior diagonal and
      // recency of movements in the superior diagonal.
      std::vector<std::vector<int> > recencyFrequencyMatrix = TabuSearch::initializeDataStructure(graph.size());

      int iteration = 10;

      bool intensification = false;
      int noImprovementCounter = 0;
      int intensificationCounter = 0;


      while(true){


      // -------------------------------------------------------------------------
      //                            LOCAL SEARCH
      // -------------------------------------------------------------------------

      // We evaluate all k = 2 swapping combinations and their profit.
      // The solution are two indexes, corresponding to the two nodes that will be swapped.

      int bestLocalI = -1;
      int bestLocalJ = -1;
      int bestLocalValue = -1;
      float bestLocalRatio = -1;

      for(int i = 0; i < graph.size(); i++){
        for(int j = i + 1 ; j < graph[i].size(); j++){
          int actualLocalValue = evaluateMovement(i,j,currentSolution,graph);
          int actualRatio = ((actualLocalValue + 1) / (recencyFrequencyMatrix[j][i] + 1));

          if(intensification){
            if((isTabu(recencyFrequencyMatrix,i,j)) && (actualLocalValue > bestValue) && (actualRatio > bestLocalRatio)){
              bestLocalValue = actualLocalValue;
              bestLocalI = i;
              bestLocalJ = j;
              bestLocalRatio = ((actualLocalValue + 1) / (recencyFrequencyMatrix[j][i] + 1));

            }else if ((!isTabu(recencyFrequencyMatrix,i,j)) && (actualRatio > bestLocalRatio)){
              bestLocalValue = actualLocalValue;
              bestLocalI = i;
              bestLocalJ = j;
              bestLocalRatio = ((actualLocalValue + 1) / (recencyFrequencyMatrix[j][i] + 1));
            }
          }else{
            if((isTabu(recencyFrequencyMatrix,i,j)) && (actualLocalValue > bestValue)){
              bestLocalValue = actualLocalValue;
              bestLocalI = i;
              bestLocalJ = j;
              bestLocalRatio = ((actualLocalValue + 1) / (recencyFrequencyMatrix[j][i] + 1));

            }else if (!isTabu(recencyFrequencyMatrix,i,j) && (actualLocalValue > bestLocalValue)){
              bestLocalValue = actualLocalValue;
              bestLocalI = i;
              bestLocalJ = j;
              bestLocalRatio = ((actualLocalValue + 1) / (recencyFrequencyMatrix[j][i] + 1));
            }
          }



        }
      }

    /* No ha mejorado la solución */
    if(bestLocalValue <= bestValue){
      if(!intensification){
         noImprovementCounter += 1;
      }else intensificationCounter += 1;
    }


    if(!intensification){
      if(noImprovementCounter == diversificationCoefficient){
         noImprovementCounter = 0;
         intensification = true;
      }
    }else{
      if(intensificationCounter == intensificationCoefficient){
        intensificationCounter = 0;
        intensification = false;
      }
    }

    // Now we've the best local solution ( it can be worst than the previous solution )
    // and it becomes the currentSolution.
    // If the value obtained is better than the best solution at the momment we update the
    // best solution.
    swap(bestLocalI, bestLocalJ, currentSolution);
    updateBestSolution(bestSolution, bestValue, currentSolution, bestLocalValue);

    // We update the tabu values of the recencyFrequencyMatrix
    updateRecFreqMatrix(recencyFrequencyMatrix);
    // And now we set the actual movement as tabu movement
    addTabu(recencyFrequencyMatrix, tabuCoefficient , bestLocalI, bestLocalJ);

    iteration += 1;
  }

  std::cout << "BEST SOLUTION IS: ";
  for(int i = 0; i < bestSolution.size(); i++)
      std::cout << bestSolution[i] << " ";
  std::cout << "\n";
  std::cout << "BEST VALUE IS: " << bestValue << "\n";
  std::cout << "Nº ITERATIONS IS: " << iteration << "\n";

  return bestSolution;

  }


  void updateRecFreqMatrix(std::vector<std::vector<int> >& recencyFrequencyMatrix){
    for(int i = 0; i < recencyFrequencyMatrix.size(); i++){
      for(int j = i + 1; j < recencyFrequencyMatrix.size(); j++){
        if(isTabu(recencyFrequencyMatrix, i, j)){
           recencyFrequencyMatrix[i][j] -= 1; // We decrement tabu time.
        }
      }
    }
  }

  bool isTabu(std::vector<std::vector<int> >& recencyFrequencyMatrix, int i, int j){
    return (recencyFrequencyMatrix[i][j] > 0);
  }

  void addTabu(std::vector<std::vector<int> >& recencyFrequencyMatrix, int period, int i, int j){
    recencyFrequencyMatrix[i][j] = period; // Add tabu
    recencyFrequencyMatrix[j][i] += 1;     // Increment frequency
  }

  void updateBestSolution(std::vector<int>& bestSolution, int& bestValue, std::vector<int>& currentSolution, int& currentValue){
    if(currentValue > bestValue){
       bestValue = currentValue;
       bestSolution = currentSolution;
       std::cout << "CURRENT BEST VALUE IS: " << bestValue << "\n";
    }
  }

  std::vector<int> generateRandomSolution(int numberOfVertexs){

    // Vector where label will be stored.
    std::vector<int> label;

    for (int i = 1; i <= numberOfVertexs; i++){
      label.push_back(i);
    }

    std::next_permutation(std::begin(label),std::end(label));

    return label;
  }


  void swap(int i, int j , std::vector<int>& label){
    int temp = label[i];
    label[i] = label[j];
    label[j] = temp;
  }

  int evaluateMovement(int i, int j , std::vector<int> label, std::vector< std::vector<short int> >& graph){
    swap(i,j,label);
    return AntiBandwidth::objectiveFunction(graph,label);
  }

  std::vector<std::vector<int> > initializeDataStructure(int dimension){
    std::vector<std::vector<int> > dataStructure;
    for (int i = 0; i < dimension; i++){
        dataStructure.push_back(std::vector<int>(dimension));
    }
    return dataStructure;
  }
}
