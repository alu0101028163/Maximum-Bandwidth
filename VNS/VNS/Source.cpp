#include <iostream>

#include "Grasp.h"
#include "vns.h"
#include "DeterministAlgorithm.h"

// "C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\bcspwr01.mtx.rnd"
int main() {

	try {
		std::vector<std::vector<short int> >
			adjMatrix = GraphGen::disperseFileToGraph(false, 
				"C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\bcspwr01.mtx.rnd");

		// Exchange for random labeling generator / GRASP
		Grasp::setPercentage(0.6);
		AntiBandwidth::solutionT labels = Grasp::grasp(adjMatrix, 100, 17);

		std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
		};

		std::cout << "Finished GRASP" << std::endl;
		VNS::traceSolution(labels, adjMatrix);

		labels = VNS::VND_LS(labels, adjMatrix, nstructs);
		std::cout << "Finished VND" << std::endl;
		VNS::traceSolution(labels, adjMatrix);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	system("PAUSE");

	return 0;
}