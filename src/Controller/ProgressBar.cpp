//
//  ProgressBar.cpp
//  RelativeNeighborhoodGraph
//
//  Created by GuillaumeBouchard on 04/12/2019.
//  Copyright © 2019 GuillaumeBouchard. All rights reserved.
//

#include "ProgressBar.hpp"

ProgressBar::ProgressBar(){
    lengthBar = 20;
  
    length = 0;
    cursor = 0;
    
    cursorBar = 0;
    cursorPercent = 0;
}

void ProgressBar::initialize(unsigned int l){
    length = l;
    print();
}

void ProgressBar::update(){
    cursor++;
    if(cursorPercent != setToPercent(cursor)){
        cursorPercent++;
        if (cursorPercent % (100/lengthBar) == 0) {
            cursorBar++;
            threadOutput();
        }
    }
    if (cursor == length) {
        std::cout << std::endl;
        listOfThread.back().detach();
    }
}

void ProgressBar::print(){
    if (listOfThread.size()>1 && listOfThread[listOfThread.size()-2].joinable()) {
        listOfThread[listOfThread.size()-2].join();
    }
    std::cout <<"[";
    for (unsigned int i = 0; i < cursorBar ; i++) {
        std::cout << "=";
    }
    for (unsigned int i = cursorBar; i < lengthBar; i++) {
        std::cout << " ";
    }
    std::cout << "] " << cursorPercent << "%" << std::endl;
    

}

void ProgressBar::threadOutput(){
    std::thread t(&ProgressBar::print, this);
    listOfThread.push_back(std::move(t));
}

unsigned int ProgressBar::setToPercent(unsigned int value){
    return value*100/length;
}
