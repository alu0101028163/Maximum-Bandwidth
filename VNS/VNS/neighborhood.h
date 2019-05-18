#pragma once

#include <utility>										// std::pair and std::swap

#include "../../GraphGenerator/GraphGenerator.h"
#include "AntiBandwidth.h"								// objectiveFunction and solutionT 

// Unify GraphGen and AntiBandwidth namespaces. Serving the same purpose
namespace NeighborStructs {

	//TODO: It would be amazing if this functions could be turned to functors, for once

	/**
		Implementation of Glover and Laguna (1997) candidate list approach for neighborhood searchs,
		applied to the anti-bandwidth maximization problem
	*/
	std::vector<int> GLCandidateList(const AntiBandwidth::solutionT& labeling, const std::vector<std::vector<short int> >& adjMatrix);

	/**
		Atomic operation used in neighbor solution searchs. Exchanges two labels 

		** THIS IS A DUPLICATE: UNIFY WITH TabuSearch::swap!!!
	*/
	void swap(int index1, int index2, AntiBandwidth::solutionT& labeling);

	/**
		This method implements the first neighborhood model with a greedy approach:
			Simple exchange is conformed by the "swap two labels" formula and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.
	*/
	AntiBandwidth::solutionT simpleExchangeGL(const AntiBandwidth::solutionT& labeling, 
		const std::vector<std::vector<short int> >& adjMatrix);

	
	/**
		This method implements the second neighborhood model with a greedy approach:
			Double exchange applies simple exchange, but twice in a row and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.
	*/
	AntiBandwidth::solutionT doubleExchangeGL(const AntiBandwidth::solutionT& labeling, 
		const std::vector<std::vector<short int> >& adjMatrix);

	/**
		This method implements the third neighborhood model with a greedy approach:
			Cyclic Adjacent Exchange performs a series of consecutive swaps of adjacent labels and is
			implemented following the Glover and Laguna technique (1997) with candidate lists
	*/
	AntiBandwidth::solutionT cyclicAdjExchangeGL(const AntiBandwidth::solutionT& labeling, 
		const std::vector<std::vector<short int> >& adjMatrix);
	

	//----------------------------------------------------------------------------------

	AntiBandwidth::solutionT simpleExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);
	
	AntiBandwidth::solutionT doubleExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);
	
	AntiBandwidth::solutionT cyclicAdjExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);
}

