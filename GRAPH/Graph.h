#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

// TODOCLASS: Header to be completed in later versions
class Graph {
private:
	std::vector<std::vector<short int> > adjacencyMatrix_;

public:

	Graph(const std::string& instance);
	~Graph();
	int getSize();
	std::vector<short int>& operator[] (int x);
	void printGraph();
};
