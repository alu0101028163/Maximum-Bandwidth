#pragma once

#include "GraphGenerator.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

// TODOCLASS: Header to be completed in later versions
class Graph {
private:
	std::vector<std::vector<short int> > adjacencyMatrix_;

	//TODO: Caracterization of labelling as:
	//	1. vector<int>
	//  2. set<int>
	//		** waiting for review

public:

	/// <summary>
	///		Build graph from an instance in a file
	/// </summary>
	/// <param name ="instance"> File path to be read from </param>
	Graph(const std::string& instance);

	/// <summary>
	///		Default destructor
	/// </summary>
	~Graph();


	void printGraph();
};
