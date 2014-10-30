//
//  ConvexHullScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 10/28/14.
//
//

#ifndef __LockMachine__ConvexHullScene__
#define __LockMachine__ConvexHullScene__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxOpenCv.h"


class ConvexHullScene : public ofxScene{
    
public:
    ConvexHullScene():ofxScene("ConvexHull"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    bool bIsDebug;
    bool bIsGrabbingBackground;
    int offsetX, offsetY;

    
private:
    
    ofVideoGrabber cam;
    ofxCvGrayscaleImage cvImg, background;
    ofxCvContourFinder cvContours;
    
    vector<ofPoint> getConvexHull(vector<ofPoint> points);
    vector< vector<ofPoint> > hulls;
    ofPoint h1,h2,h3;
    
};



#endif /* defined(__LockMachine__ConvexHullScene__) */
