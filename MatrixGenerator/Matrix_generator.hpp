#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


namespace MatrixGenerator{

  /**
   * Generates a random number.
   * @return the random integer.
   */
  int random_number();

  /**
   * Generates a random 2D vector of ints that represent the content
   * of the matrix.
   * @param nRows number of rows
   * @param nCols number of columns.
   * @return the 2D vector of integers.
   */
  std::vector< std::vector<int> > generate_random_matrix(int nRows, int nCols);

  /**
   * Prints the content of a 2D vector of integers.
   * @param nRows number of rows
   * @param nCols number of columns.
   * @param matrix 2D vector of integers.
   */
  void print_matrix(std::vector< std::vector<int> > matrix, int nRows, int nCols);


  /**
   * Stores the content of a 2D vector of integers inside a file.
   * @param matrix    2D vector of integers.
   * @param filePath  is that path of the file where the data will be stored.
   */
  void matrix_to_file(std::vector< std::vector<int> > matrix, std::string filePath);



  /**
   * Retrieves the data of a matrix from a file and stores it in a
   * 2D vector of integers that will be returned.
   * @param filePath    path of the file where the matrix data is allocated.
   * @return            a 2D vector of integers with the data of the matrix.
   */
  std::vector< std::vector<int> > file_to_matrix(std::string filePath);

}
