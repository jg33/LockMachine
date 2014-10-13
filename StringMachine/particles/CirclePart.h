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
    CirclePart():Particle(){setup();};
    
    void setup();
    void customUpdate();
    void draw();
    
    
};

#endif /* defined(__StringMachine__CirclePart__) */
