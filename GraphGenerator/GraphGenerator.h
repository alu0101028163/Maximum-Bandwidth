// GraphGenerator.h: include std files / project specific files.
#pragma once
#include <random>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

// Not using currently.
// #include "Graph.h"

namespace ABM {
	/**
	 Generates a mildly controlled non-weigthed, non-directed graph of a specified size (number of vertices).
	 Generated graph will be in specified path SYNCHRONOUSLY. It is not advised to make asynchronous calls to this
	 method if pathFile is to be open concurrently. The method stores an adjacency matrix created using the
	 generateGraphInstance method in a text file.

	 @param n vertices
	 @param factor conditions the probability with which a link between two nodes is randomly generated.
			This allows us to generate more or less heavily linked graphs
	 @param filePath where generated graph is stored
	*/
	void graphGenerator(int n, int factor, const std::string& filePath);

	/**
	 Generates a graph instance in the form of an adjacency matrix with (size) vertices
	 Said graph is non-directed and non-weighted

	 @param n nodes.
	 @return the 2D vector of integers.
	 */
	std::vector< std::vector<short int> > generateGraphInstance(int n, int factor);

	/**
	//TODO : Why not simply call it "printGeneratedMatrix"?
	 Debug purposes. Meant to print a given adjacency matrix
	 @param matrix to be sent by cout
	*/
	void traceGeneratedMatrix(const std::vector<std::vector<short int> >&) noexcept;

	/**
	 Place a previously generated adjacency matrix in a file with a fixed syntax

	 @param matrix adjacency matrix stored in a vector
	 @param string containing the name of the file to generate
	*/
	void generateGraphFile(const std::vector<std::vector<short int> >&, const std::string&);


	/**
	 * Creates a Graph instance from an input file.
	 * @param fileName
	 */
	std::vector<std::vector<short int> > denseFileToGraph(std::string fileName);
	std::vector<std::vector<short int> > disperseFileToGraph(std::string fileName);
}
