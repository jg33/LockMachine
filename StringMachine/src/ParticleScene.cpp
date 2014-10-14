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
}

void ParticleScene::update(){
    pBoss.addParticle(new CirclePart());
    pBoss.update();
    
    attractive.update();
    attractive.setPosition(ofGetMouseX(), ofGetMouseY(), 0);
    
}

void ParticleScene::draw(){
    ofBackground(0);
    pBoss.draw();
    

}