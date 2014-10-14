//
//  ConnectorScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/13/14.
//
//

#ifndef __StringMachine__ConnectorScene__
#define __StringMachine__ConnectorScene__

#include <stdio.h>
#include "ofxAppUtils.h"

class Connection{
public:
    Connection(){};
    ofVec3f start, end;
    float dist, maxDist, maxWidth;
    void draw(){
        ofPushStyle();
        float width = ofMap(dist,0,maxDist,maxWidth,0);
        ofSetLineWidth(width);
        ofLine(start, end);
        ofPopStyle();
    };
    
};

class ConnectorScene : public ofxScene{
    
public:
    ConnectorScene():ofxScene("Connections"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    void inline setPoints(map<int,ofVec3f> * _points){points = _points;};
    void inline setPointPower(map<int,float>* _powers){
        pointPower= _powers;};
    
private:
    int connectionDistance =200;
    int maxLineWidth = 10;
    
    map<int,ofVec3f> * points;
    map<int,float> * pointPower;
    vector<Connection> connections;
    
};
#endif /* defined(__StringMachine__ConnectorScene__) */
