//
//  MeshBuildScene.cpp
//  LockMachine
//
//  Created by Jesse Garrison on 1/30/15.
//
//

#include "MeshBuildScene.h"

void MeshBuildScene::setup(){
    
}

void MeshBuildScene::update(){
    
}

void MeshBuildScene::draw(){
    ofImage img;
    img.setFromPixels(cvMan->getFrame());
    img.setImageType(OF_IMAGE_GRAYSCALE);
    
    ofRectangle camDrawRect = ofRectangle(0,0   ,ofGetWidth(),ofGetHeight());
    
    img.draw(camDrawRect);
    syphon->publishScreen();
    
    
}