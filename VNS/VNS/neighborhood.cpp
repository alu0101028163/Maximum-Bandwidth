#include "neighborhood.h"

// ---------------------------------------------------------------------------------------
//					    CANDIDATE LIST NEIGHBORHOOD EXPLORATION
// ---------------------------------------------------------------------------------------

std::vector<int> NeighborStructs::GLCandidateList(
	const AntiBandwidth::solutionT & labeling,
	const std::vector<std::vector<short int>>& adjMatrix) {

	// TODO:

	return std::vector<int>();
}

AntiBandwidth::solutionT NeighborStructs::simpleExchangeGL(
	const AntiBandwidth::solutionT& labeling,
	const std::vector<std::vector<short int> >& adjMatrix) {

	return AntiBandwidth::solutionT();
}

AntiBandwidth::solutionT NeighborStructs::doubleExchangeGL(
	const AntiBandwidth::solutionT& labeling, 
	const std::vector<std::vector<short int> >& adjMatrix) {

	return AntiBandwidth::solutionT();
}

AntiBandwidth::solutionT NeighborStructs::cyclicAdjExchangeGL(
	const AntiBandwidth::solutionT& labeling,
	const std::vector<std::vector<short int> >& adjMatrix) {

	return AntiBandwidth::solutionT();
}

// --------------------------------------------------------------------------------------
//							NAIVE NEIGHBORHOOD EXPLORATION
// --------------------------------------------------------------------------------------

AntiBandwidth::solutionT NeighborStructs::simpleExchange(
	const AntiBandwidth::solutionT& labeling, 
	const std::vector<std::vector<short int>>& adjMatrix) {

	AntiBandwidth::solutionT nextLabels = labeling;
	int nextObjFunction;
	int oldObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, labeling);

	for (int i = 0; i < labeling.size() - 1; i++) {
		for (int j = i + 1; j < labeling.size(); j++) {
			// swap labels
			std::swap(nextLabels[i], nextLabels[j]);

			nextObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, nextLabels);
			if (nextObjFunction > oldObjFunction)
				return nextLabels;

			// revert swap
			std::swap(nextLabels[i], nextLabels[j]);
		}
	}

	return labeling;	// if it gets here, there have been no improvements whatsoever
}

AntiBandwidth::solutionT NeighborStructs::doubleExchange(
	const AntiBandwidth::solutionT&  labeling, 
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	AntiBandwidth::solutionT nextLabels = labeling;
	int nextObjFunction;
	int oldObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, labeling);

	for (int i = 0; i < labeling.size() - 1; i++) {
		for (int j = i + 1; j < labeling.size(); j++) {
			std::swap(nextLabels[i], nextLabels[j]);

			for (int k = 0; k < labeling.size() - 1; k++) {
				for (int z = k + 1; z < labeling.size(); z++) {
					// Only perform second swap if indexes are different 2 on 2
					if ((k != i || z != j) || (k != j || z != i)) {
						std::swap(nextLabels[k], nextLabels[z]);

						nextObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, nextLabels);
						if (nextObjFunction > oldObjFunction)
							return nextLabels;
						// reverse second swap
						std::swap(nextLabels[k], nextLabels[z]);
					}
				}
			}

			// reverse first swap
			std::swap(nextLabels[i], nextLabels[j]);
		}
	}

	return labeling;
}

AntiBandwidth::solutionT NeighborStructs::cyclicAdjExchange(
	const AntiBandwidth::solutionT& labeling, 
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	AntiBandwidth::solutionT nextLabels;
	int nextObjFunction;
	int oldObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, labeling);

	for (int i = 0; i < labeling.size(); i++) {
		nextLabels = labeling;

		for (int j = i - 1; j > 0; j--) {
			std::swap(nextLabels[j], nextLabels[j + 1]);

			nextObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, nextLabels);
			if (nextObjFunction > oldObjFunction)
				return nextLabels;
		}
	
		nextLabels = labeling;		// Resets are performed in-between consecutive swaps procedures

		for (int j = i + 1; j < labeling.size(); j++) {
			std::swap(nextLabels[j], nextLabels[j - 1]);

			nextObjFunction = AntiBandwidth::objectiveFunction(adjMatrix, nextLabels);
			if (nextObjFunction > oldObjFunction)
				return nextLabels;
		}
	}


	return labeling;
}

// --------------------------------------------------------------------------------------
//							RANDOM NEIGHBORHOOD EXPLORATION
// --------------------------------------------------------------------------------------

AntiBandwidth::solutionT NeighborStructs::simpleExchangeR(
	const AntiBandwidth::solutionT & labeling,
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	// TODO: 
	return AntiBandwidth::solutionT();
}

AntiBandwidth::solutionT NeighborStructs::doubleExchangeR(
	const AntiBandwidth::solutionT & labeling, 
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	//TODO: 
	return AntiBandwidth::solutionT();
}

AntiBandwidth::solutionT NeighborStructs::cyclicAdjExchangeR(
	const AntiBandwidth::solutionT & labeling, 
	const std::vector<std::vector<short int>>& adjMatrix) {
	
	//TODO:
	return AntiBandwidth::solutionT();
}
