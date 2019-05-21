#include "GraphGenerator.h"

using namespace std;
using namespace GraphGen;

void GraphGen::graphGenerator(int n, int factor, const std::string & filePath) {

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

std::vector<std::vector<short int>> GraphGen::generateGraphInstance(int n, int factor) {

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

void GraphGen::traceGeneratedMatrix(const std::vector<std::vector<short int>>& matrix) noexcept {

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void GraphGen::generateGraphFile(const std::vector<std::vector<short int> >& matrix, const std::string& filePath) {

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

std::vector<std::vector<short int> > GraphGen::denseFileToGraph(std::string fileName){
	std::vector < std::vector <short int > > adjacencyMatrix_;
	std::ifstream infile(fileName);

	int nVertexs;
	infile >> nVertexs;

	int value;
	short int temp;

	for(int i = 0; i < nVertexs; i++){
		adjacencyMatrix_.push_back(std::vector<short int>());
		for (int j = 0; j < nVertexs; j++){
			infile >> temp;
			adjacencyMatrix_[i].push_back(temp);
		}
	}

	infile.close();
	return adjacencyMatrix_;
}

std::vector<std::vector<short int> > GraphGen::disperseFileToGraph(bool ignorefirst, const std::string& fileName){

	std::vector < std::vector <short int > > adjacencyMatrix_;
	std::ifstream infile;
	infile.exceptions(std::ifstream::badbit);
	infile.open(fileName);

	if (!infile.good())
		throw std::ifstream::failure("Error trying to read graph file!");

	// Ignore first line when specified (for files with results)
	if (ignorefirst)
		infile.ignore(std::numeric_limits<int>::max(), infile.widen('\n'));

	int nCols, nRows, nArcs;
	infile >> nCols >> nRows >> nArcs;

	if (nCols != nRows)
		throw std::logic_error("Graph must be represented as a squared matrix");

	// Matrix initialization:
	for (int i = 0; i < nRows; i++) {
		adjacencyMatrix_.push_back(std::vector<short int>(nCols));
	}

	// While end of file is not reached fill matrix with
	// connections between adjacent vertices.
	while(!infile.eof()){
			int node, neighbour;
			infile >> node >> neighbour;
			adjacencyMatrix_[node - 1][neighbour - 1] = 1;
			adjacencyMatrix_[neighbour - 1][node - 1] = 1;
	}

	infile.close();

	return adjacencyMatrix_;
}

/*Duplicate for version compatibility*/
std::vector<std::vector<short int> > GraphGen::disperseFileToGraph(const std::string& fileName) {

	std::vector < std::vector <short int > > adjacencyMatrix_;
	std::ifstream infile;
	infile.exceptions(std::ifstream::badbit);
	infile.open(fileName);

	if (!infile.good())
		throw std::ifstream::failure("Error trying to read graph file!");

	int nCols, nRows, nArcs;
	infile >> nCols >> nRows >> nArcs;

	if (nCols != nRows)
		throw std::logic_error("Graph must be represented as a squared matrix");

	// Matrix initialization:
	for (int i = 0; i < nRows; i++) {
		adjacencyMatrix_.push_back(std::vector<short int>(nCols));
	}

	// While end of file is not reached fill matrix with
	// connections between adjacent vertices.
	while (!infile.eof()) {
		int node, neighbour;
		infile >> node >> neighbour;
		adjacencyMatrix_[node - 1][neighbour - 1] = 1;
		adjacencyMatrix_[neighbour - 1][node - 1] = 1;
	}

	infile.close();

	return adjacencyMatrix_;
}

std::vector<int> GraphGen::readLabel(const std::string& fileName){


	std::vector <int> label;
	std::ifstream infile(fileName);


	int element;
	while (infile >> element) {
		label.push_back(element);
	}

	infile.close();

	return label;

}
