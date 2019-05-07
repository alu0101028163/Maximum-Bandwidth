

Antibandwidth: main.o matrix.o
	g++ -std=c++11 -O3 -o antibandwidth main.o Matrix.o

main.o: main.cpp
	g++ -std=c++11 -O3 -c main.cpp Matrix_generator.hpp

matrix.o: Matrix.hpp Matrix.cpp
	g++ -std=c++11 -O3 -c Matrix.cpp

generator:
		g++ -std=c++11 -O3 -o generator Matrix_generator.hpp Matrix_generator.cpp


clean:
	rm -f *.o *.gch a.out
