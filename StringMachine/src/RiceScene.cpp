//
//  RiceScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#include "RiceScene.h"

void RiceScene::setup(){
    pBoss = ofxParticleManager();
    cout<<"setup rice!"<<endl;
    finishedEntering();
    
    ofColor primaryColor = ofColor::goldenRod;
    pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_SPLIT_COMPLEMENTARY);
    pallette.push_back(primaryColor);
    
}

void RiceScene::update(){
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    pBoss.addParticle(new Rice(thisColor));
    pBoss.update();
    
    
}

void RiceScene::draw(){
    ofBackground(0);
    pBoss.draw();
    
    
}