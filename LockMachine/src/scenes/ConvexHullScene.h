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
#include "CvManager.h"
#include "ofxSyphon.h"

#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480

class Hull;


class ConvexHullScene : public ofxScene{
    
public:
    ConvexHullScene():ofxScene("ConvexHull"){setSingleSetup(false);};
    ConvexHullScene(ofVideoGrabber * _camRef):ofxScene("ConvexHull"){setSingleSetup(false); cam= _camRef;};
    ConvexHullScene(ofVideoGrabber * _camRef, ofxSyphonServer* _syphon):ofxScene("ConvexHull"){setSingleSetup(false); cam= _camRef; syphon = _syphon;};
    ConvexHullScene(CvManager * _cv, ofxSyphonServer* _syphon):ofxScene("ConvexHull"){setSingleSetup(false); cvMan= _cv; syphon = _syphon;};
    
    
    void setup();
    void update();
    void draw();
    void exit(){conMan.stopThread();};
    
    bool bIsDebug;
    bool bIsGrabbingBackground;
    int offsetX, offsetY;
    
    bool bDrawInternal, bDrawExternal;
    int maxDist;
    
    void inline setCvSettings(int min, int max, int num){
        cvMinArea = min;
        cvMaxArea = max;
        cvNConsidered = num;
    };
    int cvMinArea, cvMaxArea, cvNConsidered, cvThreshold;
    
    float simplification=10;
    
private:
    ofxSyphonServer * syphon;
    
    /// CV Stuff ///
    //ofVideoGrabber grabber;
    ofVideoGrabber* cam;
    ofxCvGrayscaleImage cvImg, background;
    ofxCvContourFinder cvContours;
    CvManager * cvMan;
    
    /// Convex Hull Stuff ///
    vector<ofPoint> getConvexHull(vector<ofPoint> points);
    vector< vector<ofPoint> > hulls;
    ofPoint h1,h2,h3;
    
    //vector<Hull> newHulls;
    
    /// Connection Stuff ///
    vector< pair<ofPoint,ofPoint> > internalConnections, externalConnections;
    void makeConnections(int maxDist);
    void drawConnections();
    ConnectionManager conMan;
    //ConnectionDrawer conDraw;

    
    /// Smoothing ///

    ofxCvGrayscaleImage currentFrame;
    
    /// resizer ///
    ofPixels dumbResize(ofPixels input, int division);
    
    
    

};



class Hull{
    
public:
    Hull(){};
    Hull(vector<ofPoint> _hull){ targetHull = _hull; hull=targetHull;};
    void update();
    void set( vector<ofPoint> _newHull);
    void draw();
    
private:
    vector<ofPoint> points;
    vector<ofPoint> previousHull, hull, targetHull;
    
};

#endif /* defined(__LockMachine__ConvexHullScene__) */
