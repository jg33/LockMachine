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
    attractive.setup(pBoss.getParticlesPtr());
    cout<<"setup particles!"<<endl;
    finishedEntering();
    
    ofColor primaryColor = ofColor::goldenRod;
    pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_SPLIT_COMPLEMENTARY);
    pallette.push_back(primaryColor);
    
}

void ParticleScene::update(){
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    pBoss.addParticle(new CirclePart(thisColor));
    pBoss.update();
    
    attractive.update();
    attractive.setPosition(ofGetMouseX(), ofGetMouseY(), 0);
    
}

void ParticleScene::draw(){
    ofBackground(0);
    pBoss.draw();
    

}