#include "vns.h"

AntiBandwidth::solutionT VNS::VND(
	AntiBandwidth::solutionT init_solution, 
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	AntiBandwidth::solutionT bestSol, compSol;
	int k;	// Neighboring function index

	do {
		bestSol = init_solution;
		k = 0;

		do {
			compSol = nstructs[k](init_solution, adjMatrix);
			
			if (compSol != init_solution) {		
				init_solution = compSol;
				k = 0;
			}
			else {			// No better solutions found
				k++;
			}
		
		} while (k < nstructs.size());

		// if equal, gets out of the loop too
	} while (AntiBandwidth::objectiveFunction(adjMatrix, bestSol) > AntiBandwidth::objectiveFunction(adjMatrix, init_solution));

	return init_solution;
}

AntiBandwidth::solutionT VNS::BVNS(
	AntiBandwidth::solutionT init_solution,
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	return AntiBandwidth::solutionT();
}


void VNS::traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >& adjMatrix) {
	for (int i = 0; i < sol.size(); i++)
		std::cout << sol[i] << ", ";
	std::cout << "\t" << AntiBandwidth::objectiveFunction(adjMatrix, sol) << std::endl;
}