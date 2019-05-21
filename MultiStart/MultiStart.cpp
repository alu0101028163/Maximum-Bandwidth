
#include "MultiStart.h"


std::vector<int> MultiStart::randomVector(int numVertex){

    // We initialize the labels vector inserting a label
    // with values from 1 to numVertex
    std::vector<int> randomlabel;
    for (int i = 1; i <= numVertex; i++){
        randomlabel.push_back(i);
    }

    std::random_shuffle ( randomlabel.begin(), randomlabel.end() );

    return randomlabel;
}

void MultiStart::swap(int i, int j , std::vector<int>& label){
    int temp = label[i];
    label[i] = label[j];
    label[j] = temp;
}

int MultiStart::evaluateMovement(int i, int j , std::vector<int> label, const std::vector< std::vector<short int> >& graph){
    swap(i,j,label);
    return AntiBandwidth::objectiveFunction(graph,label);
}

void MultiStart::doubleExchange(std::vector<int>&  currentSolution, const std::vector<std::vector<short int>>& graph) {
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

void MultiStart::simpleExchange(std::vector<int>& currentSolution, const std::vector< std::vector<short int> >& graph){
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

void MultiStart::cyclicAdjExchange(std::vector<int>& currentSolution,const std::vector<std::vector<short int>>& graph) {
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

void MultiStart::calculateNeighborhood(int structureNum, std::vector<int>& curretSolution, std::vector<std::vector<short int> >& adjMatrix){

    switch (structureNum){
        case 1: simpleExchange(curretSolution, adjMatrix);
            break;
        case 2: doubleExchange(curretSolution, adjMatrix);
            break;
        case 3: cyclicAdjExchange(curretSolution, adjMatrix);
            break;
        default:break;
    }
    return;
}

//repetitions -> lleva a cabo el número de repeticiones del calculateNeighborhood.
std::vector<int> MultiStart::multiStart(int structure, const std::string &filename, int repetitions) {

    std::vector<std::vector<short int> > adjMatrix;
    adjMatrix = GraphGen::disperseFileToGraph(filename); // Generamos la matriz de adyacencia;

    std::vector<int> currentSolution = randomVector(adjMatrix.size()); // Vector con la solución inicial.
    int bestOF = AntiBandwidth::objectiveFunction(adjMatrix, currentSolution);
    int neighborhoodOF = 0;

    std::vector<int> bestSolution(currentSolution.size()); // Vector que se pasa a las distintas estructuras de entorno.
    bestSolution = currentSolution;

    for(int i = 0; i < repetitions; ++i){
        calculateNeighborhood(structure, currentSolution, adjMatrix);
        neighborhoodOF = AntiBandwidth::objectiveFunction(adjMatrix, currentSolution);
        if(bestOF < neighborhoodOF){
            bestSolution = currentSolution;
            bestOF = neighborhoodOF;
        }
        currentSolution = randomVector(adjMatrix.size());
    }
    std::cout << "BestsolutionOF " << AntiBandwidth::objectiveFunction(adjMatrix, bestSolution) << "\n";
    for ( int j = 0; j < bestSolution.size() ; ++j ) {
        std::cout << bestSolution[j] << " ";
    }

    return bestSolution;
}
