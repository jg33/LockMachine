//
//  Particle.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/9/14.
//
//

#include "Particle.h"

void Particle::setup(){
    lifespan = ofRandom(10000);
    pos = ofVec3f(ofRandom(ofGetWidth()),ofRandom( ofGetHeight()));
    seed = ofRandom(10000);
    
}

void Particle::update(){
    updateAge();
    
    acc = ofVec3f(ofSignedNoise(seed+ofGetElapsedTimef()), ofSignedNoise(600+seed+ofGetElapsedTimef()));
    
    vel+=acc;
    pos+=vel;
}

void Particle::draw(){
    ofSetColor(255);
    ofCircle(pos, 10) ;

}