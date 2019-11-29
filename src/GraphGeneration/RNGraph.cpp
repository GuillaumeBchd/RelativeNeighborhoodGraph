//
//  RNGraph.cpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 22/11/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#include "RNGraph.hpp"

/*
Constructors & Destructor
*/
RNGraph::RNGraph(DistancesBetweenNodes & distancesBetweenNodes):MatrixOfBoolean(distancesBetweenNodes.getNumberOfRows(), distancesBetweenNodes.getNumberOfRows()){
    
    
    #pragma omp parallel for
    for (unsigned int row = 0; row < getNumberOfRows(); row++) {
        for (unsigned int column = 0; column < getNumberOfColumns(); column++) {
            setElement(row, column, false);
            if (row < column && isThereAnEdgeBetweenTwoNodes(distancesBetweenNodes, row, column)) {
                setElement(row, column, true);
            }
        }
    }
    
    
}

/*
Public methods
*/

/*
Private methods
*/

bool RNGraph::isThereAnEdgeBetweenTwoNodes(DistancesBetweenNodes & distancesBetweenNodes, unsigned int node_A, unsigned int node_B){
    float distanceBetweenAandB = distancesBetweenNodes.getDistance(node_A, node_B);
    //true si aucune dist(nodeA nodeX) < dist nodeA nodeB AND dist(nodeB nodeX) < dist nodeA nodeB
    for (unsigned int node = 0; node < getNumberOfRows(); node++) {
        if(distancesBetweenNodes.getDistance(node, node_A) < distanceBetweenAandB && distancesBetweenNodes.getDistance(node, node_B) < distanceBetweenAandB){
            return false;
        }
        
    }
    return true;
    
}

