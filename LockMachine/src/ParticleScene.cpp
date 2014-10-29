//
//  ParticleScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/7/14.
//
//

#include "ParticleScene.h"

void ParticleScene::setup(){
    pBoss = ofxParticleManager();
    cout<<"setup particles!"<<endl;
    
    ofColor primaryColor = ofColor::goldenRod;
    pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_SPLIT_COMPLEMENTARY);
    pallette.push_back(primaryColor);
    
}

void ParticleScene::update(){
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    pBoss.update();

    
}

void ParticleScene::draw(){
    ofBackground(0);
    pBoss.draw();
    
    ofDrawRectangle(50, 50, 50, 50);
    

}