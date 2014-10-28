//
//  Attractor.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/10/14.
//
//

#include "Attractor.h"

void Attractor::setup(vector<ofxParticle*>* p){
    effectedParticles = p;
    force = 0.1;
    
}

void Attractor::update(){
    for (int i=0; i<effectedParticles->size();i++){
        effectedParticles->at(i)->attractToward(getPosition(),force);
        
    }
    
}