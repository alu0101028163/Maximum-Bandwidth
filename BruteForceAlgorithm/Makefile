

Antibandwidth: main.o AntiBandwidth.o DeterministAlgorithm.o Graph.o
	g++ -std=c++11 -O3 -o antibandwidth main.o AntiBandwidth.o DeterministAlgorithm.o Graph.o

main.o: main.cpp
	g++ -std=c++11 -O3 -c main.cpp AntiBandwidth.h DeterministAlgorithm.h ../GRAPH/GraphGenerator/Graph.h

Graph.o : ../GRAPH/GraphGenerator/Graph.h ../GRAPH/GraphGenerator/Graph.cpp
	g++ -std=c++11 -O3 -c ../GRAPH/GraphGenerator/Graph.h ../GRAPH/GraphGenerator/Graph.cpp

AntiBandwith.o: AntiBandwidth.h AntiBandwidth.cpp
	g++ -std=c++11 -O3 -c AntiBandwidth.cpp

DeterministAlgorithm.o: DeterministAlgorithm.h DeterministAlgorithm.cpp
	g++ -std=c++11 -O3 -c DeterministAlgorithm.cpp


clean:
	rm -f *.o *.gch a.out
