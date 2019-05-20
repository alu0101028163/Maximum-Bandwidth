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
	AntiBandwidth::solutionT labeling,
	const std::vector<std::vector<short int>>& adjMatrix,
	std::mt19937& generator) {
	
	int i, j;						
	bool distinct = false;															// ensure different indexes are chosen
	std::uniform_int_distribution<> integerDistribution(0, labeling.size() - 1);	// generate two indexes at random

	i = integerDistribution(generator);
	while (!distinct) {
		
		j = integerDistribution(generator);
		if (i != j) distinct = true;
	}

	std::swap(labeling[i], labeling[j]);

	return labeling;
}

AntiBandwidth::solutionT NeighborStructs::doubleExchangeR(
	AntiBandwidth::solutionT labeling, 
	const std::vector<std::vector<short int>>& adjMatrix,
	std::mt19937& generator) {
	
	int i1, j1, i2, j2;
	bool distinct = false;															// ensure different indexes are chosen
	std::uniform_int_distribution<> integerDistribution(0, labeling.size() - 1);	// generate two indexes at random

	i1 = integerDistribution(generator);
	while (!distinct) {

		j1 = integerDistribution(generator);
		if (i1 != j1) {
			i2 = integerDistribution(generator);
			while (!distinct) {
				j2 = integerDistribution(generator);

				if (j2 != i1 && j2 != j1) distinct = true;
			}
		}
	}

	std::swap(labeling[i1], labeling[j1]);
	std::swap(labeling[i2], labeling[j2]);

	return labeling;
}

AntiBandwidth::solutionT NeighborStructs::quintupleExchangeR(AntiBandwidth::solutionT labeling, 
	const std::vector<std::vector<short int>>& adjMatrix,
	std::mt19937 & generator) {
	
	int i = 0;
	while (i < 5) {
		// Structural quality almost ensured by random factor
		labeling = NeighborStructs::simpleExchangeR(labeling, adjMatrix, generator);
		i++;
	}
	
	return labeling;
}

AntiBandwidth::solutionT NeighborStructs::cyclicAdjExchangeR(
	AntiBandwidth::solutionT labeling, 
	const std::vector<std::vector<short int>>& adjMatrix,
	std::mt19937& generator) {
	
	std::uniform_int_distribution<> integerDistribution(0, labeling.size() - 1);
	// in this case, generate a starting index, a movement direction and a number of swaps to movement side
	bool dir = (integerDistribution(generator) > labeling.size() / 2) + 1;		// false-> right, true -> left
	int index = integerDistribution(generator) + 1;
	int n_swaps = (dir) ? 
		((integerDistribution(generator)) % (index)) :
		((integerDistribution(generator)) % (labeling.size() - index));

	for (int i = 1; i < n_swaps; i++) {
		if (dir) {	// left
			std::swap(labeling[index], labeling[index - 1]);
			index--;
		}
		else {		// right
			std::swap(labeling[index], labeling[index + 1]);
			index++;
		}
	}

	return labeling;
}
