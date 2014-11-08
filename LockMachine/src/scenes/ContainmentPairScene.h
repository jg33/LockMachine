//
//  ContainmentPairScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/7/14.
//
//

#ifndef __LockMachine__ContainmentPairScene__
#define __LockMachine__ContainmentPairScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxOpenCv.h"
#include "ContainmentBlob.h"

enum sides{
    LEFT,
    RIGHT
};

class ContainmentPairScene: public ofxScene{
    
public:
    ContainmentPairScene():ofxScene("ContainmentPair"){setup();};
    ContainmentPairScene(ofVideoGrabber * _grab):ofxScene("ContainmentPair"){cam=_grab;setup();};
    
    void setup();
    void update();
    void draw();
    
    bool bIsDebug;
    
    void setWiggle(sides side, float amount);
    
private:
    
    ofVideoGrabber * cam;
    ofxCvGrayscaleImage thisFrame, prevFrame;
    ofxCvGrayscaleImage absDiff;

    
    ContainmentBlob leftBlob;
    ContainmentBlob rightBlob;
    
    
};

#endif /* defined(__LockMachine__ContainmentPairScene__) */
