//
//  DifferenceScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 1/27/15.
//
//

#ifndef __LockMachine__DifferenceScene__
#define __LockMachine__DifferenceScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "CvManager.h"
#include "ofxOpenCv.h"

class DifferenceScene: public ofxScene{
public:
    DifferenceScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("DifferenceScene"){cvMan = _cv; syphon = _syphon; setup(); };
    void setup();
    void update();
    void draw();
private:
    
    CvManager * cvMan;
    ofxSyphonServer * syphon;
    
    ofxCvGrayscaleImage currentFrame, previousFrame, differenceFrame;
    
};


#endif /* defined(__LockMachine__DifferenceScene__) */
