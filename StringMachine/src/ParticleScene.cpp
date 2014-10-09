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
    
}

void ParticleScene::update(){
    pBoss.addParticle(new Particle());
    pBoss.update();
}

void ParticleScene::draw(){
    ofBackground(0);
    pBoss.draw();
}