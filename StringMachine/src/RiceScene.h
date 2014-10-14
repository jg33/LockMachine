//
//  RiceScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#ifndef __StringMachine__RiceScene__
#define __StringMachine__RiceScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "Rice.h"
#include "ofxColourTheory.h"

class RiceScene : public ofxScene{
    
public:
    RiceScene():ofxScene("Rice"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
private:
    
    ofxParticleManager pBoss;
    
    ofxColourTheory colorMaker;
    vector<ofColor> pallette;
    
};

#endif /* defined(__StringMachine__RiceScene__) */
