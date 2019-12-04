//
//  Exception.hpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 04/12/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include <iostream>
#include <stdio.h>
#include <string>

class Exception{
private:
    int errorCode;
    std::string comment;
    
public:
    Exception(int code);
    Exception(std::string com);
    Exception(int code, std::string com);
    
    void print();
};

#endif /* Exception_hpp */
