// GraphGenerator.h: include std files / project specific files.
#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Graph.h"

namespace ABM {
	/**
	 Generates a mildly controlled non-weighed, non-directed graph of a specified size (number of vertices).
	 Generated graph will be in specified path SYNCHRONOUSLY. It is not advised to make asynchronous calls to this
	 method if pathFile is to be open concurrently

	 @param n vertices
	 @param factor conditions the probability with which a link between two nodes is randomly generated.
			This allows us to generate more or less heavily linked graphs
	 @param filePath where generated graph is stored
	*/
	void graphGenerator(int n, int factor, const std::string& filePath);

	/**
	 Generates a graph instace in the form of an adjacency matrix with (size) vertices
	 Said graph is non-directed and non-weighed

	 @param n nodes.
	 @return the 2D vector of integers.
	 */
	std::vector< std::vector<short int> > generateGraphInstance(int n, int factor);

	/**
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

}