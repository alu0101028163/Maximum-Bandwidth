#include <iostream>
#include "Matrix_generator.hpp"
#include "Matrix.hpp"

int main(){
  /* Random binary generation */
  std::cout << "Hello Maximum Bandwidth.\n";
  std::vector< std::vector<int> > m = generate_random_matrix(50,50);
  // print_matrix(m, 50,50);
  matrix_to_file(m, "matrix1.txt");

  /* Creation of a matrix object */
  Matrix m1("matrix1.txt");
  m1.print();

}
