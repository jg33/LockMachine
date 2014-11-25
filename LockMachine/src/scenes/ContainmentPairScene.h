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
#include "ofxFilterLibrary.h"
#include "CvManager.h"
#include "ofxSyphon.h"

#include "ContainmentBlob.h"


enum sides{
    LEFT,
    RIGHT
};

class ContainmentPairScene: public ofxScene{
    
public:
    ContainmentPairScene():ofxScene("ContainmentPair"){setup();};
    ContainmentPairScene(ofVideoGrabber * _grab):ofxScene("ContainmentPair"){cam=_grab;setup();};
    ContainmentPairScene(CvManager * _cv):ofxScene("ContainmentPair"){cvMan = _cv;setup();};
    ContainmentPairScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("ContainmentPair"){cvMan = _cv; syphon = _syphon; setup();};
    
    void setup();
    void update();
    void draw();
    
    bool bIsDebug;
    
    void setWiggle(sides side, float amount);
    
private:
    
    ofVideoGrabber * cam;
    CvManager * cvMan;
    ofxCvGrayscaleImage thisFrame, prevFrame;
    ofxCvGrayscaleImage absDiff;

    
    ContainmentBlob leftBlob;
    ContainmentBlob rightBlob;
    
    ofFbo drawTex;
    
    KuwaharaFilter * filter = new KuwaharaFilter(0);
    
    ofxSyphonServer * syphon;
    
};

#endif /* defined(__LockMachine__ContainmentPairScene__) */
