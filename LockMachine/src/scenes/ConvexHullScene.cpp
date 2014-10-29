//
//  ConvexHullScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 10/28/14.
//
//

#include "ConvexHullScene.h"


void ConvexHullScene::setup(){
    cam.initGrabber(640,480);
    
    cvImg.allocate(640, 480);
    
}

void ConvexHullScene::update(){
    cam.update();
    if (cam.isFrameNew()){
        ofxCvColorImage color;
        color.allocate(640, 480);
        color.setFromPixels(cam.getPixels());
        
        cvImg = color;
        cvImg.threshold(50);
        cvContours.findContours(cvImg, 50, 640, 500, false,true);
        
        theHull = getConvexHull(cvContours.blobs[0].pts);
        
    }
    
    
}

void ConvexHullScene::draw(){
    cvImg.draw(ofPoint(100,100));
    cvContours.draw(ofPoint(100,100));
    cam.draw(400,400,640,480);
    
    ofBeginShape();
    for (int i=0; i<theHull.size(); i++) {
        ofVertex(theHull[i]);
    }
    ofEndShape();

}

bool lexicalComparison(const ofPoint& v1, const ofPoint& v2) {
    if (v1.x > v2.x) return true;
    else if (v1.x < v2.x) return false;
    else if (v1.y > v2.y) return true;
    else return false;
}

bool isRightTurn(ofPoint a, ofPoint b, ofPoint c) {
    // use the cross product to determin if we have a right turn
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}

vector<ofPoint> ConvexHullScene::getConvexHull(vector<ofPoint> points) {
    sort(points.begin(), points.end(), lexicalComparison);
    
    vector<ofPoint> hull;
    
    hull.push_back(points.at(0));
    hull.push_back(points.at(1));
    
    int currentPoint = 2;
    int direction = 1;
    
    for (int i=0; i<1000; i++) { //max 1000 tries
        
        hull.push_back(points.at(currentPoint));
        
        // look at the turn direction in the last three points
        h1 = hull.at(hull.size()-3);
        h2 = hull.at(hull.size()-2);
        h3 = hull.at(hull.size()-1);
        
        // while there are more than two points in the hull
        // and the last three points do not make a right turn
        while (!isRightTurn(h1, h2, h3) && hull.size() > 2) {
            
            // remove the middle of the last three points
            hull.erase(hull.end() - 2);
            
            if (hull.size() >= 3) {
                h1 = hull.at(hull.size()-3);
            }
            h2 = hull.at(hull.size()-2);
            h3 = hull.at(hull.size()-1);
        }
        
        // going through left-to-right calculates the top hull
        // when we get to the end, we reverse direction
        // and go back again right-to-left to calculate the bottom hull
        if (currentPoint == points.size() -1 || currentPoint == 0) {
            direction = direction * -1;
        }
        
        currentPoint+= direction;
        
        if (hull.front()==hull.back()) break;
    }
    
    return hull;
}