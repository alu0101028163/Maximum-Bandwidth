#pragma once

#include "../../GRASP/Grasp.h"
#include "../../GraphGenerator/GraphGenerator.h"
#include "../../AntiBandwidth/AntiBandwidth.h"
#include "../../NeighborhoodStructs/neighborhood.h"

namespace VNS {

	static int MAX_N_ITER_WO_IMPROVEMENT = 10;

	typedef AntiBandwidth::solutionT(*VNS)(const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//										VND-BASED LOCAL SEARCH
	// -------------------------------------------------------------------------------------------------

	/**
		This local search procedure is based on the VND algorithm, and uses neighborhood structures defined
		in NeighborStructs.
		@param sol is the initial labeling to which the local search will be applied
		@param adjMatrix is the non-directed graph defining structure, an adjacency matrix
		@param n_structs is an array containing the different neighbor search functions

		@return an improved labeling (based on Antibandwidth::objectiveFunction) if found.
				If provided sol is already a local optimum, return sol
	*/
	AntiBandwidth::solutionT VND_LS(AntiBandwidth::solutionT sol,
		const std::vector<std::vector<short int> >& adjMatrix,
		const std::vector<NeighborStructs::detNeighStructFunction>& n_structs);

	// -------------------------------------------------------------------------------------------------
	//										  STANDALONE VND
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT VND(const std::vector<std::vector<short int> >& adjMatrix);

	AntiBandwidth::solutionT VND(const std::vector<std::vector<short int> >& adjMatrix, const AntiBandwidth::solutionT& init_sol);

	// -------------------------------------------------------------------------------------------------
	//										GVNS IMPLEMENTATION
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT GVNS(const std::vector<std::vector<short int> >& adjMatrix, std::random_device& rd);

	AntiBandwidth::solutionT GVNS(const std::vector<std::vector<short int> >& adjMatrix, const AntiBandwidth::solutionT& init_sol,
		std::random_device& rd);

	// -------------------------------------------------------------------------------------------------
	//										 AUXILIAR METHODS
	// -------------------------------------------------------------------------------------------------

	void traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >&);

	void setMaxNIIterations(int iter);
}
