//
//  ContainmentPairScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/7/14.
//
//

#include "ContainmentPairScene.h"

void ContainmentPairScene::setup(){
    leftBlob = ContainmentBlob(ofVec3f(150,600));
    rightBlob = ContainmentBlob(ofVec3f(650, 600));
    
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    
    thisFrame.allocate(cam->getWidth(), cam->getHeight());
    prevFrame = thisFrame;
}

void ContainmentPairScene::update(){
    cam->update();
    
    int leftCount=0;
    int rightCount=0;
    
    int threshold = 50;
    
    if(cam->isFrameNew()){
        ofxCvColorImage colorImg;
        colorImg.setFromPixels(cam->getPixels());
        colorImg.convertToGrayscalePlanarImage(thisFrame, 0);
        
        absDiff.allocate(cam->getWidth(), cam->getHeight());
        absDiff.absDiff(thisFrame,prevFrame );
        ofPixels diffPix = absDiff.getPixels();
        
        for (int x = 0;x<cam->getWidth()/2;x++){
            for (int y = 0; y<cam->getHeight();y++){
                int pixBrightness = diffPix.getColor(x, y).getBrightness();
                //cout<<pixBrightness<<endl;

                if (pixBrightness > threshold){
                   rightCount++;
                }
                
            }
            
        }
        
        for (int x = cam->getWidth()/2;  x< cam->getWidth();  x++){
            for (int y = 0;  y < cam->getHeight();  y++){
                int pixBrightness = diffPix.getColor(x, y).getBrightness();
                if (pixBrightness > threshold){
                    leftCount++;
                    
                }
                
            }
            
        }
        
        
        
        prevFrame   = thisFrame;
    }
    
    cout<<"left: "<<rightCount<<endl;
    
    leftBlob.targetSize= leftCount/10;
    rightBlob.targetSize = rightCount/10;
    
    leftBlob.update();
    rightBlob.update();
    
    
}

void ContainmentPairScene::draw(){
    ofSetColor(0,0,0,15);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    leftBlob.draw();
    rightBlob.draw();
    
    if (bIsDebug){
        ofSetColor(255,255);
        absDiff.draw(450, 10, 320, 240);
    }
    

}

void ContainmentPairScene::setWiggle(sides side, float amt){
    switch(side){
        case LEFT:
            leftBlob.targetSize = amt;
            break;
            
        case RIGHT:
            rightBlob.targetSize = amt;
            break;
            
            
    }
    
    
}