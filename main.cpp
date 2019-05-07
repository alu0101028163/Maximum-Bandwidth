#include <iostream>
#include "Matrix_generator.hpp"

int main(){
  std::cout << "Hello Maximum Bandwidth.\n";
  std::vector< std::vector<int> > m = generate_random_matrix(50,50);
  print_matrix(m, 50,50);
  matrix_to_file(m, "matriz1.txt");
}
