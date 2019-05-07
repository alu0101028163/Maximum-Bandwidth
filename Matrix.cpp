#include "Matrix.hpp"


Matrix::Matrix(std::string filePath):
  nRows(0),
  nCols(0)
  {
  file_to_matrix(filePath);
  }

Matrix::Matrix(int nRows, int nCols):
  nRows(nRows),
  nCols(nCols)
  {
    for (int i = 0; i < nRows; i++){
      matrix.push_back(std::vector<int>(nCols));
    }
  }

Matrix::Matrix(int nRows, int nCols, std::vector< std::vector<int> > m_):
  nRows(nRows),
  nCols(nCols),
  matrix(m_)
  {
  }

Matrix::~Matrix(){}


void Matrix::file_to_matrix(std::string filePath){

  std::ifstream infile(filePath);

  infile >> nCols >> nRows;
  assert(nCols == nRows);

  int temp;
  for(int i = 0; i < nRows; i++){
    matrix.push_back(std::vector<int>());
    for (int j = 0; j < nCols; j++){
      infile >> temp;
      matrix[i].push_back(temp);
    }
  }

  infile.close();
}



void Matrix::set(int posX, int posY, int value){

  matrix[posX][posY] = value;

}


void Matrix::add(int posX, int posY, int value){

  matrix[posX][posY] = value;

}

int Matrix::get(int posX, int posY) const{
  return matrix[posX][posY];
}


int Matrix::getCols() const{
  return nCols;
}

int Matrix::getRows() const{
  return nRows;
}
