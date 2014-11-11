//
//  ContainmentBlob.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 11/7/14.
//
//

#include "ContainmentBlob.h"

void ContainmentBlob::setup(ofVec3f _pos){
    seed = (int) ofRandom(6000);
    pos =_pos;
    theMesh = ofMesh::box(100,100,100);
    baseMesh = theMesh;
    
    color = ofColor(255);
    
    smoothUp = 0.1;
    smoothDown = 0.01;
    
    prevSize = targetSize;
    speed = 1;
    
}


void ContainmentBlob::update(){
    
    if (targetSize>size){
        size += (targetSize-size)*smoothUp;
    }else if (targetSize<size){
        size += (targetSize-size)*smoothDown;
        
    }
    
    float sizeDiff = abs(size-targetSize);
    
    speed= ofMap(sizeDiff, 0, 25, 1, 10);
    
    lines.clear();
    
    for(int i=0;i<baseMesh.getNumVertices();i++){
        
        ofVec3f oldPoint = baseMesh.getVertices()[i].scale(size);
        ofVec3f noiseVec = ofVec3f(ofSignedNoise(speed*i+ofGetElapsedTimef() ),ofSignedNoise(speed* 1.33*i+ofGetElapsedTimef()+33.3),ofSignedNoise(speed*1.77*i+ofGetElapsedTimef()+104.25));
        noiseVec.scale(ofMap(sizeDiff, 0, 25, 3, 25));
        
        ofVec3f finalPoint = oldPoint+noiseVec;
        
        finalPoint.rotate(ofGetElapsedTimef()*10, ofVec3f(1,1,1));
        
        theMesh.setVertex(i, finalPoint);
        //cout<<newPoint<<endl;
        
        ofPolyline aLine;
        aLine.addVertex(finalPoint);
        aLine.addVertex(finalPoint.x, -1000, finalPoint.z);
        lines.push_back(aLine);
        
    }
    
    subMesh = theMesh;

    
}

void ContainmentBlob::draw(){
    
    ofPushMatrix();
    ofTranslate(pos);
    
    ofSetColor(ofColor::red);
    for(int i=0;i<lines.size();i++){
        lines[i].draw();
    }
    
    ofSetColor(255);
    theMesh.drawWireframe();
    
    float noiseScale1 = ofMap(ofNoise(ofGetElapsedTimef()*0.1), 0, 1, 0.7, 1.2);
    float noiseScale2 = ofMap(ofNoise(66.6+(ofGetElapsedTimef()*0.05)), 0, 1, 0.3, 0.8);

    ofScale(noiseScale1,noiseScale1);
    ofRotate(ofGetElapsedTimef()*10, -1, -3.3, -0.7);
    ofSetColor(150);
    theMesh.drawWireframe();
    ofScale(noiseScale2, noiseScale2);
    ofRotate(ofGetElapsedTimef()*2, 1, -4.5, 2.9);
    ofSetColor(ofColor::black);
    theMesh.draw();
    ofPopMatrix();
    
    
    
}

