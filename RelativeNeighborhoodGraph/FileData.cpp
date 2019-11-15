//
//  FileData.cpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 15/11/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#include "FileData.hpp"

char SEPARATION_CHARACTER = ',';

/*
Constructors & Destructor
*/
FileData::FileData(){
    separationCharacter = SEPARATION_CHARACTER;
    numberOfRows = 0;
    numberOfColumns = 0;
}

FileData::FileData(std::string filename){
    separationCharacter = SEPARATION_CHARACTER;
    std::string line;
    std::ifstream myfile(filename);
    while (std::getline(myfile, line)){
        addRowOfMatrixFromLine(line);
    }
    numberOfRows = (unsigned int) matrixOfString.size();
    numberOfColumns = (unsigned int) matrixOfString[0].size();
    
    setIsColumAClassToZero();
}

FileData::FileData(std::string filenameOfGraph, std::string filenameForIsColumnAClass){
    separationCharacter = SEPARATION_CHARACTER;
    std::string line;
    std::ifstream myfile(filenameOfGraph);
    while (std::getline(myfile, line)){
        addRowOfMatrixFromLine(line);
    }
    numberOfRows = (unsigned int) matrixOfString.size();
    numberOfColumns = (unsigned int) matrixOfString[0].size();
    
    std::ifstream fileTemp(filenameForIsColumnAClass);
    std::getline(fileTemp, line);
    setIsColumAClassWithString(line);
}


/*
Methods
*/

//Public
unsigned int FileData::getNumberOfRows(){
    return numberOfRows;
}

unsigned int FileData::getNumberOfColumns(){
    return numberOfColumns;
}

void FileData::print(){
    printIsColumnAClassAttribute();
    printMatrix();
}

void FileData::printMatrix(){
    
    for (unsigned int row = 0; row < numberOfRows; row ++) {
        for (unsigned int column = 0; column < numberOfColumns-1; column++) {
            std::cout << matrixOfString[row][column] << separationCharacter;
        }
        std::cout << matrixOfString[row][numberOfColumns-1] << std::endl;
    }
    std::cout << std::endl;
}

void FileData::printIsColumnAClassAttribute(){
    for (unsigned int column = 0; column < numberOfColumns-1; column++) {
        std::cout << isColumnAClass[column] << separationCharacter;
    }
    std::cout << isColumnAClass[numberOfColumns-1] << std::endl;
}

//Private
void FileData::addRowOfMatrixFromLine(std::string line){
    std::vector<std::string> lineVector = cutStringOnSeparationCharacter(line);
    matrixOfString.push_back(lineVector);
    numberOfRows++;
}

std::vector<std::string> FileData::cutStringOnSeparationCharacter(std::string stringToCut){
    std::vector<std::string> vectorToReturn;
    vectorToReturn.push_back(getFirstElementOfString(stringToCut));
    while (findNumberOfSeparationCharacter(stringToCut) > 0) {
        stringToCut = cutStringAfterSperationCharacter(stringToCut);
        vectorToReturn.push_back(getFirstElementOfString(stringToCut));
    }
    return vectorToReturn;
}

std::string FileData::cutStringAfterSperationCharacter(std::string stringToCut){
    size_t pos = stringToCut.find(separationCharacter);
    if(pos != std::string::npos){
        stringToCut = stringToCut.substr(pos+1);
    }
    return stringToCut;
}

std::string FileData::getFirstElementOfString(std::string stringToSearch){
    size_t pos = stringToSearch.find(separationCharacter);
    if(pos != std::string::npos){
        return stringToSearch.substr(0,pos);
    }
    else{
        return stringToSearch;
    }
}

unsigned int FileData::findNumberOfSeparationCharacter(std::string stringToSearch){
    return (unsigned int) std::count(stringToSearch.begin(), stringToSearch.end(), separationCharacter);
}

void FileData::setIsColumAClassWithString(std::string line){
    isColumnAClass.push_back(std::stoi(getFirstElementOfString(line)));
    while(findNumberOfSeparationCharacter(line) > 0){
        line = cutStringAfterSperationCharacter(line);
        isColumnAClass.push_back(std::stoi(getFirstElementOfString(line)));
    }
}

void FileData::setIsColumAClassToZero(){
    for(unsigned int column = 0; column < numberOfColumns; column++){
        isColumnAClass.push_back(0);
    }
}
