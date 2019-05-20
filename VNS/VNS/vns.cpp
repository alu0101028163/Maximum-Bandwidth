#include "vns.h"

AntiBandwidth::solutionT VNS::VND_LS(AntiBandwidth::solutionT sol, const std::vector<std::vector<short int>>& adjMatrix,
	const std::vector<NeighborStructs::detNeighStructFunction>& n_structs) {

	int k = 0;
	AntiBandwidth::solutionT compSol;

	do {
		compSol = n_structs[k](sol, adjMatrix);

		if (compSol != sol) {
			sol = compSol;
			k = 0;
		}
		else {			// No better solutions found
			std::cout << "Next struct: " << k + 1 << std::endl;
			k++;
		}
	} while (k < n_structs.size());

	return sol;
}

AntiBandwidth::solutionT VNS::VND(const std::vector<std::vector<short int>>& adjMatrix) {

	int non_improved_it = 0;
	AntiBandwidth::solutionT labeling;

	while (non_improved_it < 10) {
		labeling = Grasp::grasp(adjMatrix, 100, 17);

	}

	return AntiBandwidth::solutionT();
}

AntiBandwidth::solutionT VNS::GVNS(const std::vector<std::vector<short int>>& adjMatrix) {
	
	return AntiBandwidth::solutionT();
}


void VNS::traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >& adjMatrix) {
	for (int i = 0; i < sol.size(); i++)
		std::cout << sol[i] << ", ";
	std::cout << "\t" << AntiBandwidth::objectiveFunction(adjMatrix, sol) << std::endl;
}