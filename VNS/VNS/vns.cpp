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
	AntiBandwidth::solutionT bestlabeling = Grasp::grasp(adjMatrix, 100, std::numeric_limits<int>::max(), false);
	AntiBandwidth::solutionT nextlabeling;

	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	while (non_improved_it < 20) {

		nextlabeling = Grasp::grasp(adjMatrix, 100, std::numeric_limits<int>::max() , false);
		nextlabeling = VND_LS(nextlabeling, adjMatrix, nstructs);

		if (AntiBandwidth::objectiveFunction(adjMatrix, bestlabeling) <			// optimize
				AntiBandwidth::objectiveFunction(adjMatrix, nextlabeling)) {
			bestlabeling = nextlabeling;
			non_improved_it = 0;
		}
		else {
			non_improved_it++;
		}
	}

	return bestlabeling;
}

AntiBandwidth::solutionT VNS::GVNS(const std::vector<std::vector<short int>>& adjMatrix, std::random_device& rd) {
	
	int k;
	int non_improved_it = 0;
	bool improvement;

	AntiBandwidth::solutionT bestLabeling;
	AntiBandwidth::solutionT labeling = Grasp::grasp(adjMatrix, 100, std::numeric_limits<int>::max(), false);
	
	std::vector<NeighborStructs::randNeighStructFunction> rn_structs = {
			NeighborStructs::simpleExchangeR,
			NeighborStructs::doubleExchangeR,
			NeighborStructs::quintupleExchangeR
	};
	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	std::uniform_int_distribution<> integer_distribution(0, labeling.size() - 1);
	std::mt19937 generator{ rd() };

	while (non_improved_it < 10) {
		
		improvement = false;
		bestLabeling = labeling;
		k = 0;
		while (k < rn_structs.size()) {
			
			labeling = rn_structs[k](labeling, adjMatrix, generator);
			labeling = VND_LS(labeling, adjMatrix, nstructs);
			
			if (AntiBandwidth::objectiveFunction(adjMatrix, bestLabeling) 
				< AntiBandwidth::objectiveFunction(adjMatrix, labeling)) {

				improvement = true;
				bestLabeling = labeling;
				k = 0;
			}
			else {
				k++;
			}
		}

		if (!improvement) non_improved_it++;
	}

	return bestLabeling;
}


void VNS::traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >& adjMatrix) {
	for (int i = 0; i < sol.size(); i++)
		std::cout << sol[i] << ", ";
	std::cout << "\t" << AntiBandwidth::objectiveFunction(adjMatrix, sol) << std::endl;
}