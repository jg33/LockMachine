//
//  ConvexHullScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 10/28/14.
//
//

#include "ConvexHullScene.h"


void ConvexHullScene::setup(){
    cam.initGrabber(VIDEO_WIDTH ,VIDEO_HEIGHT);
    
    cvImg.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
    currentFrame.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
    
    cout<<"setup hulls!"<<endl;
    offsetX=0;
    offsetY=0;
    
    bDrawExternal=false;
    bDrawInternal=false;
    
    ofEnableAlphaBlending();
    
    setCvSettings(50, 500, 500);
    cvThreshold = 50;
    maxDist = 50;
    inputSmoothing = 0.5;
}

void ConvexHullScene::update(){
    cam.update();
    if (cam.isFrameNew()){
        
        ofxCvColorImage color;
        ofxCvGrayscaleImage grey;

        color.setFromPixels(cam.getPixels());
        grey.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
        color.convertToGrayscalePlanarImage(grey, 0);
        
        if(inputSmoothing>0){
            currentFrame.setFromPixels(smoothImage(currentFrame.getPixels() , grey.getPixels(), inputSmoothing));
            
        } else{
            currentFrame.setFromPixels(grey.getPixels());
        }
        cvImg.setFromPixels(currentFrame.getPixels());

        if(bIsGrabbingBackground){
            background = grey;
        }
        
        //cvImg = grey;
        cvImg.absDiff(background);
        cvImg.threshold(cvThreshold);
        cvContours.findContours(cvImg, cvMinArea, cvMaxArea, cvNConsidered, false,true);
        
        
        
        if(hulls.size()>0) hulls.clear();
        for (int i=0;i< cvContours.blobs.size();i++){
            hulls.push_back(getConvexHull(cvContours.blobs[i].pts));
            
            for (int i=0; i<hulls.size(); i++) {
                
                
            }
        
        }
        
    }
    
    makeConnections(maxDist);
    
    
}

void ConvexHullScene::draw(){
    ofBackground(0);
    
    if(bIsDebug){
        ofRectangle camDrawRect = ofRectangle(ofGetWidth()-320  ,0   ,320,240);
        ofPoint cvDrawPoint = ofPoint(ofGetWidth()-320,240);
        ofRectangle cvDrawRect = ofRectangle(cvDrawPoint, 320, 240);
        cvImg.draw(cvDrawRect);
        cvContours.draw(cvDrawRect);
        ofImage resizedCam;
        resizedCam = cam.getPixels().getChannel(0);
        resizedCam.resize(320, 240);
        resizedCam.draw(camDrawRect);
    
    }
    
    ofTranslate(offsetX, offsetY);
    
    //ofNoFill();
    //ofSetLineWidth(10);
    ofSetColor(255);
    
    
    for (int i=0; i<hulls.size(); i++) { //loop through all the hulls
        ofPolyline p;
        for (int j=0;j<hulls[i].size();j++){ //loop through points in current hull
            p.addVertex(hulls[i][j].x, hulls[i][j].y);
        }
        p.close();
        p.draw();
    }
    
    drawConnections();

}



/// Convex Hull Calculation ///
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


/// Connection Stuff ///
void ConvexHullScene::makeConnections(int maxDist){
    internalConnections.clear();
    externalConnections.clear();
    
    for (int i=0;i<hulls.size();i++){ //for each hull
        for(int j =0;j<hulls[i].size();j++){ //go through its points
            ofPoint thisPoint = hulls[i][j];
            for(int k =0;k<hulls[i].size();k++){ //each of those looks through its other points
                ofPoint thatPoint = hulls[i][k];
                if (thisPoint.distance(thatPoint) < maxDist) internalConnections.push_back( pair<ofPoint, ofPoint>(thisPoint,thatPoint));
            }
            
            for (int k=0; k<hulls.size(); k++) { //and other hulls
                if (hulls[k]!=hulls[i]){
                    for (int l=0; l<hulls[k].size(); l++) { //and other hulls' points
                        ofPoint thatPoint = hulls[k][l];
                        if (thisPoint.distance(thatPoint)< maxDist) externalConnections.push_back( pair<ofPoint, ofPoint>(thisPoint,thatPoint));
                        
                    }
                }
                
            }
            
        }
    }
    
}

void ConvexHullScene::drawConnections(){
    if(bDrawInternal){
        //ofNoFill();
        //ofBeginShape();
        for (int i=0; i<internalConnections.size(); i++) {
            ofSetColor(255, ofMap(externalConnections[i].first.distance(externalConnections[i].second), 0, maxDist,255,0) );
            ofDrawLine(internalConnections[i].first, internalConnections[i].second);
            //ofVertex(internalConnections[i].first);
            //ofVertex(internalConnections[i].second);
        }
        //ofEndShape();
    }
    
    if (bDrawExternal){
        for (int i=0; i<externalConnections.size(); i++) {
            ofSetColor(255, ofMap(externalConnections[i].first.distance(externalConnections[i].second), 0, maxDist,255,0) );
            ofDrawLine(externalConnections[i].first, externalConnections[i].second);
        }
    }
    
}


/// Smoothing ///

ofPixels ConvexHullScene::smoothImage(ofPixels oldPix, ofPixels newPix, float smoothing){
    ofPixels smoothedImage;
    smoothedImage.allocate(oldPix.getWidth(), oldPix.getHeight(), oldPix.getNumChannels());
    
    
    
    for (int i=0; i<smoothedImage.size();i++){
        try{
        smoothedImage[i] = (oldPix[i]*smoothing )+ (newPix[i]*(1-smoothing));
        }catch (...){
            
        }
    }
    
    return smoothedImage;
    
}

// dumb resize //

ofPixels ConvexHullScene::dumbResize(ofPixels input, int division){
    ofPixels output;
    output.allocate((int)input.getWidth()/division, (int)input.getHeight()/division, input.getNumChannels());
    
    for(int i=0;i<output.size();i+=output.getNumChannels()){
        output[i] = input[i*2];
        
    }
    
    return output;
    
    
}



