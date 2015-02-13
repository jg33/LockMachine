//
//  ConeScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 1/30/15.
//
//

#include "ConeScene.h"

void ConeScene::setup(){
    ofStyle coneStyle;
    
}

void ConeScene::update(){
    
    ofImage currentFrame;
    currentFrame.allocate(640, 480, OF_IMAGE_COLOR);
    currentFrame.setFromPixels (cvMan->getFrame());
    
    int pixCount =0 ;
    for (int x=0; x< currentFrame.getWidth()-1; x++) {
        for(int y=0; y< currentFrame.getHeight()-1; y++){
            ofColor thisPixel = currentFrame.getColor(x, y) ;
            
            if (thisPixel.getBrightness()>THRESHOLD) {
                pixCount++;
            }
        }
    }
    size = pixCount*0.1;
}

void ConeScene::draw(){
    ofBackground(0);
    ofNoFill();
    ofSetLineWidth(5);
    ofSetCircleResolution(100);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, size, size);
    
    syphon->publishScreen();
}