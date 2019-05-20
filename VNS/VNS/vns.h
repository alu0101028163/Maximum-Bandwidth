#pragma once

#include "AntiBandwidth.h"
#include "neighborhood.h"
#include "GraphGenerator.h"

namespace VNS {

	typedef AntiBandwidth::solutionT(*VNS)(const std::vector<std::vector<short int> >& adjMatrix);


	// -------------------------------------------------------------------------------------------------
	//											  VND_LS
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
	//												VND
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT VND(const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//											   BVNS
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT BVNS(const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//										   AUX METHODS
	// -------------------------------------------------------------------------------------------------

	void traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >&);
}