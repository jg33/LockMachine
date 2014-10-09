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
    
    void setup();
    void update();
    void draw();
    
private:
    ofVec3f pos, vel, acc;
    int seed;
    
};

#endif /* defined(__StringMachine__Particle__) */
