//
//  FlowScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/25/14.
//
//

#ifndef __LockMachine__FlowScene__
#define __LockMachine__FlowScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxFlowTools.h"
#include "ofxSyphon.h"
#include "CvManager.h"

using namespace flowTools;

class FlowScene: public ofxScene{
    
public:
    FlowScene():ofxScene("Flow"){};
    FlowScene(CvManager * _cv, ofxSyphonServer * _syphon):ofxScene("Flow"){cv=_cv;syphon=_syphon;setup(); };
    
    void setup();
    void update();
    void draw();
    
private:
    float drawWidth, drawHeight;
    float flowWidth, flowHeight;
    
    
    float lastTime, deltaTime;
    
    CvManager * cv;
    ofxSyphonServer * syphon;
    
    ftOpticalFlow		opticalFlow;
    ftVelocityMask		velocityMask;
    ftFluidSimulation	fluid;
    
    ofImage img;
    
};



#endif /* defined(__LockMachine__FlowScene__) */
