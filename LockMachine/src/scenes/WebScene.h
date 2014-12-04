//
//  WebScene.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/30/14.
//
//

#ifndef __LockMachine__WebScene__
#define __LockMachine__WebScene__

#include <stdio.h>
#include "ofxAppUtils.h"

#define MAX_POINTS_PER_LINE 50

class WebScene: public ofxScene{
public:
    WebScene():ofxScene("Web"){};
    void setup();
    void update();
    void draw();
    
    void addPoint(ofPoint location);
    
private:
    pair<ofPoint,ofPoint> newLine;
    vector<ofPolyline> primaryLines;
    vector<ofPolyline> secondaryLines;
    
    vector<int> numPointsForLine;
    vector<ofPoint> connectingPoints;
};
#endif /* defined(__LockMachine__WebScene__) */
