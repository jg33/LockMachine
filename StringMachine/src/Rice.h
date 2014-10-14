//
//  Rice.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#ifndef __StringMachine__Rice__
#define __StringMachine__Rice__

#include <stdio.h>
#include "Particle.h"

class Rice:public Particle{
public:
    Rice():Particle(){color = ofRandom(255);setup();};
    Rice(ofColor _color){color = _color;setup();};
    
    void setup();
    void customUpdate();
    void draw();
    
    ofColor color;
    ofVec3f wind;
    
private:
    ofVec3f rotation;
    
};

#endif /* defined(__StringMachine__Rice__) */
