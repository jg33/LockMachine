//
//  Particle.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/9/14.
//
//

#ifndef __StringMachine__Particle__
#define __StringMachine__Particle__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"

class Particle: public ofxParticle{
    
public:
    Particle(): ofxParticle(){setup();};
    
    virtual void setup(){};
    void update();
    virtual void draw(){};
    
    virtual void customUpdate(){};
    virtual void customDraw(){};
    
    void attractToward(ofVec3f attractor, float force);
    
protected:
    ofVec3f pos, vel, acc;
    int seed;
    float drag;
    float size, maxSize;
    
};

#endif /* defined(__StringMachine__Particle__) */
