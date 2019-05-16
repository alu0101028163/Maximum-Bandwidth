#pragma once

#include "../../GraphGenerator/GraphGenerator.h"
#include "../../AntiBandwidth/AntiBandwidth.h"			// objectiveFunction and 

// Unify ABM and AntiBandwidth namespaces. Serving the same purpose
namespace ABM {

	//TODO: It would be amazing if this functions could be turned to functors, for once

	/**
	*	TODO: Decide wether to pass a struct with solutionT and assoc value or 
	*		  to evaluate labeling value inside method
	*
	*/


	/**
		This method implements the first neighborhood model with a greedy approach:
			Simple exchange is conformed by the "swap two labels" formula and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.
	*/
	AntiBandwidth::solutionT simpleExchange(const AntiBandwidth::solutionT&);
	
	/**
		This method implements the second neighborhood model with a greedy approach:
			Double exchange applies simple exchange, but twice in a row and is implemented
			following the Glover and Laguna technique (1997) with candidate lists.
	*/
	AntiBandwidth::solutionT doubleExchange(const AntiBandwidth::solutionT&);

	/**
		This method implements the third neighborhood model with a greedy approach:
			Cyclic Adjacent Exchange performs a series of consecutive swaps of adjacent labels and is
			implemented following the Glover and Laguna technique (1997) with candidate lists
	*/
	AntiBandwidth::solutionT cyclicAdjExchange(const AntiBandwidth::solutionT&);

	//----------------------------------------------------------------------------------
}

