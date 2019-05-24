#pragma once

#include "../../AntiBandwidth/AntiBandwidth.h"
#include "../../NeighborhoodStructs/neighborhood.h"
#include "../../GraphGenerator/GraphGenerator.h"
#include "../../GRASP/Grasp.h"

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

	/**
		Implementation of VND standalone procedure with fixed neighborhood structs (simple, double, cyclic exchange)
		@param adjMatrix is the non-directed graph defining structure, an adjacency matrix

		@return best labeling obtained from iterating through VND local searchs on GRASP-generated labels
	*/
	AntiBandwidth::solutionT VND(const std::vector<std::vector<short int> >& adjMatrix);

	/**
		Implementation of VND standalone procedure with fixed neighborhood structs (simple, double, cyclic exchange)
		@param adjMatrix is the non-directed graph defining structure, an adjacency matrix
		@param init_sol is the initial "best value" computed by GRASP

		@return best labeling obtained from iterating through VND local searchs on GRASP-generated labels
	*/
	AntiBandwidth::solutionT VND(const std::vector<std::vector<short int> >& adjMatrix, const AntiBandwidth::solutionT& init_sol);

	// -------------------------------------------------------------------------------------------------
	//										GVNS IMPLEMENTATION
	// -------------------------------------------------------------------------------------------------

	/**
		Implementation of GVNS with random shake procedure based on fixed neighborhood structures
		(simple, double, quintuple, cyclic exchange)
		@param adjMatrix
		@param rd is the random component of neighbor obtention
	*/
	AntiBandwidth::solutionT GVNS(const std::vector<std::vector<short int> >& adjMatrix, std::random_device& rd);

	/**
		Implementation of GVNS with random shake procedure based on fixed neighborhood structures
		(simple, double, quintuple, cyclic exchange)
		@param adjMatrix
		@param init_sol is the starting "best value", computed with GRASP
		@param rd is the random component of neighbor obtention
	*/
	AntiBandwidth::solutionT GVNS(const std::vector<std::vector<short int> >& adjMatrix, const AntiBandwidth::solutionT& init_sol,
		std::random_device& rd);

	// -------------------------------------------------------------------------------------------------
	//										 AUXILIAR METHODS
	// -------------------------------------------------------------------------------------------------

	/**
		Prints a certain labelling passed by parameter
		@param sol is said labelling
	*/
	void traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >&);

	/**
		Sets a static variable utilized in VNS algorithm
		@param iter is the new number of maximum iterations without improvement
	*/
	void setMaxNIIterations(int iter);
}
