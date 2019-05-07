#include "Matrix_generator.hpp"
#include <cstdlib>
#include <cassert>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>



int power_of_two(int index){
    return pow(2,index);
}

bool is_pow_of_two(int number){

  int dividend = number;
  int divisor = dividend;
  int numberDivisions = 0;

  while(divisor >= 2){
    divisor = dividend / 2;
    dividend = divisor;
    numberDivisions++;
  }

  if(pow(2,numberDivisions) == number){
    return true;
  }else return false;


}

/* First argument is the size of the matrix
*  second argument is the name of the file where you want to store the matrix*/
int main(int argc, char *argv[]){

    if (argc != 3){
      std::cout << "Wrong use: \nFirst argument is the size of the matrix you want to create."
                << "\nSecond argument is the name of the file where you want to store the matrix.\n";
      exit(1);
    }


    std::stringstream convert(argv[1]);
    int matrixSize;
    convert >> matrixSize;
    matrixSize = power_of_two(matrixSize);


    std::vector< std::vector<int> > m_ = generate_random_matrix(matrixSize, matrixSize);
    std::string path = "/home/hyydra/Documents/UNIVERSITY/DYADA/ull-esit-inf-daa-1819-pract2-alu0101028163/src/" + std::string(argv[2]);

    try{
    matrix_to_file(m_, path);
    }catch(const std::length_error& e){
      throw;
    }catch(const std::ofstream::failure& e){
      throw;
    }

    std::cout << "Matrix of: ( " << matrixSize << " x " << matrixSize << " ) successfully done.\n";


}
