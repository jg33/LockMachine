//
//  CirclePart.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/10/14.
//
//

#include "CirclePart.h"


void CirclePart::setup(){
    lifespan = ofRandom(10000);
    pos = ofVec3f(ofRandom(ofGetWidth()),ofRandom( ofGetHeight()));
    seed = ofRandom(10000);
    maxSize = 10;
    size = ofRandom(1,maxSize);
    drag = 0.1;
    
    
}

void CirclePart::customUpdate(){
    
    acc = ofVec3f(ofSignedNoise(seed+ofGetElapsedTimeMillis()*0.00009), ofSignedNoise(600+seed+ofGetElapsedTimeMillis()*0.00003), ofSignedNoise(132+seed+ofGetElapsedTimeMillis()*0.00007)  ) ;

}

void CirclePart::draw(){
    if (getAge() > (lifespan*0.9) || getAge()==0){
        ofSetColor( ofClamp(ofMap(getAge(),lifespan*0.9,lifespan,255,0),0,255) ) ;
    }else{
        ofSetColor(color);
    }
    ofCircle(pos, size) ;
    
}

