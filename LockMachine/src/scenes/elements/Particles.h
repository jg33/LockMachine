//
//  Particles.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/29/14.
//
//

#ifndef __LockMachine__Particles__
#define __LockMachine__Particles__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "Particle.h"

class Dust : public Particle{
    
public:
    Dust():Particle(){};
    Dust(ofPoint startLoc):Particle(){
        pos = startLoc;
        setup();
    };

    void setup();
    //void update();
    void draw();
    
    void customUpdate();
    void push(ofVec3f amount);
    
    float lift;
    float decay;
    
private:
    
    int seed;
    ofColor color;
    
};



#endif /* defined(__LockMachine__Particles__) */
