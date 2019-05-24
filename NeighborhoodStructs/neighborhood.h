#pragma once

#include <utility>										// std::pair and std::swap

#include "../GraphGenerator/GraphGenerator.h"
#include "../AntiBandwidth/AntiBandwidth.h"								// objectiveFunction and solutionT

namespace NeighborStructs {

	// ------------------------------------------------------------------------------------
	//								STRATEGY PATTERN: C-Style
	// ------------------------------------------------------------------------------------

	typedef AntiBandwidth::solutionT(*detNeighStructFunction) (const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	typedef AntiBandwidth::solutionT(*randNeighStructFunction) (AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix, std::mt19937& generator);

	// ---------------------------------------------------------------------------------------
	//					    CANDIDATE LIST NEIGHBORHOOD EXPLORATION
	// ---------------------------------------------------------------------------------------

	/**
		Implementation of Glover and Laguna (1997) candidate list approach for neighborhood searchs,
		applied to the anti-bandwidth maximization problem

		DISCLAIMER: Not implemented
	*/
	std::vector<int> GLCandidateList(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	/**
		This method implements the first neighborhood model with a greedy approach:
			Simple exchange is conformed by the "swap two labels" formula and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.

		DISCLAIMER: Not implemented
	*/
	AntiBandwidth::solutionT simpleExchangeGL(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);


	/**
		This method implements the second neighborhood model with a greedy approach:
			Double exchange applies simple exchange, but twice in a row and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.

		DISCLAIMER: Not implemented
	*/
	AntiBandwidth::solutionT doubleExchangeGL(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	/**
		This method implements the third neighborhood model with a greedy approach:
			Cyclic Adjacent Exchange performs a series of consecutive swaps of adjacent labels and is
			implemented following the Glover and Laguna technique (1997) with candidate lists

		DISCLAIMER: Not implemented
	*/
	AntiBandwidth::solutionT cyclicAdjExchangeGL(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	// --------------------------------------------------------------------------------------
	//							ANXIOUS NEIGHBORHOOD EXPLORATION
	// --------------------------------------------------------------------------------------

	/**
		Simple Exchange Neighborhood, returns a neighboring solution to one provided, using an
		eager exploration criteria.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
	AntiBandwidth::solutionT simpleExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

<<<<<<< HEAD
	AntiBandwidth::solutionT doubleExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

=======
	/**
		Double Exchange Neighborhood, returns a neighboring solution to one provided, using an
		eager exploration criteria.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
	AntiBandwidth::solutionT doubleExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	/**
		Cyclic Adjacent Swap Neighborhood, returns a neighboring solution to one provided, using an
		eager exploration criteria.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
>>>>>>> f2050b1f182ece8afbf5e5bdb41d3314679b3b11
	AntiBandwidth::solutionT cyclicAdjExchange(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	// --------------------------------------------------------------------------------------
	//							RANDOM NEIGHBOR OBTENTION
	// --------------------------------------------------------------------------------------
<<<<<<< HEAD

=======
	/**
		Simple Exchange Neighborhood, returns a random neighboring solution to the one provided.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
>>>>>>> f2050b1f182ece8afbf5e5bdb41d3314679b3b11
	AntiBandwidth::solutionT simpleExchangeR(AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix, std::mt19937& generator);

	/**
		Double Exchange Neighborhood, returns a random neighboring solution to the one provided.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
	AntiBandwidth::solutionT doubleExchangeR(AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix, std::mt19937& generator);

	/**
		Quintuple Exchange Neighborhood, returns a random neighboring solution to the one provided.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
	*/
	AntiBandwidth::solutionT quintupleExchangeR(AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix, std::mt19937& generator);

	/**
<<<<<<< HEAD
		Patch note: This method is not consistent enough to be utilized in experiments.
		Use quintupleExchangeR instead.
=======
		Cyclic Adjacent Swap Neighborhood, returns a random neighboring solution to the one provided.

		@param labeling is the initially provided solution
		@param adjMatrix is an abstraction that represents the undirected graph
>>>>>>> f2050b1f182ece8afbf5e5bdb41d3314679b3b11
	*/
	AntiBandwidth::solutionT cyclicAdjExchangeR(AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix, std::mt19937& generator);

}
