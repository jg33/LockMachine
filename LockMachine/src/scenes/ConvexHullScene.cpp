//
//  ConvexHullScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 10/28/14.
//
//

#include "ConvexHullScene.h"

bool blobSizeSorter(ofxCvBlob first, ofxCvBlob second){
    float firstSize = first.boundingRect.width * first.boundingRect.height;
    float secondSize = second.boundingRect.width * second.boundingRect.height;

    return firstSize > secondSize;
}

bool pointXSorter(ofPoint first, ofPoint second){
    
    return first.x > second.x;
}

void ConvexHullScene::setup(){
    //grabber.initGrabber(VIDEO_WIDTH ,VIDEO_HEIGHT);
    //cam = &grabber;
    ofEnableAlphaBlending();
    
    cvImg.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
    currentFrame.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
    background.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    
    cout<<"setup hulls!"<<endl;
    offsetX=0;
    offsetY=0;
    
    bDrawExternal=false;
    bDrawInternal=false;
    
    ofEnableAlphaBlending();
    
    setCvSettings(50, 500, 500);
    cvThreshold = 50;
    maxDist = 50;
    //inputSmoothing = 0.5;
    
    conMan.startThread();
}

void ConvexHullScene::update(){
    //cam->update();
    
    if (cvMan->bHasNewFrame){
        
        ofxCvGrayscaleImage grey;
        ofxCvColorImage color;
        ofImage thisFrame;
        
        thisFrame.allocate(640 , 480, OF_IMAGE_COLOR);
        thisFrame.setFromPixels( cvMan->getFrame() );
        color.allocate(cvMan->width, cvMan->height);
        color.setFromPixels(thisFrame);
        
        thisFrame.setImageType(OF_IMAGE_GRAYSCALE);
        grey.allocate(VIDEO_WIDTH ,VIDEO_HEIGHT);
        //color.convertToGrayscalePlanarImage(grey, 0);
        grey.setFromPixels(thisFrame);
        

        currentFrame.setFromPixels(grey.getPixels());
        
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
            ofPolyline simplifier;
            simplifier.addVertices(cvContours.blobs[i].pts);
            //hulls.push_back(getConvexHull(cvContours.blobs[i].pts));
            simplifier.simplify(simplification);
            if (simplifier.getVertices().size()>2){
                hulls.push_back(getConvexHull(simplifier.getVertices()));
                
            }
            
        
        }
        
        //NEWCRAP
        /*
        vector<ofxCvBlob> blobs = cvContours.blobs;
        sort(blobs.begin(), blobs.end(), blobSizeSorter );
        
        if ( blobs.size() > newHulls.size() ){
            for (int i=newHulls.size(); i<blobs.size(); i++) {
                newHulls.push_back( Hull(getConvexHull(blobs[i].pts) ));
            }
        } else if (blobs.size() < newHulls.size() ){
            for (int i=newHulls.size(); i<blobs.size(); i--) {
                newHulls.erase(newHulls.end())   ;
            }
        } else {}
        
        for (int i=0; i<blobs.size(); i++) {
            newHulls[i].set( getConvexHull(blobs[i].pts) ) ;

        }
        
        for(int i=0;i<newHulls.size();i++){
            newHulls[i].update();
        }
         */
        
        ///
        
        conMan.lock();
        conMan.setHulls(hulls);
        conMan.unlock();
        
    }
    
    makeConnections(maxDist);
    
    
}

void ConvexHullScene::draw(){
    ofBackground(0,10);
    
    ofTranslate(offsetX, offsetY);
    
    //ofNoFill();
    //ofSetLineWidth(10);
    ofSetColor(255);
    ofSetLineWidth(1);
    
    for (int i=0; i<hulls.size(); i++) { //loop through all the hulls
        ofPolyline p;
        for (int j=0;j<hulls[i].size();j++){ //loop through points in current hull
            p.addVertex(hulls[i][j].x, hulls[i][j].y);
        }
        p.close();
        p.simplify(2);
        p.draw();
    }
    
    
    //NEWCRAP
    /*
    for(int i=0;i< newHulls.size();i++){
        newHulls[i].draw();
    }
     */
    ///
    
    drawConnections();
    
    syphon->publishScreen();
    

    
    if(bIsDebug){
        ofRectangle camDrawRect = ofRectangle(ofGetWidth()-320  ,0   ,320,240);
        ofPoint cvDrawPoint = ofPoint(ofGetWidth()-320,240);
        ofRectangle cvDrawRect = ofRectangle(cvDrawPoint, 320, 240);
        cvImg.draw(cvDrawRect);
        cvContours.draw(cvDrawRect);
        ofImage resizedCam;
        resizedCam = cvMan->getFrame();
        resizedCam.resize(320, 240);
        resizedCam.draw(camDrawRect);
        
    }
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
    
    conMan.lock();
    conMan.setMaxDist(maxDist);
    conMan.setDrawMode(bDrawInternal,bDrawExternal);
    conMan.unlock();
    
    if (bDrawInternal) {
        conMan.lock();
        internalConnections= conMan.getInternalConnections();
        conMan.unlock();
    }
    if (bDrawExternal){
        conMan.lock();
        externalConnections = conMan.getExternalConnections();
        conMan.unlock();
    }
    
    
    
}

void ConvexHullScene::drawConnections(){
    
    ofMesh poly;
    poly.setMode(OF_PRIMITIVE_LINES);
    poly.setupIndicesAuto();
    if(bDrawInternal){
        
        for (int i=0; i<internalConnections.size(); i++) {
            ofFloatColor thisColor = ofColor(255,ofMap(externalConnections[i].first.distance(externalConnections[i].second), 0, maxDist,255,0) );            //ofDrawLine(internalConnections[i].first, internalConnections[i].second);
            poly.addVertex(internalConnections[i].first);
            poly.addColor(thisColor);
            poly.addVertex(internalConnections[i].second);
            poly.addColor(thisColor);
        }
       
    }
    
    if (bDrawExternal){

        for (int i=0; i<externalConnections.size(); i++) {
           
            ofFloatColor thisColor = ofColor(255, ofMap(externalConnections[i].first.distance(externalConnections[i].second), 0, maxDist,255,0) );
            
            poly.addVertex(externalConnections[i].first);
            poly.addColor(thisColor);
            poly.addVertex(externalConnections[i].second);
            poly.addColor(thisColor );
        
        }
    }
    poly.draw(  );

    
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




///HULL///

void Hull::set(vector<ofPoint> _newHull){
    targetHull = _newHull;
    sort(targetHull.begin(),targetHull.end(),pointXSorter);

    
    if(targetHull.size()>hull.size()){
        for (int i = hull.size(); i<targetHull.size(); i++) {
            hull.push_back(targetHull[i]);
        }
    }
    
}

void Hull::update(){
    
    //hull.clear();
    for (int i=0; i<targetHull.size(); i++) {
        
        hull[i] += (targetHull[i]-hull[i])*0.1 ;
        
    }
    
}

void Hull::draw(){
    
        ofPolyline p;
        for (int i=0;i<hull.size();i++){
            p.addVertex(hull[i].x, hull[i].y);
        }
        p.close();
        p.draw();

}


