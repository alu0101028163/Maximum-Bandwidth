#include <iostream>

#include "vns.h"
#include "DeterministAlgorithm.h"

// "C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\bcspwr01.mtx.rnd"
int main() {

	try {
		std::vector<std::vector<short int> >
			adjMatrix = GraphGen::disperseFileToGraph(true, 
				"C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\ash85.mtx.rnd");
		AntiBandwidth::solutionT labels;

		// Exchange for random labeling generator / GRASP
		for (int i = 0; i < adjMatrix.size(); i++)
			labels.push_back(i + 1);

		AntiBandwidth::solutionT local_opt = VNS::VND(labels, adjMatrix);
		std::cout << "VND finished!" << std::endl;
		VNS::traceSolution(local_opt, adjMatrix);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	system("PAUSE");

	return 0;
}