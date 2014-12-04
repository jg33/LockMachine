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
    
    
    for(int i = 0; i< theMesh.getVertices().size(); i++){
        ofVec3f thisPoint = ofVec3f(ofRandom(-4500,4500), ofRandom(-1500,-1024));
        randomPoints.push_back(thisPoint);
    }
    
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
    
    meshShape.clear();
    
    for(int i=0;i<baseMesh.getNumVertices();i++){
        
        ofVec3f oldPoint = baseMesh.getVertex(i).scale(size);
        ofVec3f noiseVec = ofVec3f(ofSignedNoise(speed*i+ofGetElapsedTimef() ),ofSignedNoise(speed* 1.33*i+ofGetElapsedTimef()+33.3),ofSignedNoise(speed*1.77*i+ofGetElapsedTimef()+104.25));
        noiseVec.scale(ofMap(sizeDiff, 0, 25, 3, 10));
        
        ofVec3f finalPoint = oldPoint+noiseVec;
        
        finalPoint.rotate(ofGetElapsedTimef()*10, ofVec3f(1,1,1));
        
        theMesh.setVertex(i, finalPoint);
        //cout<<newPoint<<endl;
        
        ofPolyline aLine;
        aLine.addVertex(finalPoint);
        //aLine.addVertex(finalPoint.x, -1000, finalPoint.z);
        aLine.addVertex(finalPoint.x,-10000);
        
        lines.push_back(aLine);
        
        meshShape.curveTo(theMesh.getVertex(i));
        
    }
    meshShape.close();
    meshTess    = meshShape.getTessellation();
        //subMesh = theMesh;

    
}

void ContainmentBlob::draw(){
    
    ofPushMatrix();
    ofTranslate(pos);
    
    ofSetColor(ofColor::red);
    for(int i=0;i<lines.size();i++){
        float distance =lines[i].getVertices()[0].distance(lines[i].getVertices()[1] );
        ofColor lineColor = ofColor(50, ofMap(distance,1000,1500,0,255));
        ofSetColor(lineColor);
        lines[i].draw();
    }
    
    ofSetColor(ofColor::blueSteel);
    //theMesh.draw();
    //meshShape.setColor(150);
    //meshShape.draw();
    meshTess.draw();
    
    
    float noiseScale1 = ofMap(ofNoise(ofGetElapsedTimef()*0.1), 0, 1, 0.7, 1.2);
    float noiseScale2 = ofMap(ofNoise(66.6+(ofGetElapsedTimef()*0.05)), 0, 1, 0.3, 0.8);

    ofScale(noiseScale1,noiseScale1);
    ofRotate(ofGetElapsedTimef()*10, -1, -3.3, -0.7);
    ofSetColor(ofColor::blueViolet);
    meshTess.draw();

    ofScale(noiseScale2, noiseScale2);
    ofRotate(ofGetElapsedTimef()*2, 1, -4.5, 2.9);
    ofSetColor(ofColor::orangeRed);
    meshTess.draw();
    ofPopMatrix();
    
    
    
}

