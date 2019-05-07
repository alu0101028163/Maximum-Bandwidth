#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


/**
 * Generates a random number.
 * @return the random integer.
 */
int random_number(){
  int rNumber = (rand() % 2) + 1;
  if(rNumber == 2)
     return 0;
  else return 1;
}

/**
 * Generates a random 2D vector of ints that represent the content
 * of the matrix.
 * @param nRows number of rows
 * @param nCols number of columns.
 * @return the 2D vector of integers.
 */
std::vector< std::vector<int> > generate_random_matrix(int nRows, int nCols){
  srand((int)time(0));
  std::vector< std::vector<int> > matrix;
  for (int i = 0; i < nRows; i++){
    matrix.push_back(std::vector<int>());
    for (int j = 0; j < nCols; j++){
      matrix[i].push_back(random_number());
    }
  }
  return matrix;
}

/**
 * Prints the content of a 2D vector of integers.
 * @param nRows number of rows
 * @param nCols number of columns.
 * @param matrix 2D vector of integers.
 */
void print_matrix(std::vector< std::vector<int> > matrix, int nRows, int nCols){
  for (int i = 0; i < matrix.size(); i++){
    std::cout << "( ";
    for (int j = 0; j < matrix[i].size() ; j++){
      std::cout << matrix[i][j] << " ";
    }
    std::cout << ")\n";
  }
}


/**
 * Stores the content of a 2D vector of integers inside a file.
 * @param matrix    2D vector of integers.
 * @param filePath  is that path of the file where the data will be stored.
 */
void matrix_to_file(std::vector< std::vector<int> > matrix, std::string filePath){

     std::ofstream file;
     file.open(filePath);

     if (matrix.size() < 0){
         throw std::length_error("Matrix's number of columns must be at least 1");
     }

     if (matrix[0].size() < 0){
         throw std::length_error("Matrix's number of rows must be at least 1");
     }

     file << matrix.size() << "\n";     // Introduce number of rows
     file << matrix[0].size() << "\n";  // Introduce number of cols

     for (int i = 0; i < matrix.size(); i++){
       for (int j = 0; j < matrix[i].size(); j++){
            file << matrix[i][j] << " ";
       }
            file << "\n";
     }

     file.close();

}



/**
 * Retrieves the data of a matrix from a file and stores it in a
 * 2D vector of integers that will be returned.
 * @param filePath    path of the file where the matrix data is allocated.
 * @return            a 2D vector of integers with the data of the matrix.
 */
std::vector< std::vector<int> > file_to_matrix(std::string filePath){
  std::vector< std::vector<int> > matrix;
  std::ifstream infile(filePath);

  int nCols, nRows, temp;
  infile >> nCols >> nRows;

  int value;
  for(int i = 0; i < nRows; i++){
    matrix.push_back(std::vector<int>());
    for (int j = 0; j < nCols; j++){
      infile >> temp;
      matrix[i].push_back(temp);
    }
  }

  infile.close();
  return matrix;
}
