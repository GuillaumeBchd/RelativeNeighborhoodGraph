//
//  GraphData.cpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 22/11/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#include "GraphData.hpp"

/*
Constructors & Destructor
*/
GraphData::GraphData(FileData & fileData):MatrixOfFloat(fileData.getNumberOfRows(),fileData.getNumberOfColumnsNonClass()){
    //We have a matrix of the correct size, we just need to get the data and normalize them

    //We start by copying the correct columns from fileData
    copyDataFromFileData(fileData);
    
    //Then we normalize them
    for(unsigned int column = 0; column < getNumberOfColumns(); column++){
        normalizeColumn(column);
    }
    
}




/*
Public methods
*/

/*
Private methods
*/

void GraphData::copyDataFromFileData(FileData &fileData){
    unsigned int columnGraphData = 0;
    unsigned int columnFileData = 0;
    for (columnGraphData; columnGraphData < getNumberOfColumns(); columnGraphData++) {
        if(!fileData.isColumnUsedToGenerateTheGraph(columnFileData)){columnFileData++;} //We copy only the column used to create the graph
        for (unsigned int row = 0; row < getNumberOfRows(); row++) {
            setElement(row, columnGraphData, std::stof(fileData.getString(row, columnFileData)));
        }
        columnFileData++;
    }
}

float GraphData::getMaxOfColumn(unsigned int column){
    float maxOfColumn = getElement(0, column);
    for(unsigned int row = 1; row < getNumberOfRows(); row++){
        if(maxOfColumn<getElement(row, column)){
            maxOfColumn = getElement(row, column);
        }
    }
    return maxOfColumn;
}

float GraphData::getMinOfColumn(unsigned int column){
    float minOfColumn = getElement(0, column);
    for(unsigned int row = 1; row < getNumberOfRows(); row++){
        if(minOfColumn>getElement(row, column)){
            minOfColumn = getElement(row, column);
        }
    }
    return minOfColumn;
}

float GraphData::getNormalizedValueOfX(float x, float xmax, float xmin){
    return (x-xmin)/(xmax-xmin);
}

void GraphData::normalizeColumn(unsigned int column){
    float maxOfColumn = getMaxOfColumn(column);
    float minOfColumn = getMinOfColumn(column);
    for(unsigned int row = 0; row < getNumberOfRows(); row++){
        float x = getElement(row, column);
        setElement(row, column, getNormalizedValueOfX(x, maxOfColumn, minOfColumn));
    }
    
}
