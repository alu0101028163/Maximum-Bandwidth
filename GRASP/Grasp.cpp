#include "Grasp.h"


std::vector<std::vector<short int>> fileRead(const std::string &filename, bool isDense){
    std::vector<std::vector<short int> >  adjacencyMatrix;

    if(isDense == 1){
        adjacencyMatrix = ABM::denseFileToGraph(filename);
    }
    else if(isDense == 0){
        adjacencyMatrix = ABM::disperseFileToGraph(filename);
    }
    return adjacencyMatrix;
}

std::vector<short int> candidateList(std::vector<std::vector<short int>>& adjacencyMatrix){
    std::vector<short int> candiatesList;

    for ( int i = 1; i <= adjacencyMatrix.size(); ++i ) {
        candiatesList.push_back(i);
    }
    return candiatesList;

    //TODO
    //  Check that it works good.
}

void candidatelistEraseElement(std::vector<short int>& auxVec, short int toDelete){
    int i = 0;
    bool found = false;
    while (i < auxVec.size() && !found){
        if(auxVec[i] == toDelete)
            found = true;
        else
            i++;
    }
    if(found)
        auxVec.erase(auxVec.begin() + i);///Erase the element
    else{
        ///BUSCAR EXCEPCIÓN QUE LANZAR
    }
}

std::vector<short int> greedyFunction(std::vector<std::vector<short int>>& adjacencyMatrix,
                                      std::vector<short int>& candidateList, const std::string &filename, bool isDense){

    //Suponemos que ya se ha llamado a "fileRead" y ya tenemos nuestra matriz de adyacencia pasada por referencia.
    //A continuación, deberemos coger y crear la lista de candidatos, la cual supondremos crear fuera de esta función y pasarla por referencia.

    //===========================
    //      VECTORS TO USE
    //===========================

    std::vector<short int> vertex;  ///Vector of vertex of the graph.
    std::vector<short int> value(adjacencyMatrix.size(),0); ///Value of each vertex of the graph.
    std::vector<short int> rcl(RCL_SIZE);     ///Restricted candidate list.
    std::vector<bool>      visited(adjacencyMatrix.size(), 0); ///Vector of 1 (true) or 0 (false) for represent visited vertex.
    std::vector<short int> index(adjacencyMatrix.size()); ///Vector that contains the indexes to access our other vector(vertex).

    //============================

    std::iota(vertex.begin(), vertex.end(), 1);
    std::iota(index.begin(), index.end(), 0);

    //A continuación, buscamos un nodo aleatorio por el cual comenzar:

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( index.begin(), index.end() );

    short int chosenVertex = index[0];

    //Seguidamente, se busca el valor aleatorio para ese nodo:

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( index.begin(), index.end() );

    short int randomValue = index[0];

    //Asignamos el valor al nodo y lo marcamos como visitado:

    value[chosenVertex] = randomValue;
    visited[chosenVertex] = true;

    //Ahora eliminamos de la lista de candidatos el valor elegido.
    candidatelistEraseElement(candidateList, randomValue);

    //Llenamos la rcl:
    int i = 0;
    int j = 0;
    int k = 0;
    while(i < rcl.size()){
        /*
         * Ahora mismo está planteada la rcl para que tenga un tmaño fijo (4). Si queremos que sea variable, hay que buscar otra alternativa.
         */
        if(j < adjacencyMatrix.size()) {
            if ((candidateList[j] == randomValue + 1) || (candidateList[j] == randomValue + 2) ||
                (candidateList[j] == randomValue - 1) ||
                (candidateList[j] == randomValue - 2)) {
                rcl.push_back(candidateList[j]);
                candidatelistEraseElement(candidateList, candidateList[j]);
                i++;
            }
            j++;
        } else
            j = 0;
    }

    //TODO
    // Comprobar los vértices con los que está conectado el vertice escogido aleatoriamente. Si no hacemos esto, la rcl no estará bien.









}