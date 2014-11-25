//
//  ContainmentPairScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/7/14.
//
//

#include "ContainmentPairScene.h"

void ContainmentPairScene::setup(){
    leftBlob = ContainmentBlob(ofVec3f(250,600));
    rightBlob = ContainmentBlob(ofVec3f(750, 600));
    
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    
    thisFrame.allocate(640,480);
    prevFrame = thisFrame;
    
    drawTex.allocate(ofGetWidth(), ofGetHeight());
    drawTex.begin();
    drawTex.end();
}

void ContainmentPairScene::update(){
    
    
    int leftCount=0;
    int rightCount=0;
    
    int threshold = 50;
    
    if(cvMan != NULL){
    if(cvMan->bHasNewFrame){
        ofxCvColorImage colorImg;
        colorImg.allocate(cvMan->width, cvMan->height);
        colorImg.setFromPixels(cvMan->getFrame());
        colorImg.convertToGrayscalePlanarImage(thisFrame, 0);
        
        absDiff.allocate(colorImg.getWidth(), colorImg.getHeight());
        absDiff.absDiff(thisFrame,prevFrame );
        ofPixels diffPix = absDiff.getPixels();
        
        for (int x = 0;x<colorImg.getWidth()/2;x+=2){
            for (int y = 0; y<colorImg.getHeight();y+=2){
                int pixBrightness = diffPix.getColor(x, y).getBrightness();
                //cout<<pixBrightness<<endl;

                if (pixBrightness > threshold){
                   rightCount++;
                }
                
            }
            
        }
        
        for (int x = colorImg.getWidth()/2;  x< colorImg.getWidth();  x+=2){
            for (int y = 0;  y < colorImg.getHeight();  y+=2){
                int pixBrightness = diffPix.getColor(x, y).getBrightness();
                if (pixBrightness > threshold){
                    leftCount++;
                    
                }
                
            }
            
        }
        
        
        
        prevFrame   = thisFrame;
    }
    
    }
    
    leftBlob.targetSize= leftCount;
    rightBlob.targetSize = rightCount;
    
    leftBlob.update();
    rightBlob.update();
    
    
}

void ContainmentPairScene::draw(){
    drawTex.begin();

    ofSetColor(0,0,0,15);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    leftBlob.draw();
    rightBlob.draw();
    drawTex.end();

    //filter->begin();
    
    ofSetColor(255);
    drawTex.draw(0, 0);
    //filter->end();
    
    syphon->publishScreen();
    
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