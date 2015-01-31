//
//  RawScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 1/27/15.
//
//

#include "RawScene.h"

void RawScene::setup(){
    
}

void RawScene::update(){
    
}

void RawScene::draw(){
    ofImage img;
    img.setFromPixels(cvMan->getFrame());
    img.setImageType(OF_IMAGE_GRAYSCALE);
    
    ofRectangle camDrawRect = ofRectangle(0,0   ,ofGetWidth(),ofGetHeight());
    
    img.draw(camDrawRect);
    syphon->publishScreen();
    
    
}