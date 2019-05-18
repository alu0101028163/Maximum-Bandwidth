#include <iostream>

#include "neighborhood.h"

int main() {

	std::vector<std::vector<short int> > adjMatrix = GraphGen::disperseFileToGraph("Text.txt");
	AntiBandwidth::solutionT labels = { 1, 2, 3, 4, 5 };

	AntiBandwidth::solutionT nextlabels = NeighborStructs::cyclicAdjExchange(labels, adjMatrix);

	for (int i = 0; i < nextlabels.size(); i++)
		std::cout << nextlabels[i] << ", ";
	std::cout << std::endl;

	
	system("PAUSE");

	return 0;
}