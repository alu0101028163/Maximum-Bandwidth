#include "TabuSearch.h"

namespace TabuSearch{

  void tabuSearch(std::vector<int> initialSolution, std::vector< std::vector<short int> > graph){

    // Evaluating the initial solution we get the best objective function value for our problem.
    int bestValue = AntiBandwidth::objectiveFunction(graph,initialSolution);

    // We transform the initial solution into the actual solution
    // And also into the best solution
    std::vector<int> currentSolution = initialSolution;
    std::vector<int> bestSolution = initialSolution;


    // Stores frequency of movements in the inferior diagonal and
    // recency of movements in the superior diagonal.
    std::vector<std::vector<int> > recencyFrequencyMatrix = TabuSearch::initializeDataStructure(graph.size());

    for(int i = 0; i < 10; i++){

    MatrixGenerator::print_matrix(recencyFrequencyMatrix,graph.size(), graph.size());
    std::cout << "\n";
    // -------------------------------------------------------------------------
    //                            LOCAL SEARCH
    // -------------------------------------------------------------------------

    // We evaluate all k = 2 swapping combinations and their profit.
    // The solution are two indexes, corresponding to the two nodes that will be swapped.

    int bestLocalI = -1;
    int bestLocalJ = -1;
    int bestLocalValue = -9999;
    int bestLocalFrequency = 99999;

    for(int i = 0; i < graph.size(); i++){
      for(int j = i + 1 ; j < graph[i].size(); j++){
        int actualLocalValue;
        if(((actualLocalValue = evaluateMovement(i,j,currentSolution,graph)) > bestLocalValue) && (recencyFrequencyMatrix[i][j] <= bestLocalFrequency)){

            if((!isTabu(recencyFrequencyMatrix,i,j)) || (actualLocalValue > bestValue)){
                 std::cout << "ACTUAL LOCAL VALUE: " << actualLocalValue << "\n";
                 bestLocalValue = actualLocalValue;
                 bestLocalI = i;
                 bestLocalJ = j;
                 bestLocalFrequency = recencyFrequencyMatrix[i][j];
             }
           }
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
    addTabu(recencyFrequencyMatrix, 3, bestLocalI, bestLocalJ);

  }

  std::cout << "BEST SOLUTION IS: ";
  for(int i = 0; i < bestSolution.size(); i++)
      std::cout << bestSolution[i] << " ";
  std::cout << "\n";
  std::cout << "BEST VALUE IS: " << bestValue << "\n";

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

  bool isTabu(std::vector<std::vector<int> > recencyFrequencyMatrix, int i, int j){
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

  int evaluateMovement(int i, int j , std::vector<int> label, std::vector< std::vector<short int> > graph){
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
