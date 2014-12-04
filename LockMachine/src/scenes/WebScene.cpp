//
//  WebScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/30/14.
//
//

#include "WebScene.h"

void WebScene::setup(){
    cout<<"setup webs!"<<endl;
}

void WebScene::update(){
    if (newLine.first != ofPoint(0,0))
        newLine.second = ofPoint(ofGetMouseX(),ofGetMouseY());
    
    for(int i=0;i<primaryLines.size();i++){
        if(numPointsForLine[i] < MAX_POINTS_PER_LINE){
            ofPoint thisPoint = primaryLines[i].getPointAtPercent(ofRandomuf());
            connectingPoints.push_back(thisPoint);
        }
        
    }
    
    for (int i=0; i<connectingPoints.size(); i++) {
        ;
    }
    
}

void WebScene::draw(){
    ofBackground(0);
    
    ofDrawLine(newLine.first, newLine.second);
    
    for (int i =0; i<primaryLines.size(); i++) {
        primaryLines[i].draw();
    }
    
    for (int i =0; i<secondaryLines.size(); i++) {
        secondaryLines[i].draw();
    }
}

void WebScene::addPoint(ofPoint location){
    if (newLine.first == ofPoint(0,0) ) {
        newLine.first = location;
        newLine.second = ofPoint(ofGetMouseX(),ofGetMouseY());
    } else {
        ofPolyline thisLine;
        thisLine.addVertex(newLine.first);
        thisLine.addVertex(newLine.second);
        primaryLines.push_back(thisLine);
        
        numPointsForLine.push_back(0);
        //secondaryLines.push_back(ofMesh());
        //secondaryLines[secondaryLines.size()].setMode(OF_PRIMITIVE_LINES);
        
        newLine.first = ofPoint(0,0);
        newLine.second = ofPoint(0,0);

    }
    
    
}