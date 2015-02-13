//
//  MeshBuildScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 1/30/15.
//
//

#include "MeshBuildScene.h"

void MeshBuildScene::setup(){
    previousFrame.allocate(640, 480, OF_IMAGE_COLOR);

}

void MeshBuildScene::update(){
    
    if(cvMan->getHasNewFrame()){
        ofImage currentFrame;
        currentFrame.allocate(640, 480, OF_IMAGE_COLOR);
        currentFrame.setFromPixels (cvMan->getFrame());
        
        mesh.clear();
        
        ofxDelaunay tri;
        
        float x = 0;
        float y = 0;
        
        while ( x< currentFrame.getWidth() ) {
            
            while(y< currentFrame.getHeight()){
                
                ofColor thisPixel = currentFrame.getColor(x, y) ;
                
                if (thisPixel.getBrightness()>THRESHOLD) {
                    float newX = ofMap(x,0,640,0,ofGetWidth());
                    float newY = ofMap(y,0,480,0, ofGetHeight());
                    
                    //newX+= ofSignedNoise(x+ofGetFrameNum()*0.01)*10;
                    //newY += ofSignedNoise(y+ofGetFrameNum()*0.01+66.6)*10;
                    
                    float z = ofMap(thisPixel.getBrightness(),THRESHOLD,255,0,-200);
                    
                    tri.addPoint(newX,newY,z);
                }
                
                y+= (ofNoise((0.8*y)+66.6)*15.0) ;
            }
            y=0;
            x+= (ofNoise(x*0.9)*15.0) ;
        }
        
        tri.triangulate();
        mesh = tri.triangleMesh;
    }
}

void MeshBuildScene::draw(){
    ofBackground(0);
    
    mesh.drawWireframe();
    
    syphon->publishScreen();
    
    
    
}

