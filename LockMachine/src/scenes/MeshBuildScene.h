//
//  MeshBuildScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 1/30/15.
//
//

#ifndef __LockMachine__MeshBuildScene__
#define __LockMachine__MeshBuildScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "CvManager.h"
#include "ofxDelaunay.h"

#define THRESHOLD 200

class MeshBuildScene : public ofxScene{
public:
    MeshBuildScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("MeshBuildScene"){cvMan = _cv; syphon = _syphon; setup(); };
    void setup();
    void update();
    void draw();
private:
    
    CvManager * cvMan;
    ofxSyphonServer * syphon;
    
    ofImage previousFrame;
    ofMesh mesh;
    
    
    
};

#endif /* defined(__LockMachine__MeshBuildScene__) */
