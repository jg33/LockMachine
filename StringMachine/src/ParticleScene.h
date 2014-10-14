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
#include "CirclePart.h"
#include "Attractor.h"
#include "ofxColourTheory.h"

class ParticleScene : public ofxScene{
    
public:
    ParticleScene():ofxScene("Particles"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    Attractor attractive;
private:
    
    ofxParticleManager pBoss;
    
    ofxColourTheory colorMaker;
    vector<ofColor> pallette;
    
};


#endif /* defined(__StringMachine__ParticleScene__) */
