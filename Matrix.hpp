#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <chrono>


/**
 * Class that implements the behaviour of a matrix
 * @param nRows number of rows
 * @param nCols number of columns
 * @param matrix is the 2D vector that holds the matrix values
 */
class Matrix{

private:
    std::vector < std::vector <int> > matrix;
    int nCols;
    int nRows;

public:

    /**
     * Constructor of the class that initialized a 2D vector
     * full of zeros.
     * @param nRows number of rows
     * @param nCols number of columns.
     */
    Matrix(int nRows, int nCols);

    /**
     * Constructor of the class that reads a 2D matrix from a file.
     * @param filePath path of the file were the matrix is stored.
     */
    Matrix(std::string filePath);

    /**
     * Constructor of the class similar to the first one but copying
     * in this case the content of a 2D vector passed as parameter.
     * @param nRows number of rows
     * @param nCols number of columns
     * @param m_    2D vector from where to copy values.
     */
    Matrix(int nRows, int nCols, std::vector< std::vector<int> > m_);

    /**
     * Destructor of the class.
     */
    ~Matrix();

    /**
     * It sets a value in a certain position.
     * @param posX  x-Axis position for inserting the value.
     * @param posY  y-Axis position for inserting the value.
     * @param value to be inserted.
     */
    void set(int posX, int posY, int value);

    /**
     * Similar to set
     * @see set
     */

    void add(int posX, int posY, int value);

    /**
     * It sets or increment a value in a certain position.
     * @param posX  x-Axis position for inserting the value.
     * @param posY  y-Axis position for inserting the value.
     * @param value to be inserted/incremented.
     */

    void append(int posX, int posY, int value);

    /**
     * It gets the value in a certain position.
     * @param posX x-Axis position for inserting the value
     * @param posY y-Axis position for inserting the value
     * @return an int with the value in the [posX,posY] position.
     */
    inline int& get(int posX, int posY){
      return matrix[posX][posY];
    }

    /**
     * It gets the number of columns of the matrix.
     */
    inline int getCols(){
      return nCols;
    }

    /**
     * It gets the number of rows of the matrix.
     */
    inline int getRows(){
      return nRows;
    }

    int get(int posX, int posY) const;
    int getCols() const;
    int getRows() const;

    void file_to_matrix(std::string filePath);

};
