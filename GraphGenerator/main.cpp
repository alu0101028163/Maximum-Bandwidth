#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "GraphGenerator.h"

using namespace GraphGen;
using namespace std;

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
