//
//  FlowScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/25/14.
//
//

#include "FlowScene.h"

void FlowScene::setup(){
    drawWidth = cv->width;
    drawHeight = cv->height;
    flowWidth = drawWidth/4;
    flowHeight = drawHeight/4;
    
    opticalFlow.setup(flowWidth , flowHeight);
    fluid.setup(flowWidth, flowHeight, drawWidth, drawHeight, false);
    
    opticalFlow.setLambda(0.01);
    opticalFlow.setOffset(5);
    opticalFlow.setThreshold(0.04);
    
    lastTime = ofGetElapsedTimef();

    img.allocate(drawWidth, drawHeight, OF_IMAGE_COLOR);
    cout<<"setup flow!"<<endl;
}

void FlowScene::update(){
    if(cv->bHasNewFrame){
        opticalFlow.setSource(cv->getFrame().getTexture());
        opticalFlow.update(deltaTime);
        img = cv->getFrame();
    }
    fluid.update();
    
    deltaTime = ofGetElapsedTimef() - lastTime;
    lastTime = ofGetElapsedTimef();
}

void FlowScene::draw(){
    ofClear(0,0);
    //ofBackground(0);
    ofSetColor(255);
    ofPushStyle();
    ofDrawBox(1000, 300, 0, 100);
    //img.draw(0,0, drawWidth, drawHeight);
    opticalFlow.getOpticalFlow().draw(0,0,drawWidth,drawHeight);
    ofPopStyle();
    syphon->publishScreen();
}