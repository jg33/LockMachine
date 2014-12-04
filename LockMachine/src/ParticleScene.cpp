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
    
    ofColor primaryColor = ofColor::goldenRod;
    pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_SPLIT_COMPLEMENTARY);
    pallette.push_back(primaryColor);
    
}

void ParticleScene::update(){
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    
    /*
    if(ofRandomuf()<flow){
        pBoss.addParticle( new Dust(ofVec2f(ofRandomuf()*ofGetWidth(), ofGetHeight()+10)) ) ;
        
    }
    */
    for (int i=0; i<partsToAdd; i++) {
        pBoss.addParticle( new Dust(ofVec2f(ofRandomuf()*ofGetWidth(), ofGetHeight()+10)) );
        
    }
    partsToAdd = 0;
    
    
    pBoss.update();

    
    
}

void ParticleScene::draw(){
    ofBackground(0);
    pBoss.draw();
    
    //ofDrawRectangle(50, 50, 50, 50);
    
    syphon->publishScreen();
}

