// GraphGenerator.cpp: define el punto de entrada de la aplicación.
//

#include "GraphGenerator.h"

using namespace std;
using namespace ABM;

int main(int argc, char* argv[]) {
	int n;
	int factor;
	
	// PARAM INPUT
	std::cout << "Number of vertices (n): ";
	while (!(std::cin >> n)) {
		std::cout << "Incorrect value, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}; 
	getchar();
	
	std::cout << "Vecinity factor (%): ";
	while (!(std::cin >> factor)) {
		std::cout << "Incorrect value, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	};

	graphGenerator(n, factor, "inst1.txt");

	system("PAUSE");
	return 0;
}

void ABM::graphGenerator(int n, int factor, const std::string & filePath) {

	try {
		std::cout << "Generating graph Instance . . ." << std::endl;
		std::vector<std::vector<short int>> matrix = generateGraphInstance(n, factor);
		//traceGeneratedMatrix(matrix);
		std::cout << "Writing graph at path: " + filePath + ". . ." << std::endl;
		generateGraphFile(matrix, filePath);

		// File is now ready!
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

std::vector<std::vector<short int>> ABM::generateGraphInstance(int n, int factor) {

	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> intDistribution(0, 100);

	// matrix init
	std::vector< std::vector<short int> > instance;
	for (int i = 0; i < n; i++) {
		instance.push_back(std::vector<short int>(n));
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			short int connection = (intDistribution(generator) >= factor);
			instance[i][j] = connection;		// simmetrical
			instance[j][i] = connection;
		}
	}
	return instance;
}

void ABM::traceGeneratedMatrix(const std::vector<std::vector<short int>>& matrix) noexcept {

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void ABM::generateGraphFile(const std::vector<std::vector<short int> >& matrix, const std::string& filePath) {
	
	if (matrix.size() < 1 || matrix[0].size() < 1) {
		throw std::length_error("Generated instance must have at least 1 vertex");
	}

	std::fstream file;
	file.exceptions(std::fstream::badbit);
	file.open(filePath, std::fstream::out | std::fstream::trunc);

	if (!file.good()) {
		std::string strErr = "An error occurred when trying to open file: " + filePath + ".";
		throw std::fstream::failure(strErr.c_str());
	}

	file << matrix.size() << "\n";     // Introduce number of vertices

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			file << matrix[i][j] << " ";
		}
		file << "\n";
	}

	file.close();
}
