//
//  Attractor.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/10/14.
//
//

#ifndef __StringMachine__Attractor__
#define __StringMachine__Attractor__

#include <stdio.h>


#include "ofMain.h"
#include "ofxAppUtils.h"

class Attractor: public ofNode{
    
public:
    Attractor():ofNode(){};
    void setup(vector<ofxParticle*>*);
    void update();
    
    
private:
    vector<ofxParticle*> * effectedParticles;
    float drag, force;
};

#endif /* defined(__StringMachine__Attractor__) */
