//
//  AccumulationScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 2/12/15.
//
//

#ifndef __LockMachine__AccumulationScene__
#define __LockMachine__AccumulationScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

class AccumulationScene: public ofxScene{
    
public:
    AccumulationScene():ofxScene("Accumulation"){setup();}
    void setup(){};
    void update(){};
    void draw(){};
private:
    
    ofxSyphonServer* syphon;
    
};


#endif /* defined(__LockMachine__AccumulationScene__) */
