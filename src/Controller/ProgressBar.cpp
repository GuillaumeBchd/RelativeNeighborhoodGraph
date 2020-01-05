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
    print(0);
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
        if (listOfThread.back().joinable()) {
            listOfThread.back().join();
        }
        std::cout << std::endl;
    }
}

void ProgressBar::print(int i){
    if (listOfThread.size()>1 && listOfThread[i-1].joinable()) {
        listOfThread[i-1].join();
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
    std::thread t(&ProgressBar::print, this, listOfThread.size());
    listOfThread.push_back(std::move(t));
}

unsigned int ProgressBar::setToPercent(unsigned int value){
    return value*100/length;
}
