#include <iostream>

#include "neighborhood.h"

int main() {

	std::vector<std::vector<short int> > adjMatrix = GraphGen::disperseFileToGraph("Text.txt");
	AntiBandwidth::solutionT labels = { 1, 2, 3, 4, 5 };

	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	for (int n = 0; n < nstructs.size(); n++) {
		AntiBandwidth::solutionT nextlabels = nstructs[n](labels, adjMatrix);
		
		for (int i = 0; i < nextlabels.size(); i++)
			std::cout << nextlabels[i] << ", ";
		std::cout << std::endl;

	}
	system("PAUSE");

	return 0;
}