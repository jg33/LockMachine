//
//  Rice.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#include "Rice.h"


void Rice::setup(){
    size = 5;
}

void Rice::customUpdate(){
    wind = ofVec2f(0.1,0);
    acc += ofVec2f(0,-1); //gravity
    acc += wind;
    
    rotation = ofVec3f(vel.x*ofGetElapsedTimef(),vel.y*ofGetElapsedTimef(),vel.z*ofGetElapsedTimef() );
    
}

void Rice::draw(){
    ofBackground(0) ;
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRotateX(rotation.x);
    ofRotateY(rotation.y);
    ofRotateZ(rotation.z);
    ofRect(pos, size, size/2);
    ofPopMatrix();
}