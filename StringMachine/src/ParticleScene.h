//
//  ParticleScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/7/14.
//
//

#ifndef __StringMachine__ParticleScene__
#define __StringMachine__ParticleScene__

#include <iostream>
#include "ofxAppUtils.h"
#include "Particle.h"


class ParticleScene : public ofxScene{
    
public:
    ParticleScene():ofxScene("Particles"){};
    void setup();
    void update();
    void draw();
    
    
private:
    
    ofxParticleManager pBoss;
    
};


#endif /* defined(__StringMachine__ParticleScene__) */
