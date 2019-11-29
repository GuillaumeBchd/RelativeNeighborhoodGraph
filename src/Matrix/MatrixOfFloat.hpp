//
//  MatrixOfFloat.hpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 15/11/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#ifndef MatrixOfFloat_hpp
#define MatrixOfFloat_hpp

#include <stdio.h>
#include <vector>
#include "MatrixOfBoolean.hpp"

class MatrixOfFloat {
    //Atributes
private:
    unsigned int numberOfRows;
    unsigned int numberOfColumns;
    
    float** matrixArray;
    
    //Constructors & Destructor
public:
    MatrixOfFloat();
    MatrixOfFloat(MatrixOfFloat & matrix);
    MatrixOfFloat(unsigned int rows, unsigned int columns);
    ~MatrixOfFloat();
    
    //Methods
public:
    MatrixOfFloat operator=(MatrixOfFloat & matrix);
    
    unsigned int getNumberOfRows();
    unsigned int getNumberOfColumns();
    bool isSquare();
    bool isEmpty();
    float getElement(unsigned int row, unsigned int column);
    void setElement(unsigned int row, unsigned int column, float elem);
    void print();
    void printDimension();
    
    std::vector<float> getRow(unsigned int row);
    std::vector<float> getRowAfterLimit(unsigned int row, unsigned int limit);
    std::vector<float> getColumn(unsigned int column);
    std::vector<float> getColumnBeforeLimit(unsigned int column, unsigned int limit);
    
    void resizeMatrix(unsigned int row, unsigned int column);
    
private:
    void allocateMatrixArray();
    void desallocateMatrixArray();
    void copyArrayToMatrixArray(float** array);
    void setMatrixArrayToZero();
};

 


#endif /* MatrixOfFloat_hpp */
