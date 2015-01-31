//
//  DifferenceScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 1/27/15.
//
//

#include "DifferenceScene.h"


void DifferenceScene::setup(){
    
}

void DifferenceScene::update(){
    if(cvMan->bHasNewFrame){
        previousFrame = currentFrame;
        
        ofImage newImage;
        newImage.setImageType(OF_IMAGE_COLOR);
        newImage = cvMan->getFrame();
        newImage.setImageType(OF_IMAGE_GRAYSCALE);
        currentFrame.setFromPixels(newImage);
        
        differenceFrame = currentFrame;
        differenceFrame.absDiff(previousFrame);
    } else{
        cout<<"no new frame"<<endl;
    }
   
}

void DifferenceScene::draw(){

    
    ofRectangle camDrawRect = ofRectangle(0,0   ,ofGetWidth(),ofGetHeight());
    
    differenceFrame.draw(camDrawRect);
    
    syphon->publishScreen();
}