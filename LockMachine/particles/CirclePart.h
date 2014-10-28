//
//  CirclePart.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/10/14.
//
//

#ifndef __StringMachine__CirclePart__
#define __StringMachine__CirclePart__

#include <stdio.h>
#include "Particle.h"

class CirclePart:public Particle{
public:
    CirclePart():Particle(){color = ofRandom(255);setup();};
    CirclePart(ofColor _color){color = _color;setup();};
    
    void setup();
    void customUpdate();
    void draw();
    
    ofColor color;
    
    
};

#endif /* defined(__StringMachine__CirclePart__) */
