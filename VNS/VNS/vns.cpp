#include "vns.h"

// --------------------------------------------------------------------------------------------
//									VND-BASED LOCAL SEARCH
// --------------------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------------------
//										STANDALONE VND
// --------------------------------------------------------------------------------------------

AntiBandwidth::solutionT VNS::VND(const std::vector<std::vector<short int>>& adjMatrix) {

	int non_improved_it = 0;
	AntiBandwidth::solutionT bestlabeling = Grasp::grasp(adjMatrix, 100, false);
	AntiBandwidth::solutionT nextlabeling;

	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	while (non_improved_it < MAX_N_ITER_WO_IMPROVEMENT) {

		nextlabeling = Grasp::grasp(adjMatrix, 100, false);
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

AntiBandwidth::solutionT VNS::VND(const std::vector<std::vector<short int>>& adjMatrix,
	const AntiBandwidth::solutionT & init_sol) {

	int non_improved_it = 0;
	AntiBandwidth::solutionT bestlabeling = init_sol;
	AntiBandwidth::solutionT nextlabeling;

	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	while (non_improved_it < MAX_N_ITER_WO_IMPROVEMENT) {

		nextlabeling = Grasp::grasp(adjMatrix, 100, false);
		nextlabeling = VND_LS(nextlabeling, adjMatrix, nstructs);

		if (AntiBandwidth::objectiveFunction(adjMatrix, bestlabeling) <
			AntiBandwidth::objectiveFunction(adjMatrix, nextlabeling)) {
			bestlabeling = nextlabeling;
			non_improved_it = 0;
		}
		else {
			non_improved_it++;
			std::cout << "Next struct: " << std::endl;
		}
	}

	return bestlabeling;
}

// --------------------------------------------------------------------------------------------
//									 GVNS IMPLEMENTATION
// --------------------------------------------------------------------------------------------

AntiBandwidth::solutionT VNS::GVNS(const std::vector<std::vector<short int>>& adjMatrix, std::random_device& rd) {

	int k;
	int non_improved_it = 0;
	bool improvement;

	AntiBandwidth::solutionT bestLabeling;
	AntiBandwidth::solutionT labeling = Grasp::grasp(adjMatrix, 100, false);

	std::vector<NeighborStructs::randNeighStructFunction> rn_structs = {
			NeighborStructs::simpleExchangeR,
			NeighborStructs::doubleExchangeR,
			NeighborStructs::quintupleExchangeR,
			NeighborStructs::cyclicAdjExchangeR
	};
	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	std::uniform_int_distribution<> integer_distribution(0, labeling.size() - 1);
	std::mt19937 generator{ rd() };

	while (non_improved_it < MAX_N_ITER_WO_IMPROVEMENT) {

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

AntiBandwidth::solutionT VNS::GVNS(const std::vector<std::vector<short int>>& adjMatrix,
	const AntiBandwidth::solutionT & init_sol, std::random_device & rd) {

	int k;
	int non_improved_it = 0;
	bool improvement;

	AntiBandwidth::solutionT bestLabeling;
	AntiBandwidth::solutionT labeling = init_sol;

	std::vector<NeighborStructs::randNeighStructFunction> rn_structs = {
			NeighborStructs::simpleExchangeR,
			NeighborStructs::doubleExchangeR,
			NeighborStructs::quintupleExchangeR,
			NeighborStructs::cyclicAdjExchangeR
	};
	std::vector<NeighborStructs::detNeighStructFunction> nstructs = {
			NeighborStructs::simpleExchange,
			NeighborStructs::doubleExchange,
			NeighborStructs::cyclicAdjExchange
	};

	std::uniform_int_distribution<> integer_distribution(0, labeling.size() - 1);
	std::mt19937 generator{ rd() };

	while (non_improved_it < MAX_N_ITER_WO_IMPROVEMENT) {

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

// --------------------------------------------------------------------------------------------
//									  AUXILIAR METHODS
// --------------------------------------------------------------------------------------------

void VNS::traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >& adjMatrix) {
	for (int i = 0; i < sol.size(); i++)
		std::cout << sol[i] << ", ";
	std::cout << "\t" << AntiBandwidth::objectiveFunction(adjMatrix, sol) << std::endl;
}

void VNS::setMaxNIIterations(int iter) {
	MAX_N_ITER_WO_IMPROVEMENT = iter;
}
