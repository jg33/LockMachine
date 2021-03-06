//
//  CircleScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/8/14.
//
//

#ifndef __StringMachine__CircleScene__
#define __StringMachine__CircleScene__

#define NUMCIRCLES 5

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"


class CircleScene : public ofxScene{
    
public:
    CircleScene():ofxScene("Circles"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    void setSizes(map<int,float>);
    
    
private:
    
    
};



#endif /* defined(__StringMachine__CircleScene__) */
