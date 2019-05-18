#pragma once

#include "AntiBandwidth.h"
#include "neighborhood.h"
#include "GraphGenerator.h"

namespace VNS {

	typedef AntiBandwidth::solutionT(*VND)(const AntiBandwidth::solutionT& labeling,
		const std::vector<std::vector<short int> >& adjMatrix);

}