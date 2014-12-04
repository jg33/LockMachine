//
//  Particles.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/29/14.
//
//

#include "Particles.h"

void Dust::setup(){
    seed = ofRandom(6000);
    lifespan = ofRandom(1000,10000);
    lift = 0.8;
    decay = 0.8;
    
    color = ofColor(0);
    
    push(ofVec3f(0,ofRandom(-10,-25),0));
}

void Dust::customUpdate(){
    ofVec3f noise = ofVec3f(ofNoise(seed+ofGetElapsedTimef()), ofNoise(seed+ofGetElapsedTimef()+33.3413231), ofNoise(seed+ofGetElapsedTimef()+392.21314143)  );
    noise.normalize();
    noise *= 0.2;
    vel += ofVec3f(0,-lift,0);
    vel += noise;
    
    vel *= decay;
    
    color = ofColor(ofMap(age, 1, lifespan, 255, 1));
    
    if(pos.y<0) bAlive = false;
}

void Dust::draw(){
    ofSetColor(color);
    if (age >0){
        ofDrawCircle(pos, 1);
    }
}

void Dust::push(ofVec3f amt){
    vel += amt;
    
}