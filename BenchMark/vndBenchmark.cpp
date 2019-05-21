#include "vns.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(int argc, char *argv[]) {

	if (argc != 4) {
		std::cout << "Wrong use: \nFirst argument is the path of the instance you want to test."
			<< "\nSecond argument is the name of the instance you want to test"
			<< "\nThird argument is the best value for that instance.\n";
		exit(1);
	}

	const int N_REPS = 100;
	const int MAX_ITS_LIMIT = 50;

	std::string instancePath = std::string(argv[1]);
	std::string instanceName = std::string(argv[2]);
	std::string graspLabel = std::string(argv[3]);

	std::vector<int> labeling = GraphGen::readLabel(graspLabel);

	std::ofstream vndCalculations;
	std::string fichName = std::string("VndCalculations_" + instanceName + ".csv");
	vndCalculations.open(fichName);
	vndCalculations << "max_its_wo_improv,labeling,value\n";

	int max_its = 10;
	std::vector<std::vector<short int > > graph = GraphGen::disperseFileToGraph("../" + instancePath);
	std::vector<int> solutionElements;

	GraphGen::traceGeneratedMatrix(graph);

	for (int i = 1; i <= graph.size(); i++) {
		solutionElements.push_back(i);
	}

	while (max_its < MAX_ITS_LIMIT) {
		VNS::setMaxNIIterations(max_its);
		for (int i = 0; i < N_REPS; i++) {
			// std::vector<int> labeling = VNS::VND(graph);
			vndCalculations << max_its << ",";
			vndCalculations << "[ ";

			for (int j = 0; j < labeling.size(); j++) {
				vndCalculations << labeling[j] << " ";
			}
			vndCalculations << "],";
			vndCalculations << AntiBandwidth::objectiveFunction(graph, labeling) << "\n";
		}
		max_its += 5;
	}

	vndCalculations.close();

}
