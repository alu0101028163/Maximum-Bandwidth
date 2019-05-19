#pragma once

#include "AntiBandwidth.h"
#include "neighborhood.h"
#include "GraphGenerator.h"

namespace VNS {

	typedef AntiBandwidth::solutionT(*VNS)(AntiBandwidth::solutionT labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//												VND
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT VND(AntiBandwidth::solutionT init_solution,
		const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//											   BVNS
	// -------------------------------------------------------------------------------------------------

	AntiBandwidth::solutionT BVNS(AntiBandwidth::solutionT init_solution,
		const std::vector<std::vector<short int> >& adjMatrix);

	// -------------------------------------------------------------------------------------------------
	//										   AUX METHODS
	// -------------------------------------------------------------------------------------------------

	void traceSolution(const AntiBandwidth::solutionT& sol, const std::vector<std::vector<short int> >&);
}