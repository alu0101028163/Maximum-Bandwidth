#include <iostream>
#include "MultiStart.h"

const int REPETITIONS = 100;
int main() {
    std::string filename;
    std::vector<int> auxvec;
    int auxvecOF;

    for ( int i = 1; i <= 3; ++i ) {
        for ( int j = 0; j < REPETITIONS; ++j ) {
               MultiStart::multiStart(i, "/home/basilio/ULL/DAA/PROYECTO FINAL/Git Hub/clion_multistart/bcspwr01.mtx.rnd", REPETITIONS);
                std::cout <<  "\n";
        }
    }
}