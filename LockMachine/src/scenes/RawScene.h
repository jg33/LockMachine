//
//  RawScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 1/27/15.
//
//

#ifndef __LockMachine__RawScene__
#define __LockMachine__RawScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "CvManager.h"

class RawScene: public ofxScene{
public:
    RawScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("RawFeed"){cvMan = _cv; syphon = _syphon; setup(); };
    void setup();
    void update();
    void draw();
private:
    
    CvManager * cvMan;
    ofxSyphonServer * syphon;

};

#endif /* defined(__LockMachine__RawScene__) */
