//
//  Particle.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/9/14.
//
//

#include "Particle.h"


void Particle::update(){
    updateAge();
    
    float sizeDragFactor = ofMap(size,0,maxSize,0.1,1);
    
    vel+=acc;
    vel*= (1- (drag*sizeDragFactor));
    pos+=vel;
    
    customUpdate();
}

void Particle::attractToward(ofVec3f v, float f){
    ofVec3f distToTarget = v-pos;
    float distFactor = ofClamp(ofMap(distToTarget.length(),0,500,1,0),0,1 );
    acc += distToTarget*0.1*f*distFactor;
    
}