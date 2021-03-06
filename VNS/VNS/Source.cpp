#include <iostream>

#include "Grasp.h"
#include "vns.h"
#include "DeterministAlgorithm.h"


// ------------------------------------------------------------------------------------------------------
//						THIS MAIN IS EFFECTIVELY USED FOR ON-THE-RUN TESTING ONLY
//										
// ------------------------------------------------------------------------------------------------------


// "C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\bcspwr01.mtx.rnd"
int main() {

	try {
		std::vector<std::vector<short int> >
			adjMatrix = GraphGen::disperseFileToGraph(false, 
				"C:\\Users\\Fernando\\Documents\\GitHub\\ABM_DAA\\Literature_Instances\\hb\\bcspwr01.mtx.rnd");

		std::random_device rd;
		std::mt19937 generator{ rd() };

		// Exchange for random labeling generator / GRASP
		Grasp::setPercentage(0.6);
		AntiBandwidth::solutionT labels = Grasp::grasp(adjMatrix, 100, std::numeric_limits<int>::max());
	

		labels = VNS::GVNS(adjMatrix, rd);
		VNS::traceSolution(labels, adjMatrix);
	
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	system("PAUSE");

	return 0;
}