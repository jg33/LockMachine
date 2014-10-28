//
//  Circle.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/8/14.
//
//

#include "Circle.h"


Circle::Circle():ofNode(){
    color = ofColor::white;
    size = 50;
}

void Circle::customDraw(){
    ofSetColor(color);
    ofSetCircleResolution(size*2);
    ofCircle(pos, size);
    
    
}