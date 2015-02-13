//
//  ConeScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 1/30/15.
//
//

#ifndef __LockMachine__ConeScene__
#define __LockMachine__ConeScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "CvManager.h"

#define THRESHOLD 150

class ConeScene: public ofxScene{
public:
    ConeScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("ConeScene"){cvMan = _cv; syphon = _syphon; setup(); };
    void setup();
    void update();
    void draw();
private:
    
    CvManager * cvMan;
    ofxSyphonServer * syphon;
    
    float size = 10;
    
};


#endif /* defined(__LockMachine__ConeScene__) */
